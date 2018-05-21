#include "userdata.h"

/**
\struct Estrutura que armazena duas datas (inicial e final) e um array de tamanho N
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
@returns A estrutura para os top N
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
@param d Estrutura dos top N
@returns A data de inicio
*/
Date getDataInicioTop(UserDataTop d){
  return d->inicio;
}

/**
\brief Função que busca a data de fim
@param d Estrutura dos top N
@returns A data de fim
*/
Date getDataFimTop(UserDataTop d){
  return d->fim;
}

/**
\brief Função que busca o Array dos Top N
@param d Estrutura dos top N
@returns O array dos top N
*/
ArrayTop getArray(UserDataTop d){
  return cloneArrayTop(d->t);
}

/**
\brief Função que atualiza o Array da estrutura Top N
@param d Estrutura dos top N
@param Novo Array top N
*/
void setArray(UserDataTop d, ArrayTop n){
  d->t = n;
}

/**
\brief Função que liberta a estrutura
@param d Estrutura dos top N
*/
void freeUserDataTop(UserDataTop d){
  free(d);
}

/**
\struct Estrutura que armazena duas datas (inicial e final) e um par para o numero total de respostas e perguntas num intervalo de tempo
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
@returns A estrutura para o numero total de respostas e perguntas
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
@param d Estrutura das Respostas e perguntas
@returns Data de Inicio
*/
Date getDataInicioPar(UserDataPar d){
  return d->inicio;
}

/**
\brief Função que busca a Data de fim
@param d Estrutura das Respostas e perguntas
@returns Data de Fim
*/
Date getDataFimPar(UserDataPar d){
  return d->fim;
}

/**
\brief Função que busca o par de Respostas e perguntas
@param d Estrutura das Respostas e Perguntas
@returns Par com numero de Respostas e Perguntas
*/
LONG_pair getPar(UserDataPar d){
   long fst = get_fst_long(d->par);
   long snd = get_snd_long(d->par);
  LONG_pair novo = create_long_pair(fst, snd);
  return novo;
}

/**
\brief Função que liberta a estrutura do par das Respostas e perguntas
@param d Estrutura das Respostas e Perguntas
*/
void freeUserDataPar(UserDataPar d){
  free(d);
}

/**
\struct Estrutura com uma palavra e a lista com o ID dos titulos que contém a palavra
@param pal  Palavra
@param l Lista de Longs com os ID's dos titulos que contém a palavra
*/
struct user_dataTitle {
  char* pal;
  Lista l;
};

/**
\brief Função que cria estrutura com a String e a Lista de ID's
@param pal String da palavra
@param l Lista com os IDs dos titulos
@returns A estrutura da String com a Lista de ID's
*/
UserDataTitle createUserDataTitle (char* pal, Lista l){
  UserDataTitle novo = malloc(sizeof(struct user_dataTitle));
  novo->pal = mystrdup(pal);
  novo->l = l;
  return novo;
}

/**
\brief Função que busca a String
@param d Estrutura da String com os ID's dos titulos
@returns String da palavra
*/
char* getPal (UserDataTitle d){
	return mystrdup(d->pal);
}

/**
\brief Função que busca a Lista de ID's dos titulos
@param d Estrutura da String com os ID's dos titulos
@returns Lista de ID's dos titulos
*/
Lista getListaU (UserDataTitle d){
	return cloneLista(d->l);
}

/**
\brief Função que atualiza a Lista de ID's
@param d Estrutura da String com os ID's dos titulos
@param Nova Lista de ID's
*/
void setListaU (UserDataTitle d, Lista l){
  d->l = l;
}

/**
\brief Função que liberta a Estrutura da String e Lista dos ID's
@param d Estrutura da String com os ID's dos titulos
*/
void freeUserDataTitle(UserDataTitle d){
  if(d->l != NULL)
    free(d->l);
  free(d);
}

/**
\struct Estrutura com a data, reputação, id de user, número de resposta e id das top N Respostas
@param d Data
@param rep reputação
@param id Identificador da Pergunta
@param num_res Numero de Respostas
@param Estrutura dos TopN
*/
struct user_dataRes {
  Data d;
  int rep;
  long id;
  int num_res;
  TopN melhor;
};

/**
\brief Função que cria a estrutura para as Melhores Respostas
@param d Data
@param rep reputação
@param id Identificador da Pergunta
@param num_res Numero de Respostas
@param melhor Estrutura TopN com as melhores Respostas
@returns Estrutura das Melhores respostas
*/
UserDataRes createUserDataRes (Data i, int rep, long id, int r, TopN t){
  UserDataRes novo = malloc(sizeof(struct user_dataRes));
  novo->d = cloneData(i);
  novo->rep = rep;
  novo->id = id;
  novo->num_res = r;
  novo->melhor = cloneTopN(t);
  return novo;
}

/**
\brief Função que busca a data de uma pergunta
@param u Estrutura das Melhores Respostas
@returns Data de criação da pergunta
*/
Data getDataPergunta (UserDataRes u){
	return cloneData(u->d);
}

/**
\brief Função que busca a reputação do user
@param u Estrutura das Melhores Respostas
@returns Reputação do User
*/
int getRepU (UserDataRes u){
	return u->rep;
}

/**
\brief Função que busca o ID da pergunta
@param u Estrutura das Melhores Respostas
@returns ID da pergunta
*/
long getIdPergunta (UserDataRes u){
  return u->id;
}

/**
\brief Função que busca o numero de resposta a uma pergunta
@param u Estrutura das Melhores Respostas
@returns Número de Respostas
*/
int getAnswersRes (UserDataRes u){
  return u->num_res;
}

/**
\brief Função que atualiza o numero de respostas a uma pergunta
@param u Estrutura das Melhores Respostas
@param r Número de Respostas
*/
void setAnswers (UserDataRes u, int r){
  u->num_res = r;
}

/**
\brief Função que busca o TopN respostas
@param u Estrutura das Melhores Respostas
@returns TopN Respostas
*/
TopN getTopU (UserDataRes u){
  return cloneTopN(u->melhor);
}

/**
\brief Função que atualiza o topN respostas
@param u Estrutura das Melhores Respostas
@param n TopN respostas
*/
void setTopU (UserDataRes u, TopN n){
  u->melhor = n;
}

/**
\brief Função que liberta a Estrutura das melhores respostas
@param u Estrutura das Melhores Respostas
*/
void freeUserDataRes(UserDataRes u){
  free (u);
}

/**
\struct Estrutura com o intervalo de tempo, String com a Tag e lista com os ID's das perguntas
@param inicio Data inicial
@param fim Data final
@param nome String com nome da Tag
@param l Lista com ID dos titulos
*/
struct user_dataTag {
  Date inicio;
  Date fim;
  char* nome;
  Lista l;
};

/**
\brief Função que cria a Estrutura com o intervalo de tempo, String com a Tag e lista com os ID's das perguntas
@param inicio Data inicial
@param fim Data final
@param nome String com nome da Tag
@param l Lista com ID dos titulos
@returns Estrutura com a Tag e lista de ID de titulos que contem essa Tag
*/
UserDataTag createUserDataTag (Date i, Date f,  char* tag, Lista l){
  UserDataTag novo = malloc(sizeof(struct user_dataPar));
  novo->inicio = i;
  novo->fim = f;
  novo->nome = mystrdup(tag);
  novo->l = l;
  return novo;
}

/**
\brief Função que busca a data de inico
@param d Estrutura das Tags e lista de ID's de titulos
@returns A data de inicio
*/
Date getDataInicioTag(UserDataTag d){
  return d->inicio;
}

/**
\brief Função que busca a data de fim
@param d Estrutura das Tags e lista de ID's de titulos
@returns A data de fim
*/
Date getDataFimTag(UserDataTag d){
  return d->fim;
}

/**
\brief Função que busca a String da Tag
@param d Estrutura das Tags e lista de ID's de titulos
@returns String com a Tag
*/
char* getTagU (UserDataTag d){
	return mystrdup(d->nome);
}

/**
\brief Função que busca lista de ID's dos titulos
@param d Estrutura das Tags e lista de ID's de titulos
@returns Lista de ID's dos titulos
*/
Lista getListaUTag (UserDataTag d){
	return cloneLista(d->l);
}
/**
\brief Função que atualiza a lista de ID's dos titulos
@param d Estrutura das Tags e lista de ID's de titulos
@param l Nova Lista de ID's de titulos
*/
void setListaUTag (UserDataTag d, Lista l){
  d->l = l;
}
/**
\brief Função que liberta a estrutura
@param d Estrutura das Tags e lista de ID's de titulos
*/
void freeUserDataTag(UserDataTag d){
  if(d->l != NULL)
    free(d->l);
  free(d);
}
