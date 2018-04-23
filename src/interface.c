#include "data.h"
#include "date.h"
#include "interface.h"
#include "list.h"
#include "listaposts.h"
#include "pair.h"
#include "parser.h"
#include "postsD.h"
#include "postsID.h"
#include "tags.h"
#include "user.h"
#include "users.h"

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
  ArrayPosts arrayposts;
};


TAD_community init(){

  TAD_community com = malloc(sizeof(struct TCD_community));
  com->postsbydata = g_tree_new(&data_ord);
  com->postsbyid = g_tree_new(&compareID)
  com->users = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, freeUsers);
  com->arrayposts = createArrayPosts(0);

  return com;
}

//query 0
TAD_community load(TCD_community com, char* dump_path){

  char *docname1;
  char *docname2;
	GTree	*treeid;
  GTree *treed;
  GHashTable *tab;

	//docname1 = "/home/mercy/Desktop/Posts.xml";
	parsePosts(docname1, treed, treeid);

  com->postsbyid = treed;
  com->postsbydata = treeid;

  //docname2 = "/home/mercy/Desktop/Users.xml";

  int num_users = parseUsers(docname2, tab);
  com->users = tab;
  ArrayPosts a = createArrayPosts(num_users);


  g_tree_foreach(com->postsbydata, &insere, a);
  com->arrayposts = a;

  return com;
}

//q1
STR_pair info_from_post(TAD_community com, long id){
  STR_pair res;
  long id_pai;
  Posts_ID p = g_tree_lookup(com->postsbyid, id);
    if(getPostId2(p) == 1){
        Users u = g_hash_table_lookup(com->users, getUserId2(p));
        res = create_str_pair(getTitle2(p), getName(u));
      }
    else if(getPostId2(p) == 2){
        id_pai = getParentId2(p);
        p = g_tree_lookup(com->postsbyid, id_pai);
        Users u = g_hash_table_lookup(com->users, getUserId2(p));
        res = create_str_pair(getTitle2(p), getName(u));
    }
  return res;
}
/*
//q2

LONG_list top_most_active(TAD_community com, int N){

  g_tree_foreach(com->postsbydata, --, --)

}

//q3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    long respostas = 0;
    long perguntas = 0;

  gpointer *inicio = g_tree_lookup(com->postsbydata, begin);

  g_tree_foreach(inicio, (GTraverseFunc) compareData(inicio->data_post ,end),

}
*/

//Função que verifica se uma tag está numa lista de tags - aux p/ q4
int existeTag(char* tag, Tags t){

  if (!t) return 0;
  while(t != NULL){
    if(strcmp(tag, getNameTag(t)) == 0)
      return 1;
    else t = t->prox;
  }
  return 0;
}
/*
Lista func(Posts_D posts, char* tag, LONG_list l){
    int n = 0;
    Lista guarda = NULL;
    if(getPostType(posts) == 1){
      if(existeTag(tag, getTags(posts))){
        if(!guarda)
            guarda = createLista(getPostId(posts));
        else{
        guarda = addPost(guarda, getPostId(posts));
      }
      n++;
    }
  }
    l->size = n;
    return guarda;
}


//q4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
      gpointer *inicio = g_tree_lookup(com->postsbydata, begin);

      LONG_list res = create_list(0);
      g_tree_foreach(inicio, (GTraverseFunc) dataIgual(end, getDate(inicio)), *func(inicio, tag, res));

}
*/
//q5

USER get_user_info(TAD_community com, long id){
  USER res;
  Users u = g_hash_table_lookup(com->users, id);
  int i = 0, j;
  res->bio = getBio(u);
  //parte dos ultimos 10 posts
  while(getUserID_L(com->arrayposts) < id) i++;

    LONG_list last10posts = create_list(10);
    Lista l = getListaPosts(p, i);
    for(j = 0; l != NULL && j < 10; l = l->prox, j++){
      long post = getPostId_L(l);
      set_list(last10posts, j, post);
    }
    if(j < 9){
      for(; j < 10; j++)
          set_list(last10posts, j, -1);
    }

  res->posts = last10posts;

  return res;
}


//Função que ve se uma palavra pertence a uma string - usar a strstr -aux a q8
int pertenceTitulo(char* palavra, Posts_D p){

  if (strstr(getTitle(t), palavra) != NULL)
    return 1;
  return 0;
}


//q6

gboolean topScore(ArrayTop t, Posts_D p, Date begin, Date end){
  Data data = getDate(p);

  if(dataIgual(end, data) == 0) return TRUE;
  if(dataIgual(begin, data) == -1){
  long id = getPostId(p);
  int c = getScore(p);
  TopN n = createTopN(id, c);
  insereTop(t, n);
  }
  return FALSE;
}


LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
  int i;
  Posts_D inicio = g_tree_lookup(begin);
  ArrayTop t = createArrayTop(N);
  g_tree_foreach(inicio, topScore, t);

  LONG_list res = create_list(N);

  for(i = 0; i < N; i++){
    TopN n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }
  return res;
}


//q7


gboolean topAnswers(ArrayTop t, Posts_D p, Date begin, Date end){
  Data data = getDate(p);

  if(dataIgual(end, data) == 0) return TRUE;
  if(dataIgual(begin, data) == -1){
  long id = getPostId(p);
  int c = getAnswers(p);
  TopN n = createTopN(id, c);
  insereTop(t, n);
  }
  return FALSE;
}


LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
  int i;
  Posts_D inicio = g_tree_lookup(com->postsbydata, begin);
  ArrayTop t = createArrayTop(N);
  g_tree_foreach(inicio, topAnswers, t);

  LONG_list res = create_list(N);

  for(i = 0; i < N; i++){
    TopN n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }
  return res;
}



//q8

//LONG_list contains_word(TAD_community com, char* word, int N){



//}


//Funçao que calcula o valor da resposta para q10

int valResposta(TAD_community com, Posts_D p){
  int val;
  int rep, scr, vot, comt;

  scr = vot = getScore(p);
  comt = getComments(p);

  User u = g_hash_table_lookup(com->users, getUserId(p));
  rep = getRep(u);

  val = (scr * 0.45 + rep * 0.25 + vot * 0.2 + comt * 0.1);
  return val;
}

gboolean aux (Posts_D p, Date begin, long id){
  if((dataIgual(getDate(p), begin) > 0) && (getPostId(p) == 2)){
    if(getParentId(p) == id) return TRUE;
    }
  return FALSE;
}

//q10 erros no uso das funçoes do glib probably
long better_answer(TAD_community com, int id){
  int respostas;
  long melhor;
  int val;
  int maxval = 0;
  GTree *tree;

  Posts_ID post = g_tree_lookup(com->postsbyid, id);
  Data d = getDate2(post);
  Posts_D pergunta = g_tree_lookup(com->postsbydata, d));

  repostas = getAnswers(pergunta);

  while(respostas > 0){
    tree = pergunta;
    g_tree_foreach(tree, aux(tree, d, getPostId), *tree)
    //Posts_D r = g_tree_lookup(tree, getParentId2(pergunta));
      if(getPostType(r) == 2){
        val = valResposta(com, r);
        if(val > maxval){
          melhor = getPostId(r);
          maxval = val;
        }
      }
      respostas--;
      tree = r;
    }

  return melhor;
}
