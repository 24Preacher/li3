#include "parser.h"


/*
gboolean teste (gpointer key,gpointer value, gpointer data)
{
	long	sKey = *(long*) (key);
	char *title = getTitle(value);
	short typeid = getPostType(value);
 	long	parentid=getParentId(value);
 	int   score=getScore(value);
 	int commentCount=getComments(value);
 	int answerCount =getAnswers(value);
 	long owner =getUserId(value);

	//int reputation= getRep(value);
	int month =getMes(value);
	int year =getAno(value);
	int dia=getDia(value);
	int minuto =getMinutos(value);
	int hora= getHora(value);

	g_print ("\n\nKey: %lu\ntitle: %s\ntypeid: %d\nowner: %lu\nparentid: %lu\nscore: %d\ncommentCount: %d\nanswerCount: %d\n\n\n", sKey,title,typeid,owner,parentid,score,commentCount,answerCount);

	printf("id do user é %lu \n", owner);
	printf("dia do post é %d o mes é %d e o ano é %d a hora é %d:%d\n",dia,month,year,hora,minuto );

	return FALSE;
}*/

// vai ao users.xml buscar o id, reputation, displayname e aboutme
//usar um contador para ver o total de users

int parseUsers (xmlDocPtr doc, GHashTable *hash_table){

	//long id;
	char* id;
	xmlChar* bio;
	xmlChar* name;
	//int rep;
	char* rep;
	int num_users;

	xmlNodePtr cur = xmlDocGetRootElement(doc);

	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
			return 0;
	}

	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return 0;
	}

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

		if (xmlStrcmp(cur->name, (const xmlChar *)"row") == 0) {
			//while(!xmlStrcmp(cur->name, (const xmlChar *)"/>")){
				id = (char*)(xmlGetProp(cur, (const xmlChar*)"Id"));
				bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");
				name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
				rep = (char*)(xmlGetProp(cur, (const xmlChar*)"Reputation"));

				long *key = malloc(sizeof(long));
        *key = atol(id);

				Users user = createUsers(atol(id), (char*) name,(char*) bio, atoi(rep));
// 				g_hash_table_insert (hash_table, (gpointer) id, (gpointer)user);
                g_hash_table_insert(hash_table, key, user);
			//}
			}
		cur = cur->next;
		num_users ++;

    	}
    return num_users;
}


//vai buscar o id do post, PostTypeId, title, CreationDate, ParentId, OwnerUserId, AnswerCount, CommentCount, Score
//ver argumentos
void parsePosts (xmlDocPtr doc, GTree *tree1, GTree *tree2){

	xmlNodePtr curr = xmlDocGetRootElement(doc);

	char* post_id;

	short post_type;
    xmlChar* ptype;
	xmlChar* title;
	Tags tags = NULL;
	Data creation_date = NULL;
	long parent_id;
	long user_id;
	int answer_count;
	int comment_count;
	int score;


	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
			return;
	}

	if (curr == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	curr = curr->xmlChildrenNode;

while (curr != NULL) {
	if (xmlStrcmp(curr->name, (const xmlChar *)"row") == 0) {
		//while(!xmlStrcmp(curr->name, (const xmlChar *)"/>")){
			post_id = (char*)(xmlGetProp(curr,(const xmlChar *)"Id"));
			ptype = xmlGetProp(curr,(const xmlChar *)"PostTypeId");
			title = xmlGetProp(curr,(const xmlChar *)"Title");
			tags = strToTags((char*)(xmlGetProp(curr,(const xmlChar *)"Tags")));
			creation_date = strToData((char*)(xmlGetProp(curr,(const xmlChar *)"CreationDate")));
			user_id = atoi((char*)(xmlGetProp(curr,(const xmlChar *)"OwnerUserId")));
			comment_count = atoi((char*)(xmlGetProp(curr,(const xmlChar *)"CommentCount")));
			score = atoi((char*)(xmlGetProp(curr,(const xmlChar *)"Score")));
		//}
        post_type = atoi((char*) ptype);
		if ((!xmlStrcmp(ptype, (const xmlChar *)"1"))){
				answer_count=atoi((char*)(xmlGetProp(curr, (const xmlChar *)"AnswerCount")));
		}
		else if ((!xmlStrcmp(ptype, (const xmlChar *)"2"))){
				parent_id = atoi((char*)(xmlGetProp(curr, (const xmlChar *)"ParentId")));
		}


			Posts_D post = createPostsD(creation_date, user_id, atol(post_id), (char *) title, answer_count, post_type, parent_id, comment_count, score, tags);
			//long *key = malloc(sizeof(long));

			//*key = atol((char*) post_id);

			Data *key = malloc(sizeof(Data));
			*key = creation_date;
			g_tree_insert(tree1, key, post);



			Posts_ID post2 = createPostsID(atol(post_id), user_id,(char *) title,creation_date, answer_count, post_type, parent_id, comment_count, score, tags);
			long *key2 = malloc(sizeof(long));

			//*key2 = atol((char*) post_id);
			*key2 = atol(post_id);
			g_tree_insert(tree2, key2, post2);
		}
			curr = curr->next;
    }
}

/*
int main(int argc, char **argv){

	char* docname1 = "/home/mercy/Desktop/nana/src/Tags.xml";
    char* docname2 = "/home/mercy/Desktop/nana/src/Users.xml";
    char* docname3 = "/home/mercy/Desktop/nana/src/Posts.xml";
    
	GTree *tree1 = g_tree_new((GCompareFunc)&data_ord);
    GTree *tree2 = g_tree_new((GCompareFunc)&compareID);
    GHashTable *users = g_hash_table_new(g_direct_hash, g_direct_equal);
    GHashTable *tags = g_hash_table_new(g_str_hash, g_str_equal);
    
    int n = parseDoc(docname1, docname2, docname3, tags, users, tree1, tree2);
    
    return n;
}*/



/*

//vai buscar id_tag, tagname, count e inserir numa hash
void parseTags (xmlDocPtr doc, GHashTable *hash_table){

	xmlNodePtr nod = xmlDocGetRootElement(doc);

    char* id_tag;
	xmlChar* tagname;

	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
			return;
	}

	if (nod == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	nod = nod->xmlChildrenNode;
	while (nod != NULL) {
		if (!xmlStrcmp(nod->name, (const xmlChar *)"row")) {
			//while(!xmlStrcmp(nod->name, (const xmlChar *)"/>")){
				id_tag = (char*)(xmlGetProp(nod,(const xmlChar *)"Id"));
				tagname = xmlGetProp(nod,(const xmlChar *)"TagName");
			//}

			HashTags tag = createHashTag((char*)tagname, atol(id_tag));
            long *key = malloc(sizeof(long));
            *key = atol(id_tag);
		 	g_hash_table_insert(hash_table, key, tag);
			}
		nod = nod->next;
		}
}
*/



// int parseDoc(char *doctags, char *docusers, char *docposts, GHashTable *hash_tags, GHashTable *hash_users, GTree *tree1, GTree *tree2){
int parseDoc(char *docusers, char *docposts, GHashTable *hash_users, GTree *tree1, GTree *tree2){
	xmlDocPtr doc3, doc2;
	xmlNodePtr cur3, cur2;

// 	doc1 = xmlParseFile(doctags);
	doc2 = xmlParseFile(docusers);
	doc3 = xmlParseFile(docposts);


	if (doc3 == NULL || doc2==NULL) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return 0;
	}

// 	cur1 = xmlDocGetRootElement(doc1);
	cur2 = xmlDocGetRootElement(doc2);
 	cur3 = xmlDocGetRootElement(doc3);

	if (cur3 == NULL || cur2 == NULL) {
		fprintf(stderr,"empty document\n");
// 		xmlFreeDoc(doc1);
		xmlFreeDoc(doc2);
		xmlFreeDoc(doc3);
	return 0;
	}


	parsePosts(doc3, tree1, tree2);
     printf("parse dos posts feito\n");
    
int num_users = parseUsers(doc2, hash_users);
     printf("parse dos users feito\n");
//      parseTags(doc1, hash_tags);
//     printf("parse das tags feito\n");
     
//      g_tree_foreach(tree1, &(teste), NULL);


// 	xmlFreeDoc(doc1);
	xmlFreeDoc(doc2);
	xmlFreeDoc(doc3);

	return num_users;

}
