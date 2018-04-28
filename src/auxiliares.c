#include "auxiliares.h"



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

// aux q3
gboolean incrementaPar (Posts_D p, UserDataPar u){

  LONG_pair par = getPar(u);
  long perguntas = get_fst_long(par);
  long respostas = get_snd_long(par);
  Data data = getDate(p);
  Date begin = getDataInicioPar(u);
  Date end = getDataFimPar(u);

  if(dataIgual(end, data) == 0) return TRUE;
  if((dataIgual(begin, data)) == -1){
    short ptype = getPostType(p);
    if(ptype == 1)
        perguntas ++;
    else if (ptype == 2)
        respostas ++;

    set_fst_long(par, perguntas);
    set_snd_long(par, respostas);
    }
  return FALSE;

}

//aux q4
gboolean checkTags(Posts_D p, UserDataTag u){
    Data d = getDate(p);
    Date begin = getDataInicioTag(u);
    Date end = getDataFimTag(u);
    char* tag = getTagU(u);
    Tags t = getTags(p);
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

gboolean topScore(Posts_D p, UserDataTop top){
  Data data = getDate(p);
  Date begin = getDataInicioTop(top);
  Date end = getDataFimTop(top);
  ArrayTop t = getArray(top);

  if(dataIgual(end, data) == 0) return TRUE;
  if(dataIgual(begin, data) == -1){
    if(getPostType(p) == 2){
      long id = getPostId(p);
      int c = getScore(p);
      TopN n = createTopN(id, c);

      insereTop(t, n);
    }
  }
  return FALSE;
}
//auxs q7
gboolean inserePerguntas(Posts_D p, UserDataTop top){
      Data data = getDate(p);
      Date begin = getDataInicioTop(top);
      Date end = getDataFimTop(top);
      ArrayTop t = getArray(top);

      if(dataIgual(end, data) == 0) return TRUE;
      if(dataIgual(begin, data) == -1){
        if(getPostType(p) == 1){
          long post = getPostId(p);
          TopN novo = createTopN(post, 0);
          insereResTop(t, novo);
        }
      }
      return FALSE;
}

gboolean incrementaRespostas(Posts_D p, UserDataTop top){
      Data data = getDate(p);
      Date begin = getDataInicioTop(top);
      Date end = getDataFimTop(top);
      ArrayTop t = getArray(top);

      if(dataIgual(end, data) == 0) return TRUE;
      if(dataIgual(begin, data) == -1){
        if(getPostType(p) == 2){
          long id_pai = getPostId(p);
          alteraCount(t, id_pai);
        }
      }
      return FALSE;
}

//auxs q8
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

//aux q10

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
  if(compareMyData(getDate(p), getDataPergunta(u)) == -1){
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
