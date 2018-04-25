#ifndef PARSER_H
#define PARSER_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <glib.h>

#include "hashtags.h"
#include "users.h"
#include "postsD.h"

#include "tags.h"
#include "users.h"
#include "postsID.h"


int parseUsers (xmlDocPtr doc, GHashTable *hash_table);
void parsePosts (xmlDocPtr doc, GTree *tree1, GTree *tree2);
void parseTags (xmlDocPtr doc, GHashTable *hash_table);
int parseDoc(char *doctags, char *docusers, char *docposts, GHashTable *hash_tags, GHashTable *hash_users, GTree *tree1, GTree *tree2);




#endif
