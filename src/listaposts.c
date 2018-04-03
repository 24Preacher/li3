#include "struct.h"
#include <glib.h>
#include "date.c"

struct lligada {
	long post_id;
	struct lligada *prox;
}Lista;

struct lposts {
  int size;
  Lista lposts[];
}Lista_Posts;

Lista createLista (long id){
  Lista l = malloc(sizeof (struct lligada));
  id_post = id;
  l->prox = NULL;
}

Lista addPost (Lista l, long id){
  Lista novo = createLista(id);
  novo->prox = l;
  l = novo;
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
