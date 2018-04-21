#ifndef LISTAPOSTS_H
#define LISTAPOSTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"

typedef struct *lligada Lista;
typedef struct *lposts PostsUsers;
typedef struct *arraypost ArrayPosts;

Lista createLista (long id);
Lista addPost (Lista l, long id);
PostsUsers createPostsUsers (long user, Lista l);
ArrayPosts createArrayPosts (int size);
long getPostId_L (Lista l);
long getUserID_L (ArrayPosts p, int i);
Lista getListaPosts (ArrayPosts p, int i);
int getSizeArray (ArrayPosts p);
void setSizeArray (ArrayPosts p, int size);
PostsUsers getAPosts (ArrayPosts p, int i);
void freePostsUsers (PostsUsers p);
void freeArrayPosts (ArrayPosts p);


#endif
