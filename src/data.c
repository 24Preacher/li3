#include "data.h"

/**
\struct Data
@param dia Dia
@param mes Mês
@param ano Ano
@param hora Hora
@param minutos Minutos
@param segundos Segundos
@param msegundos Milisegundos
*/
 struct data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minutos;
   int segundos;
   int msegundos;
 };

 /**
 \brief Função que cria a estrutura da Data
 @param dia Dia
 @param mes Mês
 @param ano Ano
 @param hora Hora
 @param min Minutos
 @param seg Segundos
 @param mseg Milisegundos
 @returns A nova Data
 */
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

/**
\brief Função que busca o dia
@param d Data
@returns Dia da data
*/
int getDia (Data d){
  return d->dia;
}

/**
\brief Função que busca o mês
@param d Data
@returns Mês da data
*/
int getMes (Data d){
  return d->mes;
}

/**
\brief Função que busca o ano
@param d Data
@returns Ano da data
*/
int getAno (Data d){
  return d->ano;
}

/**
\brief Função que busca a hora
@param d Data
@returns Hora da data
*/
int getHora (Data d){
  return d->hora;
}

/**
\brief Função que busca os minutos
@param d Data
@returns Minutos da data
*/
int getMinutos (Data d){
  return d->minutos;
}

/**
\brief Função que busca os segundos
@param d Data
@returns Segundos da data
*/
int getSegundos(Data d){
  return d->segundos;
}

/**
\brief Função que busca os milisegundos
@param d Data
@returns milisegundos da data
*/
int getmSeg (Data d){
  return d->msegundos;
}

/**
\brief Função que liberta a Data
@param d Data
*/
void freeData (Data d){
  free (d);
}

/**
\brief Função que clona a estrutura da Data
@param d Data
@returns A estrutura clonada da Data
*/
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

/**
\brief Função que compara duas datas do tipo Data
@param a Data
@param b Data
@returns 0 se forem iguais, 1 se a for maior que b e -1 caso contrário
*/
gint compareMyData(Data a, Data b){

    if (a->ano > b->ano) return 1;
    else if (a->ano < b->ano) return -1;
    else if (a->mes > b->mes) return 1;
    else if (a->mes < b->mes) return -1;
    else if (a->dia > b->dia) return 1;
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

/**
\brief Função que compara duas datas do tipo Date
@param a Data
@param b Data
@returns 0 se forem iguais, 1 se a for maior que b e -1 caso contrário
*/
int compareDate(Date a, Date b){
  if (get_year(a) > get_year(b)) return 1;
  else if (get_year(a) < get_year(b)) return -1;
  else if (get_month(a) > get_month(b)) return 1;
  else if (get_month(a) < get_month(b)) return -1;
  else if (get_day(a) > get_day(b)) return 1;
  else if (get_day(a) < get_day(b)) return -1;
  else return 0;

}
/**
\brief Função que converte uma data do tipo Data no tipo Date
@param a Data
@returns Data do tipo Date
*/
Date converteData(Data a){
  Date d = createDate(a->dia, a->mes, a->ano);
  return d;
}

/**
\brief Função que compara duas datas dos tipos Date e Data
@param a Data do tipo Date
@param b Data do tipo Data
@returns 0 se forem iguais, 1 se a for maior que b e -1 caso contrário
*/
int dataIgual(Date a, Data b){
  Date n = converteData(b);
  return(compareDate(a ,n));

}

/**
\brief Função que passa de uma string para uma estrutura de Data
@param d String da Data
@returns UserDataTop
*/
Data strToData (char *d){
  int i = 0;
  Data nova;
  char ano[4];
  char mes[2];
  char dia[2];
  char hora[2];
  char minutos[2];
  char segundos[2];
  char msegundos[3];

  if(d[i] != '\0'){
      strncpy(ano, d, 4);
      strncpy(mes, d+5, 2);
      strncpy(dia, d+8, 2);
      strncpy(hora, d+11, 2);
      strncpy(minutos, d+14, 2);
      strncpy(segundos, d+17, 2);
      strncpy(msegundos, d+20, 3);
    }
    int year = atoi(ano);
    int month = atoi(mes);
    int day = atoi(dia);
    int hour = atoi(hora);
    int min = atoi(minutos);
    int sec = atoi(segundos);
    int msec = atoi(msegundos);
    nova = createData(day, month, year, hour, min, sec, msec);
  return nova;
}
