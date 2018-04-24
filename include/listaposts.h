#ifndef __LISTAPOSTS__
#define __LISTAPOSTS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"

typedef struct lligada* Lista;
typedef struct lposts* PostsUsers;
typedef struct arraypost* ArrayPosts;

Lista createLista (long id);
Lista addPost (Lista l, long id);
PostsUsers createPostsUsers (long user, Lista l);
ArrayPosts createArrayPosts (int size);
long getPostId_L (Lista l);
long getUserID_L (ArrayPosts p, int i);
Lista getListaPosts (ArrayPosts p, int i);
int getSizeArray (ArrayPosts p);
void setSizeArray (ArrayPosts p, int size);
int getOcupados(ArrayPosts p);
void setOcupados(ArrayPosts p, int o);
PostsUsers getAPosts (ArrayPosts p, int i);
void freePostsUsers (PostsUsers p);
void freeArrayPosts (ArrayPosts p);
void insere(ArrayPosts p, long user, long post);
Lista cloneLista (Lista l);
PostsUsers clonePostUsers(PostsUsers l);
ArrayPosts cloneArrayPosts(ArrayPosts l);

#endif
