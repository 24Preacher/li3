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
	long id_tag;
	int count;
	struct tags *prox;
} Tags;

/**
\brief Função que cria uma estrutura das Tags
@param nome Nome da Tag
@param id_tag Identificador da Tag
@param count Contador da Tags
@param *prox Apontador para a proxima Tag
*/
Tags createTags (char* nome, long id, int c){
	Tags t = malloc(sizeof(struct tags));
	t->nome = nome;
	t->id_tag = id;
	t->count = c;
	t->prox = NULL;

	return t;
}

/**
\brief Função que busca o nome da Tag
@param Estrutura das Tags
@returns O nome da Tag
*/
char* getNameTag (Tags t){
	return mystrdup(t->nome);
}

/**
\brief Função que busca o Identificador da Tag
@param Estrutura das Tags
@returns O ID da Tag
*/
long getIdTag (Tags t){
	return t->id_tag;
}

/**
\brief Função que busca o numero de vezes que uma Tag aparece
@param Estrutura das Tags
@returns O contador das Tags
*/
long getCountTags (Tags t){
	return t->count;
}


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
		mystrdup(r -> nome)
		r -> id_tag;
		r -> count;
}
