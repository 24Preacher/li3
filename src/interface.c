#include "struct.c"
#include "list.c"

// #define N   //nr de users

typedef struct TCD_community {
  Posts_D postsbydata;
  Posts_Id postsbyid;
  Users users;
}TAD_community;

// liga os ids dos posts ao seu user
/*
void ligaPosts (TAD_community com){
    LONG_list aux[N];
    aux = malloc (sizeof( N * LONG_list));

    long i = (long) com->postsbydata->id_user;
    aux[i]->size++;
    aux[i]->list = id_post;
    ligaPosts(com->postsbydata->esq);
    ligaPosts(com->postsbydata->dir);
} * /
