#include "struct.c"


#define N   //nr de users

typedef struct TCD_community {
  Posts_D postsbydata;
  Posts_Id postsbyid;
  Users users;
}TAD_community;

void contaPosts (TAD_community com){
    int aux[N];
    int j;
    aux = malloc (sizeof( N * User));

    for (j = 0 ; j < N; j++)
      aux[j] = 0;

    long i = com->posts_data->id_user;
    aux[i]++;
    contaPosts(com->posts_data->esq);
    contaPosts(com->posts_data->dir);
}
