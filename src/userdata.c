#include "userdata.h"

/**struct Estrutura que armazena duas datas (inicial e final) e um array de tamanho N
@param inicio Data de inicio
@param fim    Data de fim
@param t      Array com tamanho N para os top N elementos
*/
struct user_dataTop {
  Date inicio;
  Date fim;
  ArrayTop t;
};

/**
\brief Função que cria uma estrutura dos user_dataTop
@param i Data de inicio
@param f Data de fim
@param t Array com tamanho N para os top N elementos
returns A estrutura para os top N
*/
UserDataTop createUserDataTop (Date i, Date f, ArrayTop t){
  UserDataTop novo = malloc(sizeof(struct user_dataTop));
  novo->inicio = i;
  novo->fim = f;
  novo->t = cloneArrayTop(t);

  return novo;
}

/**
\brief Função que busca a data de inico
@param Estrutura dos top N
returns A data de inicio
*/
Date getDataInicioTop(UserDataTop d){
  return d->inicio;
}

/**
\brief Função que busca a data de fim
@param Estrutura dos top N
returns A data de fim
*/
Date getDataFimTop(UserDataTop d){
  return d->fim;
}

/**
\brief Função que busca o Array dos Top N
@param Estrutura dos top N
returns O array dos top N
*/
ArrayTop getArray(UserDataTop d){
  return cloneArrayTop(d->t);
}

/**
\brief Função que atualiza o Array da estrutura Top N
@param Estrutura dos top N
@param Novo Array top N
returns Estrutura dos top N atualizada
*/
void setArray(UserDataTop d, ArrayTop n){
  d->t = cloneArrayTop(n);
}

/**
\brief Função que liberta a estrutura
@param Estrutura dos top N
*/
void freeUserDataTop(UserDataTop d){
  free(d);
}

/**struct Estrutura que armazena duas datas (inicial e final) e um par para o numero total de respostas e perguntas num intervalo de tempo
@param inicio Data de inicio
@param fim    Data de fim
@param par    Par de Longs
*/
struct user_dataPar {
  Date inicio;
  Date fim;
  LONG_pair par;
};

/**
\brief Função que cria uma estrutura dos user_dataPar
@param i Data de inicio
@param f Data de fim
@param par Par com dois Longs
returns A estrutura para o numero total de respostas e perguntas
*/
UserDataPar createUserDataPar (Date i, Date f,  LONG_pair par){
  UserDataPar novo = malloc(sizeof(struct user_dataPar));
  novo->inicio = i;
  novo->fim = f;
  novo->par = create_long_pair(get_fst_long(par), get_snd_long(par));

  return novo;
}

/**
\brief Função que busca a Data de inicio
@param Estrututa das Respostas e perguntas
@returns Data de Inicio
*/
Date getDataInicioPar(UserDataPar d){
  return d->inicio;
}

/**
\brief Função que busca a Data de fim
@param Estrututa das Respostas e perguntas
@returns Data de Fim
*/
Date getDataFimPar(UserDataPar d){
  return d->fim;
}

/**
\brief Função que busca o par de Respostas e perguntas
@param Estrututa das Respostas e Perguntas
@returns Apontador para o numero de Respostas e Perguntas
*/
LONG_pair getPar(UserDataPar d){
  LONG_pair novo = malloc(sizeof(struct long_pair));
  novo->fst = get_fst_long(d->par);
  novo->snd = get_snd_long(d->par);
  return novo;
}

/**
\brief Função que liberta a estrutura do par das Respostas e perguntas
@Estrutura das Respostas e Perguntas
*/
void freeUserDataPar(UserDataPar d){
  free(d);
}


struct user_dataTitle {
  char* pal;
  Lista l;
};

UserDataTitle createUserDataTitle (char* pal, Lista l){
  UserDataTitle novo = malloc(sizeof(struct user_dataTitle));
  novo->pal = mystrdup(pal);
  novo->l = l;
  return novo;
}

char* getPal (UserDataTitle d){
	return mystrdup(d->pal);
}

Lista getListaU (UserDataTitle d){
	return cloneLista(d->l);
}

void setListaU (UserDataTitle d, Lista l){
  d->l = l;
}

void freeUserDataTitle(UserDataTitle d){
  if(d->l != NULL)
    free(d->l)
  free(d);
}

struct user_dataRes {
  Data d;
  int rep;
  long id;
  int num_res;
  TopN melhor;
};

UserDataRes createUserDataRes (Data i, int rep, long id, int r, TopN t){
  UserDataRes novo = malloc(sizeof(struct user_dataRes));
  novo->d = cloneData(i);
  novo->rep = rep;
  novo->id = id;
  novo->num_res = res;
  novo->melhor = cloneTopN(t);
  return novo;
}

Data getDataPergunta (UserDataRes u){
	return cloneData(u->d);
}

int getRepU (UserDataRes u){
	return u->rep;
}

long getIdPergunta (UserDataRes u){
  return u->id;
}

int getAnswersRes (UserDataRes u){
  return u->num_res;
}

void setAnswers (UserDataRes u, int r){
  u->num_res = r;
}

TopN getTopU (UserDataRes u){
  return cloneTopN(u->melhor);
}

void setTopU (UserDataRes u, TopN n){
  u->melhor = n;
}

void freeUserDataRes(UserDataRes u){
  free (u);
}

struct user_dataTag {
  Date inicio;
  Date fim;
  char* nome;
  Lista l;
};

UserDataTag createUserDataTag (Date i, Date f,  char* tag, Lista l){
  UserDataPar novo = malloc(sizeof(struct user_dataPar));
  novo->inicio = i;
  novo->fim = f;
  novo->nome = mystrdup(tag);
  novo->l = l;
  return novo;
}

Date getDataInicioTag(UserDataTag d){
  return d->inicio;
}

Date getDataFimTag(UserDataTag d){
  return d->fim;
}

char* getTagU (UserDataTag d){
	return mystrdup(d->nome);
}

Lista getListaUTag (UserDataTag d){
	return cloneLista(d->l);
}

void setListaUTag (UserDataTag d, Lista l){
  d->l = l;
}

void freeUserDataTag(UserDataTag d){
  if(d->l != NULL)
    free(d->l)
  free(d);
}
