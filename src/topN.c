#include "topN.h"

struct topn {
  long id;
  int count;
};

TopN createTopN (long id, int c){
  TopN novo = malloc(sizeof(struct topn));
  novo->id = id;
  novo->count = c;

  return novo;
}

int getID_Top(TopN t){
  return t->id;
}

int getCount(TopN t){
  return t->count;
}

void setCount(TopN t, int c){
  t->count = c;
}

void freeTop (TopN t){
  free(t);
}

struct topArray {
  int size;
  int ocupados;
  TopN top[];
};

ArrayTop createArrayTop (int size){
  ArrayTop t = malloc(sizeof(struct topArray));
  t->size = size;
  t->ocupados = 0;
  t->top = malloc(sizeof(struct topn) * size);
  return t;
}

int getSizeTop (ArrayTop t){
	 return t->size;
}

int getOcupados2(ArrayTop t){
	return t->ocupados;
}

void setOcupados2(ArrayTop t, int o){
	t->ocupados = o;
}


TopN getTop (ArrayTop t ,int i){
  return t->top[i];
}

void setTop(ArrayTop t, TopN n, int i){
  t->top[i]= n;
}

void freeArrayTop(ArrayTop t){
  free(t);
}


void insereTop (ArrayTop t, TopN n){
  int i = 0;
  int tam = getSizeTop(t);
  int ocup = getOcupados(t);
  int cont = getCount(n);

  if(ocup == tam){
    TopN ultimo = getTop(t, tam);
    if (cont > getCount(ultimo)){
          while(i < tam && getCount(getTop(t, i)) >= cont) i++;
          pos = i;
          for(int j = ocup-1; j > i; j--){
            TopN anterior = getTop(t, j-1);
            setTop(t, n, j);
          }
          setTop(t, n, pos);
        }
  }
  else{
    while(i < ocup && getCount(getTop(t, i)) >= cont) i++;
    if(i == ocup) setTop(t, n, i);
    else{
      pos = i;
      for(int k = ocup; k > i; k--){
        TopN anterior = getTop(t, k-1);
        setTop(t, n, k);
      }
      setTop(t, n, pos);
      ocup++;
      setOcupados(t, ocup);
    }
  }
}

TopN cloneTopN(TopN t){
  TopN a = malloc(sizeof(struct topn));
  a->id = t->id;
  a->count = t->count;
  return a;
}

ArrayTop cloneArrayTop(ArrayTop t){
  ArrayTop a = malloc(sizeof(struct topArray));
  a->size = t->size;
  a->ocupados = t->ocupados;
  for(i=0;i<t->size;i++){
    a->top[i] = t->top[i]
  }
  return a;
}
