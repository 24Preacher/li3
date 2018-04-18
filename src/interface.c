#include "postsD.c"
#include "postsID.c"
#include "listaposts.c"
#include "tags.c"
#include "users.c"
#include "string.h"
#include <glib.h>



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

STR_pair info_from_post(TAD_community com, long id){

  Posts_ID p = g_tree_lookup(com->postsbyid, id);

  char* nome = g_hash_table_lookup(com->users, p->id_user);
  //nome = malloc(sizeof(nome));
  STR_pair res = create_str_pair(p->title, nome);

  return res;
}
/*
LONG_list top_most_active(TAD_community com, int N){

}
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    long respostas = 0;
    long perguntas = 0;

  gpointer *inicio = g_tree_lookup(com->postsbydata, begin);

  g_tree_foreach(inicio, (GTraverseFunc) compareData(inicio->data_post ,end),

}
*/
//Função que verifica se uma tag está numa lista de tags

int existeTag(char* tag, Tags t){

  if (!t) return 0;

  while(t != NULL){
    if(strcmp(tag,t->nome) == 0)
      return 1;
    else t = t->prox;
  }
  return 0;
}

long func(Posts_D posts, char* tag, LONG_list l){
    int n = 0;
    long guarda[];
    if(posts->post_type == 1){
      if(existeTag(tag, posts->tags)){
        guarda[n] = posts->id_post;
        n++;
      }
    }
    l->size = n;
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
      gpointer *inicio = g_tree_lookup(com->postsbydata, begin);

      g_tree_foreach(inicio, (GTraverseFunc) dataIgual(end, inicio->data_post), *func);


}
