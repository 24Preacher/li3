#include "postsID.h"
#include <glib.h>
#include "data.c"

/**
\struct Estrutura(AVL) que armazena os posts ordenados pelo identificador deste
@param id_post Identificador do post
@param id_user Identificador do utilizador
@param titulo  Título do post
@param data    Data do post
*/
struct Posts_id
{
	long id_post;
	long id_user;
	char* titulo;
	Data data_post;
}Posts_ID;

/**
\brief Função que cria uma estrutura dos posts
@param id_post Identificador do post
@param id_user Identificador do utilizador
@param titulo  Título do post
@param data    Data do post
returns A estrutura dos posts
*/
Posts_ID createPostsID (long post, long user, char* title, Data d){
	Posts_ID *r = g_tree_new((GCompareFunc)compareID(user,r->id_user));

	return r;
}

/**
\brief Função que busca o identificador do post
@param Estrutura dos posts
@returns O id do post
*/
long getPostId2 (Posts_ID posts){
	return posts->id_post;
}

/**
\brief Função que busca o identificador do utilizador
@param Estrutura dos posts
@returns O id do utilizador
*/
long getUserId2 (Posts_ID posts){
	return posts->id_user;
}

/**
\brief Função que busca o título do post
@param Estrutura dos posts
@returns Apontador para o título do post
*/
char* getTitle2 (Posts_ID posts){
	return mystrdup(posts->titulo);
}

/**
\brief Função que busca a data do post
@param Estrutura dos posts
@returns A data do post
*/
Data getDate2 (Posts_ID posts){
	return (cloneData(posts -> data_post));
}
