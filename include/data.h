#ifndef __DATA__
#define __DATA__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"


typedef struct data* Data;

Data createData (int dia, int mes, int ano, int hora, int min, int seg, int mseg);

int getDia (Data d);

int getMes (Data d);

int getAno (Data d);

int getHora (Data d);

int getMinutos (Data d);

int getSegundos(Data d);

int getmSeg(Data d);

void freeData (Data d);

Data cloneData (Data d);

gint compareMyData(Data a, Data b);

int compareDate(Date a, Date b);

Date converteData(Data a);

int dataIgual(Date a, Data b);

Data strToData (char *d);



#endif
