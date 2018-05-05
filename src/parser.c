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

	Data d = getDate(value);
	int month =getMes(d);
	int year =getAno(d);
	int dia=getDia(d);
	int minuto =getMinutos(d);
	int hora= getHora(d);

	g_print ("\n\nKey: %lu\ntitle: %s\ntypeid: %d\nowner: %lu\nparentid: %lu\nscore: %d\ncommentCount: %d\nanswerCount: %d\n\n\n", sKey,title,typeid,owner,parentid,score,commentCount,answerCount);

	printf("id do user é %lu \n", owner);
	printf("dia do post é %d o mes é %d e o ano é %d a hora é %d:%d\n",dia,month,year,hora,minuto );

	return FALSE;
} */


int parseUsers (xmlDocPtr doc, GHashTable *hash_table){


	xmlNodePtr cur = xmlDocGetRootElement(doc);

	char* id;
	xmlChar* bio;
	xmlChar* name;

	char* rep;
	int num_users;


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
				id = (char*)(xmlGetProp(cur, (const xmlChar*)"Id"));
				bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");
				name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
				rep = (char*)(xmlGetProp(cur, (const xmlChar*)"Reputation"));

				long *key = malloc(sizeof(long));
                *key = atol(id);

				Users user = createUsers(atol(id), (char*) name,(char*) bio, atoi(rep));

                g_hash_table_insert(hash_table, key, user);
			}
		cur = cur->next;
		num_users ++;

    	}
    return num_users;
}


void parsePosts (xmlDocPtr doc, GTree *tree1, GTree *tree2){


	xmlNodePtr curr = xmlDocGetRootElement(doc);

	xmlChar * keyxml;
	long post_id;
	//short post_type;
  int ptype;
	char * title;
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
				keyxml = (xmlGetProp(curr,(const xmlChar *)"Id"));
				post_id = atol((char *) keyxml);
				xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"OwnerUserId"));
				user_id = atol((char *) keyxml);
				xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"ParentId"));
				parent_id = keyxml ? atol((char *)keyxml) : -2;
				if (keyxml)
					xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"CommentCount"));
				comment_count = keyxml ? atoi((char *)keyxml) : 0;
				if (keyxml)
					xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"Score"));
				score = keyxml ? atoi((char *)keyxml) : 0;
				if (keyxml)
					xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"PostTypeId"));
				ptype = keyxml ? atoi((char *)keyxml) : -3;
				if (keyxml)
					xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"AnswerCount"));
				answer_count = keyxml ? atoi((char *)keyxml) : 0;
				if (keyxml)
					xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"CreationDate"));
				creation_date = keyxml ? strToData((char *) keyxml) : NULL;
				if (keyxml)
					xmlFree(keyxml);

				keyxml = (xmlGetProp(curr,(const xmlChar *)"Tags"));
				tags = keyxml ? strToTags((char *)keyxml) : NULL;
				//sq free

				keyxml = (xmlGetProp(curr,(const xmlChar *)"Title"));
				title = keyxml ? mystrdup((char *) keyxml) : NULL;
				if (keyxml)
					xmlFree(keyxml);

				Posts_ID post1 = createPostsID(post_id,user_id,title,creation_date,answer_count,ptype,parent_id,comment_count,score,tags);
				Posts_D post2 = createPostsD(creation_date,user_id,post_id,title,answer_count,ptype,parent_id,comment_count,score,tags);

				/*  printf("ID USER:%ld\n",getUserId2(post1));
				  printf("ID POST:%ld\n",getPostId2(post1));
				  printf("TITULO:%s\n",getTitle2(post1));
					printf("COMENTARIOS:%d\n",getComments2(post1));
				  printf("RESPOSTAS:%d\n",getAnswers2(post1));
				  printf("TIPO:%d\n",getPostType2(post1));
					printf("SCORE:%d\n",getScore2(post1));
				  printf("ID PAI:%ld\n",getParentId2(post1));
*/
				long * key = malloc(sizeof(long));
				*key = post_id;


				g_tree_insert(tree1, key, post1);
				g_tree_insert(tree2, creation_date, post2);


				/*printf("ID POST:%ld\n",getPostId2(post1));
				printf("ID USER:%ld\n",user_id);
				printf("ID PAI:%ld\n",parent_id);
				printf("COMENTARIOS:%d\n",comment_count);
				printf("SCORE:%d\n",score);
				printf("TIPO:%d\n",ptype);
				printf("RESPOSTAS:%d\n",answer_count);
				printf("TITULO:%s\n",);*/

				if (title)
					free(title);


		}
			curr = curr->next;
    }
}

/*
int main(int argc, char **argv){


    char* docname2 = "/home/mercy/Desktop/nana/src/Users.xml";
    char* docname3 = "/home/mercy/Desktop/nana/src/Posts.xml";

	GTree *tree1 = g_tree_new((GCompareFunc)&data_ord);
    GTree *tree2 = g_tree_new((GCompareFunc)&compareID);
    GHashTable *users = g_hash_table_new(g_direct_hash, g_direct_equal);


    int n = parseDoc(docname2, docname3, users, tree1, tree2);

    return n;
}





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

//    g_tree_foreach(tree1, &(teste), NULL);


// 	xmlFreeDoc(doc1);
	xmlFreeDoc(doc2);
	xmlFreeDoc(doc3);

	return num_users;

}
