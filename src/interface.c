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
#include <string.h>

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

  com->postsbyid= g_tree_new((GCompareFunc)&compareID);
  com-> postsbydata = g_tree_new((GCompareFunc)&data_ord);
  com->users = g_hash_table_new_full(g_direct_hash, g_direct_equal, &free,(GDestroyNotify) freeUsers);
  com->tabtags = g_hash_table_new_full(g_str_hash, g_str_equal, &free, (GDestroyNotify)freeHashTag);
  com->arrayposts = NULL;

  return com;
}

//query 0
TAD_community load(TAD_community com, char* dump_path){

  char *docname1 = "/home/preacher/Desktop/copy/src/Posts.xml";
  char *docname2 = "/home/preacher/Desktop/copy/src/Users.xml";

  parseDoc(docname2, docname1, com->users, com->postsbyid,com->postsbydata);

//  g_tree_foreach((GTree*)com->postsbydata, (GTraverseFunc)&insere, (gpointer)a);
//s  com->arrayposts = a;

//
//  parseTags((xmlDocPtr)(docname3 ), tags);
//  com->tabtags = tags;

  return com;
}

//q1
STR_pair info_from_post(TAD_community com, long id){
  Posts_ID p;
  int type;
  char* titulo;
  char* nome;
  STR_pair res;
  gpointer g = g_tree_lookup(com->postsbyid, &id);
  if(g)
  p = (Posts_ID) g;
  type = getPostType2(p);
  if(type==1){
    titulo = getTitle2(p);
    long *user = malloc(sizeof(long));
    *user = getUserId(p);
    gpointer gg = g_hash_table_lookup(com->users,user);
    if(gg){
      nome = getName(gg);
        }
  }
  if(type==2){
    long *pai = malloc(sizeof(long));
    *pai = getParentId2(p);
    gpointer gg = g_tree_lookup(com->postsbyid,pai);
    Posts_ID pp = (Posts_ID) gg;
    titulo = getTitle2(pp);
    long *user = malloc(sizeof(long));
    *user = getUserId(p);
    gpointer h = g_hash_table_lookup(com->users,user);
    if(h){
      Users hh = (Users) h;
      nome = getName(hh);
    }
  }
res = create_str_pair(titulo, nome);
printf("Nome: %s Titulo: %s\n",nome,titulo);
return res;
}

/*
//q2
LONG_list top_most_active(TAD_community com, int N){
  LONG_list res;
  ArrayTop t = createArrayTop(N);

  percorre(com->arrayposts, t);

  res = converteTopList(t, N);
  freeArrayTop(t);

  return res;
}

*/
//q3
/*
LONG_pair total_posts(TAD_community com, Date begin, Date end){
  LONG_pair par = create_long_pair(0,0);
  UserDataPar u = createUserDataPar(begin, end, par);
  gpointer inicio = g_tree_lookup(com->postsbydata,&begin);
  if(inicio){
    Posts_D ini = (Posts_D) inicio;
    g_tree_foreach(ini,&incrementaPar,u);
  }
    LONG_pair par2 = getPar(u);
    printf("%ld\n",get_fst_long(par2));
    printf("%ld\n",get_snd_long(par2));
    return par2;
}
*/

/*
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

  while(getUserID_L(getAPosts(com->arrayposts, i)) < id) i++;

    LONG_list last10posts = create_list(10);
    Lista l = getListaPosts(com->arrayposts, i);
    Lista aux = cloneLista(l);

    for(j = 0; j < 10 && aux != NULL; j++){
      long post = getPostId_L(aux);
      set_list(last10posts, j, post);
      aux = getProx(aux);
    }
    if(j < 10){
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
  ArrayTop t = createArrayTop(N);
  UserDataTop top = createUserDataTop(begin, end, t);

  gpointer inicio = g_tree_lookup((GTree *) com->postsbydata, begin);
  g_tree_foreach((GTree *) inicio, (GTraverseFunc) &topScore, (gpointer)top);

  LONG_list res;
  t = getArray(top);
  res = converteTopList(t, N);
  freeUserDataTop(top);

  return res;
}


//q7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
      LONG_pair par = create_long_pair(0, 0);
      UserDataPar u = createUserDataPar (begin, end, par);


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
   qsort(&t, N, sizeof(TopN), cmpCount);

   LONG_list l = converteTopList(t, N);
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

  guarda = getListaU(u);
  for(i = 0; guarda != NULL && i < N; i++){
    long id = getPostId_L(guarda);
    set_list(res, i, id);
  }
  if(i < N){
  for(; i< N; i++)
    set_list(res, i, -1);
  }
  freeLista(guarda);
  freeUserDataTitle(u);
  return res;
}

//q9
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
  LONG_list res = create_list(N);
  int i, j, pos1, pos2;
  ArrayData c = createArrayData(N);
  Lista a, b;
  a = b = NULL;
  AuxData new = NULL;

  for(i = 0; i < getSizeArray(com->arrayposts); i++){
    long user = getUserID_L(getAPosts(com->arrayposts, i));
    if(user == id1) pos1 = i;
    if(user == id2) pos2 = i;
  }

  Lista posts1 = getListaPosts(com->arrayposts, pos1);
  for(; posts1 != NULL; posts1 = getProx(posts1)){
    long postid1 = getPostId_L(posts1);
    gpointer p = g_tree_lookup((GTree*)com->postsbyid, (gconstpointer) postid1);
    if(getPostType2(p) == 2){
      long parent = getParentId2(p);
      a = addPost(a, parent);
      if(pertence(getListaPosts(com->arrayposts,pos2), parent)){
        gpointer n = g_tree_lookup((GTree*)com->postsbyid, (gconstpointer) parent);
        AuxData nova = createAuxData(getDate2(n), parent);
        inserePelaData(c, nova);
      }
    }
  }
  Lista posts2 = getListaPosts(com->arrayposts, pos2);
  for(; posts2 != NULL; posts2 = getProx(posts2)){
    long postid2 = getPostId_L(posts2);
    gpointer p2 = g_tree_lookup((GTree*)com->postsbyid, (gconstpointer) postid2);
    if(getPostType2(p2) == 2){
      long parent2 = getParentId2(p2);
      b = addPost(b, parent2);
      if(pertence(getListaPosts(com->arrayposts,pos1), parent2)){
        gpointer n2 = g_tree_lookup((GTree*)com->postsbyid, (gconstpointer) parent2);
        AuxData nova2 = createAuxData(getDate2(n2), parent2);
        inserePelaData(c, nova2);
      }
    }
  }

while(a != NULL){
  while(b != NULL){
    long pergunta = getPostId_L(a);
    if(pertence(b, pergunta)){
      gpointer pai = g_tree_lookup((GTree *)com->postsbyid, (gconstpointer)pergunta);
      AuxData nova3 = createAuxData(getDate2(pai), pergunta);
      inserePelaData(c, nova3);
      b = getProx(b);
    }
  }
  a = getProx(a);
}
  int ocup = getOcupadosData(c);
  for(j = 0; ocup > 0 && j < N; j++){
    new = getAuxData(c, j);
    long val = getId_Aux(new);
    set_list(res, j, val);
    ocup--;
  }
  if(j < N){
    for(; j < N; j++)
    set_list(res, j, -1);
  }
  freeAuxData(new);
  freeArrayData(c);

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

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
  ArrayTop t = createArrayTop(N);
  g_hash_table_foreach((GHashTable*)com->users,(GTraverseFunc) &topRep, (gpointer)t);
  g_tree_foreach((GTree*)com->postsbydata, (GTraverseFunc), );

}*/

TAD_community clean(TAD_community com){

  if(com != NULL){
    freePostsD(com->postsbydata);
    freePostsID(com->postsbyid);
    freeUsers(com->users);
  //  freeArrayPosts(com->arrayposts);
//     freeHashTag(com->tabtags);
    free(com);
    com = NULL;
  }
  return com;
}
