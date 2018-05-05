#include "tags.h"

/**
\struct Lista Ligada que armazena as Tags
@param nome Nome da Tag
@param *prox Apontador para a proxima Tag
*/
struct tags {
	char* nome;
	struct tags *prox;
};

/**
\brief Função que cria a estrutura das Tags
@param nome Nome da tag
@returns A estrutura das Tags
*/
Tags createTags (char* nome){
	Tags t = malloc(sizeof(struct tags));
	t->nome = mystrdup(nome);
	t->prox = NULL;

	return t;
}

/**
\brief Função que adiciona uma tag
@param t Lista de Tags
@param tag Tag a adicionar
@returns A estrutura das Tags
*/
Tags addTag(Tags t, char* tag){
    Tags novo = createTags(tag);
    novo->prox = t;
    t = novo;
    return t;
}

/**
\brief Função que busca o nome da tag
@param t Estrutura das Tags
@returns O nome da tag
*/
char* getNameTag (Tags t){
	return mystrdup(t->nome);
}

/**
\brief Função que liberta a estrutura das Tags
@param t Estrutura das Tags
*/
void freeTags (Tags t){
	 if (t)
	 	free(t);
}

/**
\brief Função que clona a estrutura das Tags
@param t Estrutura das Tags
@returns A estrutura clonada das Tags
*/
Tags cloneTags (Tags t){
	Tags r = malloc(sizeof(struct tags));
	r -> nome = mystrdup(t -> nome);
	return r;
}

/**
\brief Função que passa de uma string para uma lista ligada de Tags
@param a String das Tags
@returns Lista ligada das Tags
*/
Tags strToTags(char* a){
    Tags t;
    char* b;
    int i,j, k = 0;

    if(a == NULL) return NULL;

    for(i = 0; a[i] != '\0'; i++){
        if(a[i] == '>');
           b = malloc((i-k)*sizeof(char));
        for(j = 0; j < (i-k-1); j++)
            b[j] = a[j+k+1];
        b[j] = '\0';

        t = addTag(t, b);
        k = i+1;
    }
    return t;
}

/**
\brief Função que verifica se uma tag existe numa lista ligada de tags
@param tag Tag a procurar
@param t Estrutura das Tags
@returns 1 se a tag existir, 0 caso contrário
*/
int existeTag(char* tag, Tags t){

  if (!t) return 0;
  while(t != NULL){
    if(strcmp(tag, getNameTag(t)) == 0)
      return 1;
    else t = t->prox;
  }
  return 0;
}
