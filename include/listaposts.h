#ifndef LISTAPOSTS_H
#define LISTAPOSTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"

typedef struct *lligada Lista;

typedef struct *lposts Lista_Posts;

Lista createLista (long id);

Lista addPost (Lista l, long id);

Lista createLPosts (int size);

long getPostId_L (Lista l);

Lista getListaPosts (Lista_Posts l);

void freeListaPosts (Lista_Posts l);

#endif
