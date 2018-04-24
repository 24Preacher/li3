#ifndef __TAGS__
#define __TAGS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"

typedef struct tags*  Tags;

Tags createTags (char* nome, long id, int c);

char* getNameTag (Tags t);

long getIdTag (Tags t);

long getCountTags (Tags t);

void freeTags (Tags t);

#endif
