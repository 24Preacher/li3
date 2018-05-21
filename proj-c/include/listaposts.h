#ifndef __LISTAPOSTS__
#define __LISTAPOSTS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"
#include "postsD.h"

typedef struct lligada* Lista;
typedef struct lposts* PostsUsers;
typedef struct arraypost* ArrayPosts;

Lista createLista (long post);
Lista addPost (Lista l, long post);
int lengthL(Lista l);
PostsUsers createPostsUsers (long user, Lista l);
ArrayPosts createArrayPosts (int size);
long getPostId_L (Lista l);
long getUserID_L (PostsUsers p);
Lista getListaPosts (ArrayPosts p, int i);
int getSizeArray (ArrayPosts p);
int getOcupados(ArrayPosts p);
void setOcupados(ArrayPosts p, int o);
PostsUsers getAPosts (ArrayPosts p, int i);
void setAPosts(ArrayPosts p, int i, PostsUsers c);
void freePostsUsers (PostsUsers p);
void freeArrayPosts (ArrayPosts p);
void insere(Posts_D posts, ArrayPosts p);
Lista cloneLista (Lista l);
PostsUsers clonePostUsers(PostsUsers l);
ArrayPosts cloneArrayPosts(ArrayPosts l);
Lista getProx(Lista l);
void freeLista(Lista l);
int pertence(Lista l, long p);

#endif
