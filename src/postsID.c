#include "postsID.h"
#include <glib.h>
#include "data.c"

/**
\struct Estrutura(AVL) que armazena os posts ordenados pelo identificador deste
@param id_post Identificador do post
@param id_user Identificador do utilizador
@param titulo  Título do post
@param data    Data do post
@param num_respostas Número de respostas do post
@param post_type Tipo do post
@param parent_id Identificador do pai
@param num_comentarios Número de comentarios do post
@param score Score do post
@param tags Tags presentes no post
*/
struct Posts_id
{
	long id_post;
	long id_user;
	char* titulo;
	Data data_post;
	int num_respostas;
	short post_type; //1 - pergunta, 2 - resposta
	long parent_id;
	int num_comentarios;
	int score;
	Tags tags;
}Posts_ID;

/**
\brief Função que cria uma estrutura dos posts
@param id_post Identificador do post
@param id_user Identificador do utilizador
@param titulo  Título do post
@param data    Data do post
returns A estrutura dos posts
*/
Posts_ID createPostsID (long post, long user, char* title, Data d, int respostas,
		short ptype, long parent, int com, int score, Tags t){
	Posts_ID *r = g_tree_new(&compareID);

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

/**
\brief Função que busca o número de resposta do post
@param Estrutura dos posts
@returns O número de respostas
*/
int getAnswers2 (Posts_ID posts){
	return posts->num_respostas;
}

/**
\brief Função que busca o tipo de post
@param Estrutura dos posts
@returns O tipo de post
*/
short getPostType2 (Posts_ID posts){
	return posts->post_type;
}

/**
\brief Função que busca o id do pai caso exista
@param Estrutura dos posts
@returns O id do pai
*/
long getParentId2 (Posts_ID posts){
	return posts->parent_id;
}

/**
\brief Função que busca o número de comentarios
@param Estrutura dos posts
@returns O número de comentarios
*/
int getComments2 (Posts_ID posts){
	return posts->num_comentarios;
}

/**
\brief Função que busca o score de um post
@param Estrutura dos posts
@returns O score do post
*/
int getScore2 (Posts_ID posts){
	return posts->score;
}

/**
\brief Função que busca as Tags de um post
@param Estrutura dos posts
@returns Apontador para as Tags do post
*/
Tags getTags2 (Posts_ID posts){
	return (cloneTags(posts -> tags));
}


void freePostsID (Posts_D posts){
	 if (posts)
	 	free(posts);
}

Posts_ID clonePostsID (Posts_ID posts){
	Posts_ID p = malloc(sizeof(struct Posts_id));
	p->id_post = posts->id_post;
	p->id_user = posts->id_user;
	p->id_titulo = posts->titulo;
	p->data_post = posts -> data_post;
	p->num_respostas = posts->num_respostas;
	p->post_type = posts->post_type;
	p->parent_id = posts->parent_id;
	p->num_comentarios = posts->num_comentarios;
	p->score = posts->score;
	p->tags = posts -> tags;
	return p;
}
