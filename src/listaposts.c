#include "listaposts.h"
#include <stdlib.h>

/**
\struct Definição de listas ligadas de ids de posts
@param id_post Identificador do utilizador
*/
struct lligada {
	long id_post;
	struct lligada *prox;
}Lista;

/**
\struct Estrutura, array de listas ligadas, que guarda os id dos posts de cada utilizador.
@param size Tamanho da lista ligada -- ta mal, ver depois
@param lposts array de listas
*/
struct lposts {
  int size;
  Lista lposts[];
}Lista_Posts;

/**
\brief Função que cria uma lista
@param id_post Identificador do post
returns A lista com o id
*/
Lista createLista (long id){
  Lista l = malloc(sizeof (struct lligada));
  id_post = id;
  (*l)->prox = NULL;

	return l;
}

/**
\brief Função que adiciona um id à cabeça da lista
@param id_post Identificador do post
returns A lista com o id adicionado
*/
Lista addPost (Lista l, long id){
  Lista novo = createLista(id);
  novo->prox = l;
  l = novo;

	return novo;
}

/**
\brief Função que aloca memória para o array de listas
@param size Tamanho do array
returns O array de listas
*/
Lista_Posts createLPosts (int size){
  if (size <= 0)
    return NULL;
  Lista_Posts l = malloc (sizeof(Lista_Posts));
  l->size = size;
  l->lposts = malloc(sizeof(Lista)* size);
  return l;
}

/**
\brief Função que busca o identificador do post
@param l lista dos identificadores de posts
returns O id do post
*/
long getPostId_L (Lista l){
  return l->post_id;
}

/**
\brief Função que busca o identificador do post
@param l array de listas
@param i índice do array
returns A lista que se encontrava no array i
*/
Lista getListaPosts (Lista_Posts l, int i){
  return l->lposts[i];
}

/**
\brief Função que liberta o array de listas
@param l array de listas
*/
void freeListaPosts (Lista_Posts l){
  if (l){
    free(l->lposts);
    free(l);
  }
}
