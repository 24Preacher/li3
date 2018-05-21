#ifndef __TAGS__
#define __TAGS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "common.h"

typedef struct tags* Tags;

Tags createTags (char* nome);

Tags addTag(Tags t, char* tag);

char* getNameTag (Tags t);

void freeTags (Tags t);

Tags cloneTags(Tags t);

Tags strToTags(char *a);

int existeTag(char* tag, Tags t);

#endif
