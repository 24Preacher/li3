#ifndef _POSTSID_H_
#define _POSTSID_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"
#include "tags.h"

typedef struct Posts_id* Posts_ID;
Posts_ID createPostsID (long post, long user, char* title, Data d, int respostas,short ptype, long parent, int com, int score, Tags t);
long getPostId2 (Posts_ID posts);
long getUserId2 (Posts_ID posts);
char* getTitle2 (Posts_ID posts);
Date getDate2 (Posts_ID posts);
int getAnswers2 (Posts_ID posts);
short getPostType2 (Posts_ID posts);
long getParentId2 (Posts_ID posts);
int getComments2 (Posts_ID posts);
int getScore2 (Posts_ID posts);
Tags getTags2 (Posts_ID posts);
void freePostsID (Posts_ID posts);
Posts_ID clonePostsID (Posts_ID posts);

#endif
