#include "postsID.h"

/**
\struct Estrutura(AVL) que armazena os posts ordenados pelo identificador deste
@param id_post Identificador do post
@param id_user Identificador do utilizador
@param titulo  Título do post
@param data    Data do post
@param post_type Tipo do post
@param parent_id Identificador do pai

*/
struct Posts_id
{
	long id_post;
	long id_user;
	char* titulo;
	Data data_post;
	int post_type;
	long parent_id;
};

/**
\brief Função de comparação de ids para criar a AVL
@param a Valor
@param b Valor a comparar
@returns 0 se forem iguais, 1 se a for maior que b e -1 caso contrário
*/
gint compareID(gconstpointer a, gconstpointer b){
    long id1 = *(long*) a;
    long id2 = *(long*) b;

 if(id1 > id2){
         return 1;
			 }
     else if (id1 < id2){
        return -1;
			}
   else return 0;
}


/**
\brief Função que cria uma estrutura dos posts
@param post Identificador do post
@param user Identificador do utilizador
@param title  Título do post
@param data    Data do post
@param ptype Tipo do post
@param parent Identificador do pai
returns A estrutura dos posts
*/
Posts_ID createPostsID (long post, long user, char* title, Data d, int ptype,
	long parent){
	Posts_ID r = malloc(sizeof(struct Posts_id));
	r->id_post = post;
	r->id_user = user;
	r->titulo = mystrdup(title);
	r->data_post = d;
	r->post_type = ptype;
	r->parent_id = parent;

	return r;
}

/**
\brief Função que busca o identificador do post
@param posts Estrutura dos posts
@returns O id do post
*/
long getPostId2 (Posts_ID posts){
	if (!posts){
		return -2;
	}
	return posts->id_post;
}

/**
\brief Função que busca o identificador do utilizador
@param posts Estrutura dos posts
@returns O id do utilizador
*/
long getUserId2 (Posts_ID posts){
	return posts->id_user;
}

/**
\brief Função que busca o título do post
@param posts Estrutura dos posts
@returns Apontador para o título do post
*/
char* getTitle2 (Posts_ID posts){
	return mystrdup(posts->titulo);
}

/**
\brief Função que busca a data do post
@param posts Estrutura dos posts
@returns A data do post
*/
Data getDate2 (Posts_ID posts){
	return (cloneData(posts -> data_post));
}

/**
\brief Função que busca o tipo de post
@param posts Estrutura dos posts
@returns O tipo de post
*/
int getPostType2 (Posts_ID posts){
	return posts->post_type;
}

/**
\brief Função que busca o id do pai caso exista
@param posts Estrutura dos posts
@returns O id do pai
*/
long getParentId2 (Posts_ID posts){
	return posts->parent_id;
}


/**
\brief Função que liberta a estrutura dos Posts_ID
@param posts Estrutura dos posts
*/
void freePostsID (gpointer posts){
	 g_tree_destroy((GTree*)posts);
}

/**
\brief Função que clona a estrutura dos Posts_ID
@param posts Estrutura dos Posts_ID a clonar
@returns A estrutura clonada dos Posts_ID
*/
Posts_ID clonePostsID (Posts_ID posts){
	Posts_ID p = malloc(sizeof(struct Posts_id));
	p->id_post = posts->id_post;
	p->id_user = posts->id_user;
	p->titulo = posts->titulo;
	p->data_post = posts -> data_post;
	p->post_type = posts->post_type;
	p->parent_id = posts->parent_id;
	return p;
}
