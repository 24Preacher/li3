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
struct TCD_community {
  Posts_D postsbydata;
  Posts_ID postsbyid;
  Users users;
};


//TAD_community init();

//TAD_community load(TAD_community com, char* dump_path);
/*
STR_pair info_from_post(TAD_community com, long id){

  Posts_ID p = g_tree_lookup(com->postsbyid, id);

  char* nome = g_hash_table_lookup(com->users, p->id_user);
  nome = malloc(sizeof(nome));
  STR_pair res = create_str_pair(p->title, nome);

  return res;
}

LONG _list top_most_active(TAD_community com, int N){

}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
    long respostas = 0;
    long perguntas = 0;

  gpointer *inicio = g_tree_lookup(com->postsbydata, begin);

  g_tree_foreach(inicio, (GTraverseFunc) compareData(inicio->data_post ,end),

}




*/
