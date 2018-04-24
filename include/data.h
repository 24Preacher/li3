#ifndef __DATA__
#define __DATA__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"

typedef struct data* Data;

Data createData (int dia, int mes, int ano, int hora, int min);

int getDia (Data d);

int getMes (Data d);

int getAno (Data d);

int getHora (Data d);

int getMinutos (Data d);

void freeData (Data d);

#endif
