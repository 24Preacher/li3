
#ifndef HASHTAGS_H
#define HASHTAGS_H

#include "common.h"
#include <glib.h>
#include <stdlib.h>

typedef struct htags* HashTags;

GHashTable* createHashTag(char *tagname, long id);
char* getTagName (HashTags t);
long getIDTag(HashTags t);
void freeHashTag (HashTags t);

#endif
