#include "listaposts.h"
#include <stdlib.h>

struct lligada {
	long id_post;
	struct lligada *prox;
}Lista;

typedef struct lposts {
  int size;
  Lista lposts[];
}Lista_Posts;

Lista createLista (long id){
  Lista l = malloc(sizeof (struct lligada));
  id_post = id;
  (*l)->prox = NULL;

	return l;
}

Lista addPost (Lista l, long id){
  Lista novo = createLista(id);
  novo->prox = l;
  l = novo;

	return novo;
}

Lista createLPosts (int size){
  if (size <= 0)
    return NULL;
  Lista_Posts l = malloc (sizeof(Lista_Posts));
  l->size = size;
  l->lposts = malloc(sizeof(Lista)* size);
  return l;
}

long getPostId_L (Lista l){
  return l->post_id;
}

Lista getListaPosts (Lista_Posts l){
  return l->lposts;
}


void freeListaPosts (Lista_Posts l){
  if (l){
    free(l->lposts);
    free(l);
  }
}
