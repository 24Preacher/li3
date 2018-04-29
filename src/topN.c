#include "topN.h"

/**
\struct Definição de uma estrutura que guarda um identificador e um contador
@param id Identificador de um post/utilizador
@param count contador
*/
struct topn {
  long id;
  int count;
};

/**
\brief Função que cria uma célula com um identificador e um contador
@param id Identificador de um utilizador/post
@param c contador
returns O topN com o identificador e o contador
*/
TopN createTopN (long id, int c){
  TopN novo = malloc(sizeof(struct topn));
  novo->id = id;
  novo->count = c;

  return novo;
}

/**
\brief Função que busca o identificador dentro do TopN
@param t TopN
@returns identificador
*/
int getID_Top(TopN t){
  return t->id;
}

/**
\brief Função que atualiza o id dentro do TopN
@param t TopN
@param novo id
*/
void setID_Top(TopN t, long id){
  t->id = id;
}

/**
\brief Função que busca o contador dentro do TopN
@param t TopN
@returns contador
*/
int getCount(TopN t){
  return t->count;
}

/**
\brief Função que atualiza o contador dentro do TopN
@param t TopN
@param c novo valor do contador
*/
void setCount(TopN t, int c){
  t->count = c;
}

/**
\brief Função que liberta o TopN
@param t TopN
*/
void freeTop (TopN t){
  free(t);
}

/**
\struct Definição de um array de células que contém um identificador e uma contagem
@param size Tamanho do array
@param ocupados Número de células do array preenchidas
@param top Apontador para o ínicio do array
*/
struct topArray {
  int size;
  int ocupados;
  TopN * top;
};

/**
\brief Função que cria um array de células TopN
@param size Tamanho do array
@returns O ArrayTop
*/
ArrayTop createArrayTop (int size){
  ArrayTop t = malloc(sizeof(struct topArray));
  t->size = size;
  t->ocupados = 0;
  t->top = malloc(sizeof(struct topn) * size);
  return t;
}

/**
\brief Função que busca o tamanho do array
@param t ArrayTop
@returns tamanho do array
*/
int getSizeTop (ArrayTop t){
	 return t->size;
}

/**
\brief Função que busca o número de células preenchidas do array
@param t ArrayTop
@returns O número de células ocupadas do array
*/
int getOcupados2(ArrayTop t){
	return t->ocupados;
}

/**
\brief Função que atualiza o número de células preenchidas do array
@param t ArrayTop
@param O número atualizado de células ocupadas do array
*/
void setOcupados2(ArrayTop t, int o){
	t->ocupados = o;
}

/**
\brief Função que busca o TopN num certo índice
@param t ArrayTop
@param i índice do array
@returns O TopN na posição i do array
*/
TopN getTop (ArrayTop t ,int i){
  return cloneTopN(t->top[i]);
}

/**
\brief Função que atualiza o TopN num certo índice
@param t ArrayTop
@param i índice do array
*/
void setTop(ArrayTop t, TopN n, int i){
  t->top[i]= n;
}

/**
\brief Função que liberta o array
@param t ArrayTop
*/
void freeArrayTop(ArrayTop t){
  free(t);
}

/**
\brief Função que insere um TopN num ArrayTop, ordenado de forma decrescente do valor do contador
@param t ArrayTop
@param n TopN a inserir
*/
void insereTop (ArrayTop t, TopN n){
  int i = 0,pos;
  int tam = getSizeTop(t);
  int ocup = getOcupados2(t);
  int cont = getCount(n);

  if(ocup == tam){
    TopN ultimo = getTop(t, tam-1);
    if (cont > getCount(ultimo)){
          while(i < tam && getCount(getTop(t, i)) >= cont) i++;
          pos = i;
          for(int j = ocup-1; j > i; j--){
            TopN anterior = getTop(t, j-1);
            setTop(t, anterior, j);
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
        setTop(t, anterior, k);
      }
      setTop(t, n, pos);
      ocup++;
      setOcupados2(t, ocup);
    }
  }
}

/**
\brief Função que clona a estrutura dos TopN
@param t TopN a clonar
@returns A estrutura clonada dos TopN
*/
TopN cloneTopN(TopN t){
  TopN a = malloc(sizeof(struct topn));
  a->id = t->id;
  a->count = t->count;
  return a;
}

/**
\brief Função que clona a estrutura dos ArrayTop
@param t ArrayTop a clonar
@returns A estrutura clonada dos ArrayTop
*/
ArrayTop cloneArrayTop(ArrayTop t){
  ArrayTop a = malloc(sizeof(struct topArray));
  a->size = t->size;
  a->ocupados = t->ocupados;
  for(int i=0;i<t->size;i++){
    a->top[i] = t->top[i];
  }
  return a;
}

void insereResTop(ArrayTop t, TopN n){
  int i = 0, pos;
  int ocup = getOcupados2(t);

  while(i < ocup && getID_Top(n) > getID_Top(getTop(t,i))) i++;
    if (i == ocup) setTop(t, n, i);
    else{
      pos = i;
      for(int k = ocup; k > i; k--){
        TopN anterior = getTop(t, k-1);
        setTop(t, anterior, k);
      }
      setTop(t, n, pos);
      ocup++;
      setOcupados2(t, ocup);
    }
}

void alteraCount(ArrayTop t, long id){
  int i = 0;
  int tam = getSizeTop(t);

  while(i < tam && id > getID_Top(getTop(t,i))) i++;

  if (id == getID_Top(getTop(t,i))) {
      int c = getCount(getTop(t,i));
      c++;
      setCount(getTop(t,i), c);
    }
}

struct auxdata{
  Data data;
  long id;
};

AuxData createAuxData(Data d, long p){
  AuxData nova = malloc(sizeof(struct auxdata));
  nova->data = cloneData(d);
  nova->id = p;
  return nova;
}

Data getData_Aux (AuxData c){
  return cloneData(c->data);
}

long getId_Aux (AuxData c){
  return c->id;
}

void freeAuxData(AuxData c){
  free(c);
}

struct arraydata{
  int size;
  int ocupados;
  AuxData *p;
};

ArrayData createArrayData (int size){
  if (size <= 0) return NULL;
  ArrayData novo = malloc(sizeof(struct arraydata));
  novo->size = size;
  novo->ocupados = 0;
  novo->p = malloc((sizeof(struct auxdata)) * size);
  return novo;
}

int getSizeArrayData (ArrayData c){
  return c->size;
}

int getOcupadosData (ArrayData c){
  return c->ocupados;
}

void setOcupadosData (ArrayData c, int o){
  c->ocupados = o;
}

AuxData getAuxData (ArrayData c, int i){
  return c->p[i];
}

void setAuxData (ArrayData c, AuxData nova, int i){
  c->p[i] = nova;
}

void freeArrayData (ArrayData c){
  for (int i = 0; i < getSizeArrayData(c); i++)
    freeAuxData(getAuxData(c, i));
}


void inserePelaData(ArrayData c, AuxData nova){
  int i = 0,pos;
  int tam = getSizeArrayData(c);
  int ocup = getOcupadosData(c);
  Data d = getData_Aux(nova);

  if(ocup == tam){
    AuxData ultimo = getAuxData(c, tam-1);
    if(compareMyData(getData_Aux(ultimo), d) == -1){
      while(i < tam && compareMyData(getData_Aux(getAuxData(c, i)), d) == 1) i++;
      pos = i;
      for(int j = ocup-1; j > i; j--){
        AuxData ant = getAuxData(c, j-1);
        setAuxData(c, ant, j);
      }
      setAuxData(c, nova, pos);
    }
  }
  else{
  while(i < ocup && compareMyData(getData_Aux(getAuxData(c, i)), d) == 1) i++;
  if (i == ocup) setAuxData(c, nova, i);
  else{
    pos = i;
    for(int k = ocup; k > i; k--){
      AuxData ant = getAuxData(c, k-1);
      setAuxData(c, ant, k);
    }
    setAuxData(c, nova, pos);
    ocup++;
    setOcupadosData(c, ocup);
    }
  }
}
