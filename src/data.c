#include "data.h"

 struct data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minutos;
   int segundos;
 };

Data createData (int dia, int mes, int ano, int hora, int min, int seg){
  Data d = malloc (sizeof(struct data));
  d->dia = dia;
  d->mes = mes;
  d->ano = ano;
  d->hora = hora;
  d->minutos = min;
  d->segundos = seg;

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

int getSegundos(Data d){
  return d->segundos;
}

void freeData (Data d){
  free (d);
}

Data cloneData (Data d){
  Data r = malloc(sizeof(struct data));
  r->dia = d->dia;
  r->mes = d->mes;
  r->ano = d->ano;
  r->hora = d->hora;
  r->minutos = d->minutos;
  r->segundos = d->segundos;
  return r;
}
