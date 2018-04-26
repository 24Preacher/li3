#include "parser.h"



/*gboolean teste (gpointer key,gpointer value, gpointer data)
{
	long	sKey = *(long*) (key);
	char *title = getTitle(value);
	short typeid = getPostType(value);
	long	parentid=getParentId(value);
	int   score=getScore(value);
	int commentCount=getComments(value);
	int answerCount =getAnswers(value);
	long owner =getUserId(value);

	int reputation= getRep(value);
	int month =getMes(value);
	int year =getAno(value);
	int dia=getDia(value);
	int minuto =getMinutos(value);
	int hora= getHora(value);

	g_print ("\n\nKey: %lu\ntitle: %s\ntypeid: %d\nowner: %lu\nparentid: %lu\nscore: %d\ncommentCount: %d\nanswerCount: %d\n\n\n", sKey,title,typeid,owner,parentid,score,commentCount,answerCount);

	printf("id do user é %lu e a sua reputação é %d", owner,reputation);
	printf("dia do post é %d o mes é %d e o ano é %d a hora é %d:%d\n",dia,month,year,hora,minuto );

	return FALSE;
}


*/
// vai ao users.xml buscar o id, reputation, displayname e aboutme
//usar um contador para ver o total de users

int parseUsers (xmlDocPtr doc, GHashTable *hash_table){

	long id;
	xmlChar* bio;
	xmlChar* name;
	int rep;
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


	while (cur != NULL) {

		if (xmlStrcmp(cur->name, (const xmlChar *)"row")) {
			while(!xmlStrcmp(cur->name, (const xmlChar *)"/>")){
				id = atol((char*)(xmlGetProp(cur, (const xmlChar*)"Id")));
				bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");
				name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
				rep = atoi((char*)(xmlGetProp(cur, (const xmlChar*)"Reputation")));

				cur = cur->next;
				num_users ++;
			}
		}


		Users user = createUsers(id, (char*) name,(char*) bio, rep);
		g_hash_table_insert (hash_table, (gpointer) id, (gpointer)user);



    }
     xmlFreeDoc(doc);
    return num_users;

}


//vai buscar o id do post, PostTypeId, title, CreationDate, ParentId, OwnerUserId, AnswerCount, CommentCount, Score
//ver argumentos
void parsePosts (xmlDocPtr doc, GTree *tree1, GTree *tree2){

	xmlNodePtr curr = xmlDocGetRootElement(doc);

	long post_id;

	short post_type;
    xmlChar* ptype;
	xmlChar* title;
	Tags tags;
	Data creation_date;
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





//ver se é um a um
while (curr != NULL) {
	if ((!xmlStrcmp(curr->name, (const xmlChar *)"row"))) {
		while(!xmlStrcmp(curr->name, (const xmlChar *)"/>")){
			post_id = atol((char*)(xmlGetProp(curr,(const xmlChar *)"Id")));
			ptype = (xmlGetProp(curr,(const xmlChar *)"PostTypeId"));
			title = xmlGetProp(curr,(const xmlChar *)"Title");
			tags = strToTags((char*)(xmlGetProp(curr,(const xmlChar *)"Tags")));
			creation_date = strToData((char*)(xmlGetProp(curr,(const xmlChar *)"CreationDate")));
			user_id = atoi((char*)(xmlGetProp(curr,(const xmlChar *)"OwnerUserId")));
			comment_count = atoi((char*)(xmlGetProp(curr,(const xmlChar *)"CommentCount")));
			score = atoi((char*)(xmlGetProp(curr,(const xmlChar *)"Score")));
		}
        post_type = atoi((char*) ptype);
		if ((!xmlStrcmp(ptype, (const xmlChar *)"1"))){
				answer_count=atoi((char*)(xmlGetProp(curr, (const xmlChar *)"AnswerCount")));
		}
		else if ((!xmlStrcmp(ptype, (const xmlChar *)"2"))){
				parent_id = atoi((char*)(xmlGetProp(curr, (const xmlChar *)"ParentId")));
		}


			Posts_D post = createPostsD(creation_date, user_id, post_id, (char *) title, answer_count, post_type, parent_id, comment_count, score, tags);
			long *key = malloc(sizeof(long));

			*key = atol((char*) post_id);

			g_tree_insert(tree1, key, post);



			Posts_ID post2 = createPostsID(post_id, user_id,(char *) title,creation_date, answer_count, post_type, parent_id, comment_count, score, tags);
			long *key2 = malloc(sizeof(long));

			*key2 = atol((char*) post_id);

			g_tree_insert(tree2, key2, post2);


			curr = curr->next;
	}
	xmlFreeDoc(doc);
    }
}
/*
int main(int argc, char **argv){

	char *docname;
	GTree	*tree;
	docname = "/Desktop/copy/src/Posts.xml";
	parsePosts(docname, tree);
	g_tree_foreach(tree,&(teste),NULL);
	return(1);

}*/





//vai buscar id_tag, tagname, count e inserir numa hash
void parseTags (xmlDocPtr doc, GHashTable *hash_table){

	xmlNodePtr nod = xmlDocGetRootElement(doc);

	long id_tag;
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

	while (nod != NULL) {
		if (!xmlStrcmp(nod->name, (const xmlChar *)"row")) {
			while(!xmlStrcmp(nod->name, (const xmlChar *)"/>")){
				id_tag = atol((char*)(xmlGetProp(nod,(const xmlChar *)"Id")));
				tagname = xmlGetProp(nod,(const xmlChar *)"TagName");
			}
		}
		HashTags tag = createHashTag((char*)tagname, id_tag);
	 	g_hash_table_insert(hash_table, (gpointer) id_tag, (gpointer)tag);

	}

xmlFreeDoc(doc);

}




int parseDoc(char *doctags, char *docusers, char *docposts, GHashTable *hash_tags, GHashTable *hash_users, GTree *tree1, GTree *tree2){

	xmlDocPtr doc1, doc2, doc3;
	xmlNodePtr cur1, cur2, cur3;

	doc1 = xmlParseFile(doctags);
	doc2 = xmlParseFile(docusers);
	doc3 = xmlParseFile(docposts);


	if (doc1 == NULL || doc2==NULL || doc3==NULL) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return 0;
	}

	cur1 = xmlDocGetRootElement(doc1);
	cur2 = xmlDocGetRootElement(doc2);
	cur3 = xmlDocGetRootElement(doc3);

	if (cur1 == NULL || cur2 == NULL || cur3 == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc1);
		xmlFreeDoc(doc2);
		xmlFreeDoc(doc3);
	return 0;
	}


	parseTags(doc1, hash_tags);
	int num_users = parseUsers(doc2, hash_users);
	parsePosts(doc3, tree1, tree2);


	xmlFreeDoc(doc1);
	xmlFreeDoc(doc2);
	xmlFreeDoc(doc3);

	return num_users;

}
