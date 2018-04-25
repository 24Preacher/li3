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
#include "glib.c"
#include "topN.h"
#include "userdata.h"



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
  HashTags tabtags;
};


TAD_community init(){

  TAD_community com = malloc(sizeof(struct TCD_community));
  com->postsbydata = g_tree_new(&data_ord);
  com->postsbyid = g_tree_new(&compareID);
  com->users = g_hash_table_new_full(g_direct_hash, g_direct_equal, free, freeUsers);
  com->arrayposts = createArrayPosts(0);
  com->tabtags = g_hash_table_new_full(g_str_hash, g_str_equal, free, freeHashTag);

  return com;
}

//query 0
TAD_community load(TAD_community com, char* dump_path){

  char *docname1 = "";
  char *docname2 = "";
  char *docname3 = "";
	GTree	*treeid;
  GTree *treed;
  GHashTable *tab;
  GHashTable *tags;

	parsePosts((docname1 ++ dump_path), treed, treeid);

  com->postsbyid = treed;
  com->postsbydata = treeid;


  int num_users = parseUsers((docname2 ++ dump_path), tab);
  com->users = tab;
  ArrayPosts a = createArrayPosts(num_users);


  g_tree_foreach(com->postsbydata, &insere, a);
  com->arrayposts = a;

  parseTags((docname3 ++ dump_path), tags);
  com->tabtags = tags;

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

//aux para q2
void percorre(ArrayPosts p, ArrayTop t){
  int i;

  for(i = 0; i < getSizeArray(p); i++){
    long id = getUserID_L(p, i);
    Lista posts = getListaPosts(p,i);
    int c = lengthL(posts);
    TopN n = createTopN(id, c);
    insereTop(t, n);
  }
}

//q2
LONG_list top_most_active(TAD_community com, int N){
  int i;
  LONG_list res = create_list(N);
  ArrayTop t = createArrayTop(N);

  percorre(com->arrayposts, t);

  for(i = 0; i < N; i++){
    TopN n = getTop(t, i);
    long id = getID_Top(t);
    set_list(res, i, id);
  }

  return res;
}

// aux q3
gboolean incrementaPar (Posts_D p, UserDataPar u){

  LONG_pair par = getPar(u);
  long perguntas = get_fst_long(par);
  long respostas = get_snd_long(par);
  Data data = getDate(p);
  Date begin = getDataInicioPar(u);
  Date end = getDataFimPar(u);

  if(dataIgual(end, data) == 0) return TRUE;
  if(dataIgual(begin, data) == -1){
    short ptype = getPostType(p);
    if(ptyte == 1)
        perguntas ++;
    else if (ptype == 2)
        respostas ++;

    set_fst_long(par, perguntas);
    set_snd_long(par, respostas);
    }
  return FALSE;

}



//q3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    LONG_pair par = create_long_pair(0, 0);
    UserDataPar u = createUserDataPar (begin, end, par);

    gpointer *inicio = g_tree_lookup(com->postsbydata, begin);

    g_tree_foreach(inicio, &incrementaPar, u);

    par = getPar(u);
    return par;

}

//aux q4
gboolean checkTags(Posts_D p, UserDataTag u){
    Data d = getDate(p);
    Date begin = getDataInicioTag(u);
    Date end = getDataFimTag(u);
    char* tag = getTagU(u);
    Lista t = getTags(p);
    Lista temtags = getListaUTag(u);


  if(dataIgual(end, d) == 0) return TRUE;
  if(dataIgual(begin, d) == -1){
    if(getPostType(p) == 1){
      if (existeTag(tag, t) == 1){
        addPost(temtags, getPostId(p));
        setListaUTag(u, temtags);
      }
    }
  }
  return FALSE;
}





//q4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
      Posts_D p = g_tree_lookup(com->postsbydata, begin);
      Lista l = NULL;
      UserDataTag u = createUserDataTag(begin, end, tag, l);
      LONG_list res;
      g_tree_foreach(inicio, &checkTags, u);

      l = getListaUTag(u);
      int tam = lengthL(l);
      res = create_list(tam);

      for(int i = 0; i < tam; i++, l = l->prox){
        set_list(res, i, getPostId_L);
      }
      return res;
}

//q5

USER get_user_info(TAD_community com, long id){
  USER res;
  Users u = g_hash_table_lookup(com->users, id);
  int i = 0, j;
  char* bio = getBio(u);

  while(getUserID_L(com->arrayposts, i) < id) i++;

    LONG_list last10posts = create_list(10);
    Lista l = getListaPosts(com->arrayposts, i);
    for(j = 0; l != NULL && j < 10; l = l->prox, j++){
      long post = getPostId_L(l);
      set_list(last10posts, j, post);
    }
    if(j < 9){
      for(; j < 10; j++)
          set_list(last10posts, j, -1);
    }

  res = create_user(bio, last10posts);

  return res;
}


//q6

gboolean topScore(Posts_D p, UserDataTop top){
  Data data = getDate(p);
  Date begin = getDataInicioTop(top);
  Date end = getDataFimTop(top);
  ArrayTop t = getArray(top);

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

  ArrayTop t = createArrayTop(N);
  UserDataTop top = createUserDataTop(begin, end, t);

  Posts_D inicio = g_tree_lookup(com->postsbydata, begin);
  g_tree_foreach(inicio, &topScore, top);

  LONG_list res = create_list(N);
  t = getArray(top);
  for(i = 0; i < N; i++){
    TopN n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
  }
  return res;
}


//q7
/* query 7 ta mal

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
int pertenceTitulo(char* palavra, Posts_D p){
  if (strstr(getTitle(p), palavra) != NULL)
    return 1;
  return 0;
}

gboolean temPalavra(Posts_D p, UserDataTitle u){
  Lista l = getListaU(u);
  char* pal = getPal(u);

  if(getPostType(p) == 1){
    if(pertenceTitulo(pal, p)){
     long post = getPostId(p);
     Lista res = addPost(l, post);
     setListaU(u, res);
    }
  }
  return FALSE;
}

//q8

LONG_list contains_word(TAD_community com, char* word, int N){

  Lista guarda = NULL;
  UserDataTitle u = createUserDataTitle(word, guarda);
  g_tree_foreach(com->postsbydata, &temPalavra, u);

  LONG_list res = create_list(N);

  for(int i = 0; i < N; i++){
    guarda = getListaU(u);
    long id = getUserID_L(guarda);
    set_list(res, i, id);
  }
  return res;
}

int valResposta(Posts_D p, int rep){
  int scr, comt;

  scr = getScore(p);
  comt = getComments(p);

  int res = (scr * 0.65 + rep * 0.25 + comt * 0.1);
  return res;
}

gboolean melhor(Posts_D p, UserDataRes u){
  int respostas = getAnswersRes(u);
  int val;
  TopN max = getTopU(u);
  TopN novo;

  if(respostas <= 0) return TRUE;
  if(compareData(getDate(p), getDataPergunta(u)) == -1){
    if(getParentId(p) == getIdPergunta(u)){
      val = valResposta(p, getRepU(u));
      if(max == NULL || val > getCount(max)) {
        novo = createTopN(getPostId(p),val);
        setTopU(u, novo);
      }
      respostas--;
      setAnswers(u, respostas);
    }
  }
  return FALSE;
}

//q10
long better_answer(TAD_community com, long id){

  Posts_ID p = g_tree_lookup(com->postsbyid, id);
  long user = getUserId2(p);
  Users u = g_hash_table_lookup(com->users);
  int rep = getRep(u);

  Data d = getDate2(p);
  Posts_D post = g_tree_lookup(com->postsbydata, d);

  long pergunta = getPostId(post);
  int r = getAnswers(post);
  TopN melhor = NULL;
  UserDataRes ud = createUserDataRes(d, rep, pergunta, r, melhor);
  g_tree_foreach(post, &melhor, ud);

  long melhor_resposta = getID_Top(getTopU(ud));
  return melhor_resposta;
}
