#include "parser.h"


// vai ao users.xml buscar o id, reputation, displayname e aboutme
//usar um contador para ver o total de users
void parseUsers (xmlNodePtr nodo, Users users){

	xmlDocPtr doc;
	xmlNodePtr cur;

	long id;
	xmlChar bio;
	xmlChar name;
	int rep;
	int num_users;


	doc = xmlParseFile(users);
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
			return;
	}

  cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}


	while (cur != NULL) {

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			while((!xmlStrcmp(cur->name, (const xmlChar *)"/>")){
				id = atoi(xmlGetProp(cur, (long *)"Id"));
				bio = xmlGetProp(cur, (xmlChar *)"AboutMe");
				name = xmlGetProp(cur, (xmlChar *)"DisplayName");
				rep = atoi(xmlGetProp(cur, (char *)"Reputation"));

				cur = cur->next;
				num_users ++;
			}
		}

}


/*
void parsePosts (){

}



void parseTags (){

}


*/
