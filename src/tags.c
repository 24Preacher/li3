#include "tags.h"

// Lista ligada para guardar as tags
struct tags {
	char* nome;
	//long id_tag;
	//int count;
	struct tags *prox;
} Tags;

Tags createTags (char* nome){
	Tags t = malloc(sizeof(struct tags));
	t->nome = nome;
	t->prox = NULL;

	return t;
}

char* getNameTag (Tags t){
	return mystrdup(t->nome);
}
/*
long getIdTag (Tags t){
	return t->id_tag;
} */

void freeTags (Tags t){
	 if (t)
	 	free(t);
}

Tags cloneTags (Tags t){
	Tags r = malloc(sizeof(struct tags));
	r -> nome = mystrdup(t -> nome);
	return r;
}
