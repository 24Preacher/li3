#include "userdata.h"

//structs auxiliar para o foreach
struct user_dataTop {
  Date inicio;
  Date fim;
  ArrayTop t;
};


UserDataTop createUserDataTop (Date i, Date f, ArrayTop t){
  UserDataTop novo = malloc(sizeof(struct user_dataTop));
  novo->inicio = converteData(cloneData(i));
  novo->fim = converteData(cloneData(f));
  novo->t = cloneArrayTop(t);

  return novo;
}

Date getDataInicioTop(UserDataTop d){
  return converteData(cloneData(d->inicio));
}

Date getDataFimTop(UserDataTop d){
  return converteData(cloneData(d->fim));
}

ArrayTop getArray(UserDataTop d){
  return cloneArrayTop(d->t);
}

void setArray(UserDataTop d, ArrayTop n){
  d->t = cloneArrayTop(n);
}


void freeUserDataTop(UserDataTop d){
  free(d);
}

struct user_dataPar {
  Data inicio;
  Data fim;
  LONG_pair par;
};

UserDataPar createUserDataPar (Date i, Date f,  LONG_pair par){
  UserDataPar novo = malloc(sizeof(struct user_dataPar));
  novo->inicio = converteData(cloneData(i));
  novo->fim = converteData(cloneData(f));
  novo->par = create_long_pair(get_fst_long(par), get_snd_long(par));

  return novo;
}

Date getDataInicioPar(UserDataPar d){
  return converteData(cloneData(d->inicio));
}

Date getDataFimPar(UserDataPar d){
  return converteData(cloneData(d->fim));
}

LONG_pair getPar(UserDataPar d){
  LONG_pair novo = malloc(sizeof(struct long_pair));
  novo->fst = get_fst_long(d->par);
  novo->snd = get_snd_long(d->par);
  return novo;
}

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
	return cloneLista(p->l);
}

void setListaU (UserDataTitle d, Lista l){
  d->l = l;
}
void freeUserDataTitle(UserDataTitle d){
  if(d->l != NULL)
    free(d->l)
  free(d);
}


-----
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
  u->melhor = cloneTopN(n);
}

void freeUserDataRes(UserDataRes u){
  free (u);
}
