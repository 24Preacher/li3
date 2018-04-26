#include "data.h"

 struct data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minutos;
   int segundos;
   int msegundos;
 };

Data createData (int dia, int mes, int ano, int hora, int min, int seg, int mseg){
  Data d = malloc (sizeof(struct data));
  d->dia = dia;
  d->mes = mes;
  d->ano = ano;
  d->hora = hora;
  d->minutos = min;
  d->segundos = seg;
  d->msegundos = mseg;

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

int getmSeg (Data d){
  return d->msegundos;
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
  r->msegundos = d->msegundos;
  return r;
}

gint compareMyData(Data a, Data b){

    if (a->ano > b->ano) return 1;
    else if (a->ano < b->ano) return -1;
    else if (a->mes > b->mes) return 1;
    else if (a->mes < b->mes) return -1;
    else if (a->dia) > b->dia) return 1;
    else if (a->dia < b->dia) return -1;
    else if (a->hora > b->hora) return 1;
    else if (a->hora < b->hora) return -1;
    else if (a->minutos > b->minutos) return 1;
    else if (a->minutos < b->minutos) return -1;
    else if (a->segundos > b->segundos) return 1;
    else if (a->segundos < b->segundos) return -1;
    else if (a->msegundos > b->msegundos) return 1;
    else if (a->msegundos  < b->msegundos) return -1;
    else return 0;

}

int compareDate(Date a, Date b){
  if (get_year(a) > get_year(b)) return 1;
  else if (get_year(a) < get_year(b)) return -1;
  else if (get_month(a) > get_month(b)) return 1;
  else if (get_month(a) < get_month(b)) return -1;
  else if (get_day(a) > get_day(b)) return 1;
  else if (get_day(a) < get_day(b)) return -1;
  else return 0;

}

Date converteData(Data a){
  Date d = createDate(a->dia, a->mes, a->ano);
  return d;
}

int dataIgual(Date a, Data b){
  Date n = converteData(b);
  return(compareDate(a ,n));

}


Data strToData (char *d){
  int i = 0;
  Data d;
  char ano[4];
  char mes[2];
  char dia[2];
  char hora[2];
  char minutos[2];
  char segundos[2];
  char msegundos[3];

  while(d[i] != '\0'){
    if(d[i] == '-' || d[i] == ':' d[i] == 'T' || d[i] == '.'){
      strncpy(d->ano, *d, 4);
      strncpy(d->mes, *(d+5), 2);
      strncpy(d->dia, *(d+8), 2);
      strncpy(d->hora, *(d+11), 2);
      strncpy(d->minutos, *(d+14), 2);
      strncpy(d->segundos, *(d+17), 2);
      strncpy(d->msegundos, *(d+20), 3);
    }
  }
  return d;
}
