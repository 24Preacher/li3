#ifndef POSTSID_H
#define POSTSID_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "date.h"

typedef struct *Posts_id Posts_ID;

long getPostId2 (Posts_ID posts);

long getUserId2 (Posts_ID posts);

char* getTitle2 (Posts_ID posts);

Date getDate2 (Posts_ID posts);

#endif
