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

  TAD_community com = malloc(sizeof(struct TCD_community));

  com->postsbyid = g_tree_new((GCompareFunc)&compareID);
  com->postsbydata = g_tree_new((GCompareFunc)&data_ord);
  com->users = g_hash_table_new_full(g_direct_hash, g_direct_equal, free,(GDestroyNotify) freeUsers);
  com->arrayposts = createArrayPosts(0);
  com->tabtags = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)freeHashTag);

  return com;
}

//query 0
TAD_community load(TAD_community com, char* dump_path){

  char *docname1 = "/home/mercy/Desktop/nana/src/Posts.xml";
  char *docname2 = "/home/mercy/Desktop/nana/src/Users.xml";
  char *docname3 = "/home/mercy/Desktop/nana/src/Tags.xml";
  GTree	*treeid = NULL;
  GTree *treed = NULL;
  GHashTable *tab = NULL;
  GHashTable *tags = NULL;


  //parsePosts(docname1 ++ dump_path, treed, treeid);
  int num_users = parseDoc(docname3, docname2, docname1, tags, tab, treed, treeid);

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
  gpointer p = g_tree_lookup((GTree*)com->postsbyid, (gconstpointer)id);
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
  TopN n = NULL;
  percorre(com->arrayposts, t);

  for(i = 0; i < N; i++){
    n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }
  freeTop(n);
  for(;i < N-1; i++)
    set_list(res, i, -1);
  freeArrayTop(t);

  return res;
}



//q3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    LONG_pair par = create_long_pair(0, 0);
    UserDataPar u = createUserDataPar (begin, end, par);

    gpointer inicio = g_tree_lookup((GTree *)com->postsbydata, (gconstpointer)begin);

    g_tree_foreach((GTree*)inicio, (GTraverseFunc) &incrementaPar, (gpointer)u);

    par = getPar(u);
    freeUserDataPar(u);
    return par;

}



//q4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){

      Lista l = NULL;
      UserDataTag u = createUserDataTag(begin, end, tag, l);
      LONG_list res;

      gpointer p = g_tree_lookup((GTree*) com->postsbydata, (gconstpointer)begin);
      g_tree_foreach((GTree *) p, (GTraverseFunc) &checkTags,(gpointer) u);

      l = getListaUTag(u);
      int tam = lengthL(l);
      res = create_list(tam);
      Lista aux = cloneLista(l);
      for(int i = 0; i < tam && aux != NULL ; i++){
        long post = getPostId_L(aux);
        set_list(res, i, post);
        aux = getProx(aux);
      }
      freeLista(l);
      freeLista(aux);
      freeUserDataTag(u);
      return res;
}

//q5

USER get_user_info(TAD_community com, long id){
  USER res;
  gpointer u = g_hash_table_lookup((GHashTable*) com->users, (gconstpointer)id);
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
  freeLista(l);
  freeLista(aux);
  res = create_user(bio,(long *) last10posts);

  return res;
}


//q6




LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
  int i;

  ArrayTop t = createArrayTop(N);
  UserDataTop top = createUserDataTop(begin, end, t);
  TopN n = NULL;

  gpointer inicio = g_tree_lookup((GTree *) com->postsbydata, begin);
  g_tree_foreach((GTree *) inicio, (GTraverseFunc) &topScore, (gpointer)top);

  LONG_list res = create_list(N);
  t = getArray(top);
  for(i = 0; i < N; i++){
    n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }
  for(; i < N-1; i++)
    set_list(res, i, -1);

  freeTop(n);
  freeUserDataTop(top);

  return res;
}


//q7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
      LONG_pair par = create_long_pair(0, 0);
      UserDataPar u = createUserDataPar (begin, end, par);
      int i;
      TopN c = NULL;

    gpointer inicio = g_tree_lookup((GTree *)com->postsbydata, (gconstpointer)begin);

    g_tree_foreach((GTree*)inicio, (GTraverseFunc) &incrementaPar, (gpointer)u);
        par = getPar(u);
        int size = (int)(get_fst_long(par));
        freeUserDataPar(u);

   ArrayTop t = createArrayTop(size);
   UserDataTop n = createUserDataTop(begin, end, t);

   g_tree_foreach((GTree*)inicio, (GTraverseFunc)&inserePerguntas, (gpointer) n);
   g_tree_foreach((GTree*)inicio, (GTraverseFunc)&incrementaRespostas, (gpointer)n);

   t = getArray(n);
   //ordenar o array

   LONG_list l = create_list(N);
   for(i = 0; i < N; i++){
     c = getTop(t, i);
     long id = getID_Top(c);
     set_list(l, i, id);
   }
   for(; i < N-1; i++)
     set_list(l, i, -1);

   freeTop(c);
   freeUserDataTop(n);
   return l;
}

//q8

LONG_list contains_word(TAD_community com, char* word, int N){
  int i;
  Lista guarda = NULL;
  UserDataTitle u = createUserDataTitle(word, guarda);
  g_tree_foreach((GTree *)com->postsbydata, (GTraverseFunc) &temPalavra, (gpointer)u);

  LONG_list res = create_list(N);

  for(i = 0; i < N; i++){
    guarda = getListaU(u);
    long id = getPostId_L(guarda);
    set_list(res, i, id);
  }
  for(; i< N-1; i++)
    set_list(res, i, -1);

  freeLista(guarda);
  freeUserDataTitle(u);
  return res;
}

//q10
long better_answer(TAD_community com, long id){

  gpointer p = g_tree_lookup((GTree*) com->postsbyid, (gconstpointer)id);
  long user = getUserId2(p);
  gpointer u = g_hash_table_lookup((GHashTable*)com->users, (gconstpointer)user);
  int rep = getRep(u);

  Data d = getDate2(p);
  gpointer post = g_tree_lookup((GTree*)(com->postsbydata), (gconstpointer)d);

  long pergunta = getPostId(post);
  int r = getAnswers(post);
  TopN melhor = NULL;
  UserDataRes ud = createUserDataRes(d, rep, pergunta, r, melhor);
  g_tree_foreach((GTree*) post, (GTraverseFunc) melhor,(gpointer) ud);

  long melhor_resposta = getID_Top(getTopU(ud));

  freeUserDataRes(ud);
  return melhor_resposta;
}
