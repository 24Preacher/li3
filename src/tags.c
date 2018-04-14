#include "tags.h"

// Lista ligada para guardar as tags
/**
\struct Lista Ligada que armazena as Tags
@param nome Nome da Tag
@param id_tag Identificador da Tag
@param count Contador da Tags
@param *prox Apontador para a proxima Tag
*/
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

/**
\brief Função que clona a estrutura das Tags
@param Estrutura das Tags
@returns A estrutura clonada das Tags
*/
Tags cloneTags (Tags t){
	Tags r = malloc(sizeof(struct tags));
	r -> nome = mystrdup(t -> nome);
	return r;
}
