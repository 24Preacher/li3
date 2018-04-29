#ifndef __POSTSD__
#define __POSTSD__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"
#include "tags.h"
#include "data.h"


typedef struct Posts_data* Posts_D;

Posts_D createPostsD (Data d, long user, long post, char* title,int respostas,
		short ptype, long parent, int com, int score, Tags t);

Data getDate (Posts_D posts);

long getUserId (Posts_D posts);

long getPostId (Posts_D posts);

char* getTitle (Posts_D posts);

int getAnswers (Posts_D posts);

short getPostType (Posts_D posts);

long getParentId (Posts_D posts);

int getVotes (Posts_D posts);

int getComments (Posts_D posts);

int getScore (Posts_D posts);

Tags getTags (Posts_D posts);

void freePostsD (gpointer posts);

Posts_D clonePostsD (Posts_D posts);

gint data_ord (Posts_D a, Posts_D b);

#endif
