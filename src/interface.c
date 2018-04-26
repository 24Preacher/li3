#include "data.h"
#include "tags.h"
#include "postsD.h"
#include "postsID.h"
#include "interface.h"
#include "listaposts.h"
#include "parser.h"
#include "users.h"
#include "topN.h"
#include "userdata.h"
#include "auxiliares.h"
#include "hashtags.h"

#include <glib.h>


/**
\struct Definição do tipo abstrato(TAD) da estrutura principal
@param postsbydata Estrutura dos posts ordenados pela data
@param postsbyid Estrutura dos posts ordenados pelo id
@param Users Estrutura dos utilizadores
*/
struct TCD_community {
  GTree* postsbydata;
  GTree* postsbyid;
  GHashTable* users;
  ArrayPosts arrayposts;
  GHashTable* tabtags;
};


TAD_community init(){
    
  GTree *treedata = g_tree_new((GCompareFunc)&data_ord);
  TAD_community com = malloc(sizeof(struct TCD_community));
  com->postsbydata = treedata;
  GTree *treeid = g_tree_new((GCompareFunc)&compareID);
  com->postsbyid = treeid;
  com->users = g_hash_table_new_full(g_direct_hash, g_direct_equal, free,(GDestroyNotify) freeUsers);
  com->arrayposts = createArrayPosts(0);
  com->tabtags = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)freeHashTag);

  return com;
}

//query 0
TAD_community load(TAD_community com, char* dump_path){

  char *docname1 = "";
  char *docname2 = "";
  char *docname3 = "";
  GTree	*treeid = NULL;
  GTree *treed = NULL;
  GHashTable *tab = NULL;
  GHashTable *tags = NULL;

  
  int num_users = parseDoc(docname3, docname2, docname1, tags, tab, treed, treeid);
  //parsePosts(docname1 ++ dump_path, treed, treeid);

  com->postsbyid = treed;
  com->postsbydata = treeid;


  //parseUsers(docname2 ++ dump_path, tab);
  com->users = tab;
  ArrayPosts a = createArrayPosts(num_users);


  g_tree_foreach((GTree*)com->postsbydata, (GTraverseFunc)insere, (gpointer)a);
  com->arrayposts = a;

  //parseTags((xmlDocPtr)(docname3 ), tags);
  com->tabtags = tags;

  return com;
}

//q1
STR_pair info_from_post(TAD_community com, long id){
  STR_pair res;
  long id_pai;
  long id_user;
  Posts_ID p = g_tree_lookup((GTree*)com->postsbyid, (gconstpointer)id);
    if(getPostId2(p) == 1){
        id_user = getUserId2(p);
        Users u = g_hash_table_lookup((GHashTable*)com->users,(gconstpointer) id_user);
        res = create_str_pair(getTitle2(p), getName(u));
      }
    else if(getPostId2(p) == 2){
        id_pai = getParentId2(p);
        p = g_tree_lookup((GTree*)com->postsbyid, (gconstpointer)id_pai);
        id_user = getUserId2(p);
        Users u = g_hash_table_lookup((GHashTable*)com->users,(gconstpointer) id_user);
        res = create_str_pair(getTitle2(p), getName(u));
    }
  return res;
}

//q2
LONG_list top_most_active(TAD_community com, int N){
  int i;
  LONG_list res = create_list(N);
  ArrayTop t = createArrayTop(N);

  percorre(com->arrayposts, t);

  for(i = 0; i < N; i++){
    TopN n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }

  return res;
}



//q3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    LONG_pair par = create_long_pair(0, 0);
    UserDataPar u = createUserDataPar (begin, end, par);

    gpointer *inicio = g_tree_lookup((GTree *)com->postsbydata, (gconstpointer)begin);

    g_tree_foreach((GTree*)inicio, (GTraverseFunc) incrementaPar, (gpointer)u);

    par = getPar(u);
    return par;

}



//q4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
      Posts_D p = g_tree_lookup((GTree*) com->postsbydata, (gconstpointer)begin);
      Lista l = NULL;
      UserDataTag u = createUserDataTag(begin, end, tag, l);
      LONG_list res;
      g_tree_foreach((GTree *) p, (GTraverseFunc) checkTags,(gpointer) u);

      l = getListaUTag(u);
      int tam = lengthL(l);
      res = create_list(tam);
      Lista aux = cloneLista(l);
      for(int i = 0; i < tam && aux != NULL ; i++){
        long post = getPostId_L(aux);
        set_list(res, i, post);
        aux = getProx(aux);
      }
      return res;
}

//q5

USER get_user_info(TAD_community com, long id){
  USER res;
  Users u = g_hash_table_lookup((GHashTable*) com->users, (gconstpointer)id);
  int i = 0, j;
  char* bio = getBio(u);

  while(getUserID_L(com->arrayposts, i) < id) i++;

    LONG_list last10posts = create_list(10);
    Lista l = getListaPosts(com->arrayposts, i);
    Lista aux = cloneLista(l);
  
    for(j = 0; j < 10 && aux != NULL; j++){
      long post = getPostId_L(aux);
      set_list(last10posts, j, post);
      aux = getProx(aux);
    }
    if(j < 9){
      for(; j < 10; j++)
          set_list(last10posts, j, -1);
    }

  res = create_user(bio,(long *) last10posts);

  return res;
}


//q6




LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
  int i;

  ArrayTop t = createArrayTop(N);
  UserDataTop top = createUserDataTop(begin, end, t);

  Posts_D inicio = g_tree_lookup((GTree *) com->postsbydata, begin);
  g_tree_foreach((GTree *) inicio, (GTraverseFunc) topScore, (gpointer)top);

  LONG_list res = create_list(N);
  t = getArray(top);
  for(i = 0; i < N; i++){
    TopN n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }
  return res;
}

/*
//q7
 query 7 ta mal

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


LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
  int i;
  Posts_D inicio = g_tree_lookup(com->postsbydata, begin);
  ArrayTop t = createArrayTop(N);
  g_tree_foreach(inicio, &topAnswers, t);

  LONG_list res = create_list(N);

  for(i = 0; i < N; i++){
    TopN n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }
  return res;
}

*/

//Função que ve se uma palavra pertence a uma string - usar a strstr -aux a q8

//q8

LONG_list contains_word(TAD_community com, char* word, int N){

  Lista guarda = NULL;
  UserDataTitle u = createUserDataTitle(word, guarda);
  g_tree_foreach((GTree *)com->postsbydata, (GTraverseFunc) temPalavra, (gpointer)u);

  LONG_list res = create_list(N);

  for(int i = 0; i < N; i++){
    guarda = getListaU(u);
    long id = getPostId_L(guarda);
    set_list(res, i, id);
  }
  return res;
}

//q10
long better_answer(TAD_community com, long id){

  gpointer p = g_tree_lookup((GTree*) com->postsbyid, (gconstpointer)id); //no arg da arvore
  long user = getUserId2(p);
  Users u = g_hash_table_lookup((GHashTable*)com->users, (gconstpointer)user);
  int rep = getRep(u);

  Data d = getDate2(p); // erro tem haver ficheiro postid
  gpointer post = g_tree_lookup((GTree*)(com->postsbydata), (gconstpointer)d);

  long pergunta = getPostId(post);
  int r = getAnswers(post);
  TopN melhor = NULL;
  UserDataRes ud = createUserDataRes(d, rep, pergunta, r, melhor);
  g_tree_foreach(post, (GTraverseFunc) melhor, ud);

  long melhor_resposta = getID_Top(getTopU(ud));
  return melhor_resposta;
}
