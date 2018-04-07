#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


//
void parseUsers (xmlNodePtr nodo, Users users){

	xmlDocPtr doc;
	xmlNodePtr cur;

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
	  if ((!xmlStrcmp(cur->name, (const xmlChar *)"id"))){
	    parseUsers (cur, doc);
	  }
		cur = cur->next;
	}




}

//fazer o mesmo
/*
void parsePosts (){

}


void parseTags (){

}

void parseVotes(){

}

*/
