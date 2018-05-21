#include "auxiliares.h"

/**
\brief Função que compara a contagem de 2 TopN
@param top1 TopN
@param top2 TopN
@returns 0 se forem iguais, -1 se top1 for maior que top2 e 1 caso contrário
*/
int cmpCount(const void* top1, const void* top2){
  int c1 = getCount((TopN)top1);
  int c2 = getCount((TopN)top2);

  if(c1 > c2) return -1;
  else if(c1 < c2) return 1;
  else return 0;
}
/**
\brief Função que converte um ArrayTop para um LONG_list
@param t ArrayTop a converter
@param N Tamanho da LONG_list resultante
@returns Uma lista de N ids no formato LONG_list
*/
LONG_list converteTopList(ArrayTop t, int N){
  LONG_list res = create_list(N);
  int i, ocup = getOcupados2(t);
  TopN n = NULL;

  for(i = 0; ocup > 0 && i < N; i++){
    n = getTop(t, i);
    long id = getID_Top(n);
    set_list(res, i, id);
    ocup--;
  }
  if(i < N){
    for(;i < N; i++)
      set_list(res, i, -1);
  }
  freeTop(n);
  return res;
}

/**
\brief Função que percorre o ArrayPosts e insere num ArrayTop o id do utilizador e o seu número de posts
@param p ArrayPosts
@param t ArrayTop
*/
void percorre(ArrayPosts p, ArrayTop t){
  int i;

  for(i = 0; i < getSizeArray(p); i++){
    long id = getUserID_L(getAPosts(p, i));
    Lista posts = getListaPosts(p,i);
    int c = lengthL(posts);
    TopN n = createTopN(id, c);
    insereTop(t, n);
  }
}

/**
\brief Função que incrementa o par de contadores de perguntas e respostas ao percorrer a árvore
@param key Key do nodo da AVL dos posts
@param data Valor do nodo da AVL correspondente à key
@param info Userdata passada à função
@returns TRUE caso a data do post seja igual à data final, parando a travessia
*/
gboolean incrementaPar (void * key, void * data, void * info){
  Posts_D p = (Posts_D) data;
  UserDataPar u = (UserDataPar) info;
  LONG_pair par = getPar(u);
  long perguntas = get_fst_long(par);
  long respostas = get_snd_long(par);
  Data d = getDate(p);
  Date begin = getDataInicioPar(u);
  Date end = getDataFimPar(u);

  if(dataIgual(end, d) == 0) return TRUE;
  if((dataIgual(begin, d)) == -1){
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

/**
\brief Função que caso a tag exista nas tags da pergunta, adiciona o seu id a uma lista
@param p Valor do nodo da AVL
@param u Userdata passada à função, que contém as datas de ínicio e fim, a tag a procurar e uma lista
@returns TRUE caso a data do post seja igual à data final, parando a travessia
*/
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

/**
@param p Valor do nodo da AVL
\brief Função que adiciona o score de uma resposta e o seu id a um ArrayTop
@param top Userdata passada à função, que contém as datas de início e fim e um ArrayTop
@returns TRUE caso a data do post seja igual à data final, parando a travessia
*/
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

/**
\brief Função que insere as perguntas num ArrayTop
@param p Valor do nodo da AVL
@param top Userdata passada à função, que contém as datas de início e fim, a tag a procurar e uma lista
@returns TRUE caso a data do post seja igual à data final, parando a travessia
*/
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

/**
\brief Função que incrementa a contagem do ArrayTop quando encontra uma resposta das perguntas no ArrayTop
@param p Valor do nodo da AVL
@param top Userdata passada à função, que contém as datas de ínicio e fim, a tag a procurar e uma lista
@returns TRUE caso a data do post seja igual à data final, parando a travessia
*/
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

/**
\brief Função que verifica se uma palavra pertence ao título de um post
@param palavra Palavra a verificar
@param p Posts
@returns 1 se pertencer, 0 caso contrário
*/
int pertenceTitulo(char* palavra, Posts_D p){
  if (strstr(getTitle(p), palavra) != NULL)
    return 1;
  return 0;
}

/**
\brief Função que caso a palavra exista no titulo da pergunta, adiciona o seu id a uma lista
@param p Valor do nodo da AVL
@param u Userdata passada à função, que contém uma palavra e uma lista
@returns FALSE
*/
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

/**
\brief Função que calcula o valor de uma resposta
@param p Posts
@param rep Reputação
@returns Valor da resposta
*/
int valResposta(Posts_D p, int rep){
  int scr, comt;

  scr = getScore(p);
  comt = getComments(p);

  int res = (scr * 0.65 + rep * 0.25 + comt * 0.1);
  return res;
}

/**
\brief Função que calcula qual é a melhor resposta
@param p Valor do nodo da AVL
@param u Userdata passada à função, que contém a data, o id e o numero de respostas da pergunta, a reputação e um TopN com a melhor resposta encontrada
@returns TRUE caso o número de respostas seja 0, parando a travessia
*/
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

/**
\brief Função que percorre os utilizadores e os insere num ArrayTop consoante a sua reputação
@param u Valor da célula da Tabela de Hash dos Utilizadores
@param t ArrayTop
@returns FALSE
*/
gboolean topRep(Users u, ArrayTop t){
  long id = getUserId3(u);
  int c = getRep(u);
  TopN n = createTopN(id, c);
  insereTop(t, n);

  return FALSE;
}
