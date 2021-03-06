#ifndef __POSTSID__
#define __POSTSID__



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"
#include "tags.h"
#include "data.h"

typedef struct Posts_id* Posts_ID;
gint compareID(gconstpointer a, gconstpointer b);
Posts_ID createPostsID (long post, long user, char* title, Data d, int ptype, long parent);
long getPostId2 (Posts_ID posts);
long getUserId2 (Posts_ID posts);
char* getTitle2 (Posts_ID posts);
Data getDate2 (Posts_ID posts);
int getPostType2 (Posts_ID posts);
long getParentId2 (Posts_ID posts);
void freePostsID (gpointer posts);
Posts_ID clonePostsID (Posts_ID posts);


#endif
