#include "tags.h"

// Lista ligada para guardar as tags
/**
\struct Lista Ligada que armazena as Tags
@param nome Nome da Tag
@param *prox Apontador para a proxima Tag
*/
struct tags {
	char* nome;
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

/**
\brief Função que conta o número de Tags
@param String das Tags
@returns Número de tags
*/
int contaTags(char a[]){
	int i;
	int cont = 0;
	for (i = 0;a[i] == '\0'; i++){
		if (a[i] == '<')
		cont++;
	}
	return cont;
}

/**
\brief Função que passa de uma strinf para uma lista ligada de Tags
@param String das Tags
@returns Lista ligada das Tags
*/
Tags strToTags(char a[]){
	Tags t;
	char b[];
	int p = 0
	int cont = contaTags(a[])
	if (cont = 0){
	t = NULL;
	return t;
}
for (int i = 0; a[i] != '\0'; i++){
		if(a[i] == '<'){
			i++;
			while(a[i] != '>'){
				b[p] = a[i];
				p++;
				i++;
			}
			b[p] = '\0';
		}
		t = createTags(mystrdup(b));
		t = t -> prox;
		p = 0;
	}
}
return t;
}

int existeTag(char* tag, Tags t){

  if (!t) return 0;
  while(t != NULL){
    if(strcmp(tag, getNameTag(t)) == 0)
      return 1;
    else t = t->prox;
  }
  return 0;
}
