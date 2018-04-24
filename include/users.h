#ifndef __USERS__
#define __USERS__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"

typedef struct users* Users;

Users createUsers (long id, char* nome, char* bio, int rep);

long getUserId3 (Users u);

char* getName (Users u);

char* getBio (Users u);

int getRep (Users u);

void freeUsers (Users u);

#endif
