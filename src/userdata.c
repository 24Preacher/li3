#include "userdata.h"

//struct auxiliar para o foreach
struct user_data {
  Data inicio;
  Data fim;
  ArrayTop t;
};


UserData createUserData (Data i, Data f, ArrayTop t){
  UserData novo = malloc(sizeof(struct user_data));
  UserData->inicio = i;
  UserData->fim = f;
  UserData->t = t;

  return novo;
}

Data getDataInicio(UserData d){
  return cloneData(d->inicio);
}

Data getDataFim(UserData d){
  return cloneData(d->fim);
}

ArrayTop getArray(UserData d){
  return d->cloneArrayTop(t);
}

void setArray(UserData d, ArrayTop n){
  d->t = n;
}


void freeUserData(UserData d){
  free(d);
}
