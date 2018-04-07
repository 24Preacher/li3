#include "data.h"

 struct data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minutos;
 }

Data createData (int dia, int mes, int ano, int hora, int min){
  Data d = malloc (sizeof(struct data));
  d->dia = dia;
  d->mes = mes;
  d->ano = ano;
  d->hora = hora;
  d->minutos = min;

  return d;
}

int getDia (Data d){
  return d->dia;
}

int getMes (Data d){
  return d->mes;
}

int getAno (Data d){
  return d->ano;
}

int getHora (Data d){
  return d->hora;
}

int getMinutos (Data d){
  return d->minutos;
}

void freeData (Data d){
  free (d);
}

Data cloneData (Data d){
  Data r = malloc(sizeof(struct data));
  r -> dia;
  r -> mes;
  r -> ano;
  r -> hora;
  r -> min;
}
