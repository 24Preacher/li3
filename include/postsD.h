#ifndef POSTSD_H
#define POSTSD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"


typedef struct *Posts_data Posts_D;

Date getDate (Posts_D posts);

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

void freePostsD (Posts_D posts);

Posts_D clonePostsID (Posts_D posts);

#endif
