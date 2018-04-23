#include "parser.h"



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


/*
// vai ao users.xml buscar o id, reputation, displayname e aboutme
//usar um contador para ver o total de users

int parseUsers (xmlNodePtr doc, GHashTable *hash_table){

	long id;
	xmlChar bio;
	xmlChar name;
	int rep;
	int num_users;

	xmlNodePtr cur = xmlDocGetRootElement(doc);

	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
			return;
	}

	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}


	while (cur != NULL) {

		if ((xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			while((!xmlStrcmp(cur->name, (const xmlChar *)"/>")){
				id = atoi(xmlGetProp(cur, (long *)"Id"));
				bio = xmlGetProp(cur, (xmlChar *)"AboutMe");
				name = xmlGetProp(cur, (xmlChar *)"DisplayName");
				rep = atoi(xmlGetProp(cur, (char *)"Reputation"));

				cur = cur->next;
				num_users ++;
			}
		}


		user = create_user(id, name, bio, rep);
		gboolean g_hash_table_insert (hash_table, id, user);

		return num_users;
}

*/


//vai buscar o id do post, PostTypeId, title, CreationDate, ParentId, OwnerUserId, AnswerCount, CommentCount, Score
//ver argumentos
void parsePosts (xmlDocPtr doc, GTree *tree1, GTree *tree2){

	xmlNodePtr curr = xmlDocGetRootElement(doc);

	long post_id;
	short post_type;
	xmlChar title;
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
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
		while((!xmlStrcmp(cur->name, (const xmlChar *)"/>")){
			post_id = atoi(xmlGetProp(cur,(const xmlChar *)"Id"));
			post_type = atoi(xmlGetProp(cur,(const xmlChar *)"PostTypeId"));
			title = xmlGetProp(cur,(const xmlChar *)"Title");
			tags = atoi(xmlGetProp(cur,(const xmlChar *)"Tags"));
			creation_date = atoi(xmlGetProp(cur,(const xmlChar *)"CreationDate"));
			parent_id =(xmlChar*) "0";
			user_id = atoi(xmlGetProp(cur,(const xmlChar *)"OwnerUserId"));
			answer_count=(xmlChar*)"0";
			comment_count = atoi(xmlGetProp(cur,(const xmlChar *)"CommentCount"));
			score = atoi(xmlGetProp(cur,(const xmlChar *)"Score"));
		}

		if ((!xmlStrcmp(post_type, (const xmlChar *)"1"))){
				answer_count=atoi(xmlGetProp(cur, (const xmlChar *)"AnswerCount"));
		}
		else if ((!xmlStrcmp(post_type, (const xmlChar *)"2"))){
				parent_id = atoi(xmlGetProp(cur, (const xmlChar *)"ParentId"));
		}


			post = createPostsD(creation_date, user_id, post_id, (char *) title, answer_count, post_type, parent_id, comment_count, score, tags);
			long *key = malloc(sizeof(long));

			*key = atol((char*) post_id);

			g_tree_insert(tree1, key, post);



			post2 = createPostsID(post_id, user_id, (char *) title, creation_date);
			long *key2 = malloc(sizeof(long));

			*key2 = atol((char*) post_id);

			g_tree_insert(tree2, key2, post2);


			curr = curr->next;
	}

}


int main(int argc, char **argv){

	char *docname;
	GTree	*tree;
	docname = "/home/helena/Desktop/Posts.xml";
	parsePosts(docname, tree);
	g_tree_foreach(tree,&(teste),NULL);
	return(1);

}



/*

//vai buscar id_tag, tagname, count e inserir numa hash
void parseTags (xmlDocPtr doc, GHashTable *hash_table){

	xmlNodePtr nod = xmlDocGetRootElement(doc);

	long id_tag;
	xmlChar tagname;
	long count_tags;

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
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			while((!xmlStrcmp(cur->name, (const xmlChar *)"/>")){
				id_tag = atoi(xmlGetProp(cur,(const xmlChar *)"Id"));
				tagname = xmlGetProp(cur,(const xmlChar *)"TagName");
			}
		}
		tag = createHashTag(tagname, id_tag);
	 	g_hash_table_insert(hash_table, id_tag, tag);

	}


}
*/
