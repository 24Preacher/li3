#include "parser.h"


// vai ao users.xml buscar o id, reputation, displayname e aboutme
//usar um contador para ver o total de users
void parseUsers (xmlNodePtr doc, GHashTable *hash_table){

	long id;
	xmlChar bio;
	xmlChar name;
	int rep;
	int num_users;

	xmlNodePtr cur = xmlDocGetRootElement(doc)

//
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

/* inserir na hash
user = create_user;
gboolean g_hash_table_insert (hash_table, id, user);
*/
}


//vai buscar o id do post, PostTypeId, title, CreationDate, ParentId, OwnerUserId, AnswerCount, CommentCount, Score
void parsePosts (xmlDocPtr doc,   ){

	xmlNodePtr curr = xmlDocGetRootElement(doc)

	long post_id;
	int post_type;
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
while (cur != NULL) {
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {

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

		if ((!xmlStrcmp(post_type, (const xmlChar *)"1"))){
				answer_count=atoi(xmlGetProp(cur, (const xmlChar *)"AnswerCount"));
}
		else if ((!xmlStrcmp(post_type, (const xmlChar *)"2"))){
				parent_id = atoi(xmlGetProp(cur, (const xmlChar *)"ParentId"));


}




/*
//vai buscar id_tag, tagname, count
void parseTags (){

}


*/
