#include "postsD.c"
#include "postsID.c"
#include "listaposts.c"
#include "tags.c"
#include "users.c"
#include <glib.h>

// #define N_users

/**
\struct Definição do tipo abstrato(TAD) da estrutura principal
@param postsbydata Estrutura dos posts ordenados pela data
@param postsbyid Estrutura dos posts ordenados pelo id
@param Users Estrutura dos utilizadores
*/
typedef struct TCD_community {
  Posts_D postsbydata;
  Posts_ID postsbyid;
  Users users;
}TAD_community;


//TAD_community init();

//TAD_community load(TAD_community com, char* dump_path);
/*
STR_pair info_from_post(TAD_community com, long id){

  Nodo r = g_tree_lookup(com->postsbyid, id);

  char* nome = g_hash_table_lookup(com->users, r->id_user);
  nome = malloc(sizeof(nome));
  STR_pair res = create_str_pair(r->title, nome);

}*/
