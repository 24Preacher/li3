#include "parser.h"



/**
\brief Função que faz parse do ficheiro xml dos Users e os insere numa Tabela de Hash
@param doc Documento XML
@param hash_table Tabela de hash onde se vai inserir a informação dos utilizadores
@return Número de utilizadores inseridos
*/
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

/**
\brief Função que faz parse do ficheiro xml dos Posts e os insere em duas AVL
@param doc Documento XML
@param tree1 AVL onde se vai inserir a informação dos posts ordenada pelo id
@param tree2 AVL onde se vai inserir a informação dos posts ordenada pela data
*/
void parsePosts (xmlDocPtr doc, GTree *tree1, GTree *tree2){


	xmlNodePtr curr = xmlDocGetRootElement(doc);

	xmlChar * keyxml;
	long post_id;
  int ptype;
	char * title;
	Tags tags = NULL;
	Data creation_date = NULL;
	long user_id;
	long parent_id;
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

				keyxml = (xmlGetProp(curr,(const xmlChar *)"Title"));
				title = keyxml ? mystrdup((char *) keyxml) : NULL;
				if (keyxml)
					xmlFree(keyxml);

				Posts_ID post1 = createPostsID(post_id,user_id,title,creation_date,ptype,parent_id);
				Posts_D post2 = createPostsD(creation_date,user_id,post_id,title,answer_count,ptype,parent_id,comment_count,score,tags);


				long * key = malloc(sizeof(long));
				*key = post_id;

				g_tree_insert(tree1, key, post1);
				g_tree_insert(tree2, creation_date, post2);

				if (title)
					free(title);


		}
			curr = curr->next;
    }
}


/**
\brief Função que faz parse dos ficheiros xml
@param docusers Documento XML dos Users
@param docposts Documento XML dos Posts
@param hash_users Tabela de hash onde se vai inserir a informação dos utilizadores
@param tree1 AVL onde se vai inserir a informação dos posts ordenada pelo id
@param tree2 AVL onde se vai inserir a informação dos posts ordenada pela data
@returns Número de utilizadores
*/
int parseDoc(char *docusers, char *docposts, GHashTable *hash_users, GTree *tree1, GTree *tree2){
	xmlDocPtr doc1, doc2;
	xmlNodePtr cur1, cur2;

	doc1 = xmlParseFile(docusers);
	doc2 = xmlParseFile(docposts);


	if (doc1 == NULL || doc2==NULL) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return 0;
	}

	cur1 = xmlDocGetRootElement(doc1);
 	cur2 = xmlDocGetRootElement(doc2);

	if (cur1 == NULL || cur2 == NULL) {
		fprintf(stderr,"empty document\n");

		xmlFreeDoc(doc1);
		xmlFreeDoc(doc2);
	return 0;
	}


	parsePosts(doc2, tree1, tree2);
     printf("parse dos posts feito\n");

int num_users = parseUsers(doc1, hash_users);
     printf("parse dos users feito\n");


  xmlFreeDoc(doc1);
	xmlFreeDoc(doc2);
	return num_users;

}
