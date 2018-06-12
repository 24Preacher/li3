package engine;



import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.HashMap;
import java.util.stream.Collectors;
import li3.TADCommunity;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.SAXException;
import java.io.IOException;

import java.io.File;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Set;
import java.util.List;
import java.util.ArrayList;


import common.Pair;


/*
 * Classe que implementa a estrutura principal e os métodos para resolver as queries
 * @author Grupo 32
 * @version 12/06/2018
 */

public class TCD_Community  implements TADCommunity {
    /** TreeMap que guarda os posts organizados pelo seu id */
    private Map<Long, Posts> arvPostsID;
    /** HashMap que armazena os utilizadores organizados pelo seu id*/
    private Map<Long, Users> tabUsers;
    /** HashMap que associa cada tag ao seu respetivo id */
    private Map<String, Long> tabTags;

    /**
     * Construtor vazio
     */
    public TCD_Community (){
        this.arvPostsID = new TreeMap<>();
        this.tabUsers = new HashMap<>();
        this.tabTags = new HashMap<>();
    }

    /**
     * Construtor parametrizado
     */
    public TCD_Community (Map<Long, Posts> arvID, Map<Long, Users> tab, Map<String, Long> tags){
        setArvPostsID(arvID);
        setTabUsers(tab);
        setTabTags(tags);
    }

    /**
     * Construtor por cópia
     */
    public TCD_Community (TCD_Community com){
        this.arvPostsID = com.getArvPostsID();
        this.tabUsers = com.getTabUsers();
        this.tabTags = com.getTabTags();
    }


    /**
     * Método que obtém a árvore dos posts
     * @return os posts
     */
    public TreeMap<Long, Posts> getArvPostsID(){
        TreeMap<Long, Posts> res = new TreeMap<>();
        for(Posts p : this.arvPostsID.values())
            res.put(p.getIdPost(),p.clone());
        return res;
    }

    /**
     * Método que obtém a tabela dos utilizadores
     * @return os utilizadores
     */
    public HashMap<Long,Users> getTabUsers(){
        HashMap<Long,Users> res = new HashMap<>();
        for(Users u : this.tabUsers.values())
            res.put(u.getId(),u.clone());
        return res;
    }

    /**
     * Método que obtém as tags e os seus respetivos ids
     * @return as tags
     */
    public HashMap<String,Long> getTabTags(){
        HashMap<String,Long> res = new HashMap<>();
        for(Map.Entry<String,Long> t : this.tabTags.entrySet())
            res.put(t.getKey(),t.getValue());
        return res;
    }



    /**
     * Método que atualiza a árvore dos posts
     */
    public void setArvPostsID(Map<Long,Posts> postsID){
        this.arvPostsID = new TreeMap<>();
        postsID.values().forEach(p -> this.arvPostsID.put(p.getIdPost(),p.clone()));
    }

    /**
     * Método que atualiza a tabela dos utilizadores
     */
    public void setTabUsers(Map<Long, Users> tab){
        this.tabUsers = new HashMap<>();
        tab.values().forEach(u -> this.tabUsers.put(u.getId(), u.clone()));
    }

    /**
     * Método que atualiza a tabela das tags
     */
    public void setTabTags(Map<String, Long> tab){
        this.tabTags = new HashMap<>();
        for(Map.Entry<String,Long> t : this.tabTags.entrySet())
            this.tabTags.put(t.getKey(), t.getValue());
    }

    /**
     * Devolve uma cópia de uma TCD_Community
     */
    public TCD_Community clone(){
        return new TCD_Community(this);
    }


    /**
     * Verifica a igualdade com outra TCD_Community
     */
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        TCD_Community com = (TCD_Community) o;

        return (this.arvPostsID.equals(com.getArvPostsID()) && this.tabUsers.equals(com.getTabUsers())
                        && this.tabTags.equals(com.getTabTags()));
    }

    /**
     * Devolve representação textual da TCD_Community
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nPosts(ordenados pelo ID): ").append(this.arvPostsID.toString());
        sb.append("\nUtilizadores: ").append(this.tabUsers.toString());
        sb.append("\nTags: ").append(this.tabTags.toString());
        return sb.toString();
    }

    /**
     * Método que insere os posts nos utilizadores
     */
    public void inserePosts(){
        for(Posts p : this.arvPostsID.values())
            p.inserePostDoUser(this.tabUsers);
    }

    /**
     * Método que faz o load dos ficheiros xml para a estrutura principal
     */
    public void load(String dumpPath){

      SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
      try{
        SAXParser saxParser = saxParserFactory.newSAXParser();

        ParsePosts parse_post = new ParsePosts();
        saxParser.parse(new File(dumpPath + "/Posts.xml"), parse_post);

        ParseUsers parse_users = new ParseUsers();
        saxParser.parse(new File(dumpPath + "/Users.xml"), parse_users);

        ParseTags parse_tags = new ParseTags();
        saxParser.parse(new File(dumpPath + "/Tags.xml"), parse_tags);

          this.arvPostsID = parse_post.getPosts();

          this.tabUsers = parse_users.getuHash();


          this.tabTags = parse_tags.gettags();
    } catch (ParserConfigurationException | SAXException | IOException e){
      e.printStackTrace();
    }
    this.inserePosts();
}

/**
 * Query 1
 */
public Pair<String,String> infoFromPost(long id)
{
  String titulo = " ", nome = " ";

  Posts p = this.arvPostsID.get(id);
  if(p != null){
    if(p.getPostType() == 1){
      titulo = p.getTitulo();
      nome = this.tabUsers.get(p.getIdAutor()).getNome();
    }
    else {
      Posts p1 = this.arvPostsID.get(p.getIdPai());
      titulo = p1.getTitulo();
      nome = this.tabUsers.get(p1.getIdAutor()).getNome();
    }
  }

  return new Pair<>(titulo, nome);
}



/**
 * Query 2
 */
public List<Long> topMostActive(int N){
  List<Users> maiorNumPosts= this.tabUsers.values().stream()
                                           .sorted(new ComparadorNumPosts())
                                           .limit(N)
                                           .collect(Collectors.toList());

  return maiorNumPosts.stream().map(Users::getId).collect(Collectors.toList());
}



/**
 * Query 3
 */
public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
  long respostas = 0;
  long perguntas = 0;

  LocalDateTime inicio = begin.atStartOfDay();
  LocalDateTime fim = end.atTime(23,59,59);
  List<Posts> postsEntreDatas = this.arvPostsID.values().stream()
                                              .filter(p->p.getData().isAfter(inicio) && p.getData().isBefore(fim))
                                              .collect(Collectors.toList());

  for(Posts p : postsEntreDatas)
    if(p.getPostType() == 1)
      perguntas++;
    else if (p.getPostType() == 2)
      respostas++;
  return new Pair<>(perguntas, respostas);
}


/**
 * Query 4
 */
public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
  LocalDateTime inicio = begin.atStartOfDay();
  LocalDateTime fim = end.atTime(23,59,59);

  return  this.arvPostsID.values().stream()
                        .filter(p->p.getData().isAfter(inicio) && p.getData().isBefore(fim) && p.getTags().contains(tag))
                        .sorted(new ComparadorDataPost().reversed())
                        .map(Posts :: getIdPost)
                        .collect(Collectors.toList());
}


/**
 * Query 5
 */
public Pair<String, List<Long>> getUserInfo(long id)
{
  String bio = " ";
  List<Long> postsU = new ArrayList<>();

  Users u = this.tabUsers.get(id);
  if(u != null) {
    bio = u.getBio();
    postsU = u.getPostsUser().stream()
                             .sorted(new ComparadorDataPost().reversed())
                             .limit(10)
                             .map(Posts::getIdPost)
                             .collect(Collectors.toList());
  }
  return new Pair<>(bio, postsU);
}


/**
 * Query 6
 */
public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
    LocalDateTime inicio = begin.atStartOfDay();
    LocalDateTime fim = end.atTime(23,59,59);

  return this.arvPostsID.values().stream()
                       .filter(p->p.getData().isAfter(inicio) && p.getData().isBefore(fim) && p.getPostType() == 2)
                       .sorted(new ComparadorVotosDec())
                       .limit(N)
                       .map(Posts :: getIdPost)
                       .collect(Collectors.toList());
    }


/**
 * Query 7
 */
public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
    LocalDateTime inicio = begin.atStartOfDay();
    LocalDateTime fim = end.atTime(23,59,59);

      return this.arvPostsID.values().stream()
                           .filter(p->p.getData().isAfter(inicio) && p.getData().isBefore(fim) && p.getPostType() == 1)
                           .sorted(new ComparadorRespostasDec())
                           .limit(N)
                           .map(Posts::getIdPost)
                           .collect(Collectors.toList());
    }


/**
 * Query 8
 */
public List<Long> containsWord(int N, String word){
      return this.arvPostsID.values().stream()
                           .filter(p->p.getPostType() == 1 && p.getTitulo().contains(word))
                           .sorted(new ComparadorDataPost().reversed())
                           .limit(N)
                           .map(Posts::getIdPost)
                           .collect(Collectors.toList());
}

/**
 * Query 9
 */
public List<Long> bothParticipated(int N, long id1, long id2){
    Set<Posts> aux = new TreeSet<>(new ComparadorDataPost().reversed());

    Set<Posts> respostasUser1 = this.tabUsers.get(id1).getPostsUser().stream().filter(p->p.getPostType() == 2).collect(Collectors.toSet());
    Set<Posts> respostasUser2 = this.tabUsers.get(id2).getPostsUser().stream().filter(p->p.getPostType() == 2).collect(Collectors.toSet());

    Set<Posts> perguntasUser1 = this.tabUsers.get(id1).getPostsUser().stream().filter(p->p.getPostType() == 1).collect(Collectors.toSet());
    Set<Posts> perguntasUser2 = this.tabUsers.get(id2).getPostsUser().stream().filter(p->p.getPostType() == 1).collect(Collectors.toSet());


    for(Posts r1 : respostasUser1){
      Posts pai1 = this.arvPostsID.get(r1.getIdPai());
        if(perguntasUser2.contains(pai1))
            aux.add(pai1.clone());
      }

    for(Posts r2 : respostasUser2){
      Posts pai2 = this.arvPostsID.get(r2.getIdPai());
        if(perguntasUser1.contains(pai2))
          aux.add(pai2.clone());
      }

    List<Long> idsPai1 = respostasUser1.stream().map(Posts::getIdPai).collect(Collectors.toList());
    List<Long> idsPai2 = respostasUser2.stream().map(Posts::getIdPai).collect(Collectors.toList());

    for(Long l1 : idsPai1){
      if(idsPai2.contains(l1))
        aux.add(this.arvPostsID.get(l1).clone());
      }

  return aux.stream()
            .limit(N)
            .map(Posts::getIdPost)
            .collect(Collectors.toList());
    }



/**
 * Query 10
 */
public long betterAnswer(long id){
      double val, max = 0;
      long melhor = 0;

      Posts p = this.arvPostsID.get(id);

      if(p != null){
        List<Posts> respostas = this.arvPostsID.values().stream().filter(a->a.getIdPai() == id).collect(Collectors.toList());

        for(Posts pp : respostas){
          int rep = this.tabUsers.get(pp.getIdAutor()).getReputacao();
          val = pp.getVotos() * 0.65 + pp.getComentarios() * 0.1 + rep * 0.25;
          if(val > max)
            melhor = pp.getIdPost();
        }
      }

      return melhor;
 }

 /**
  * Query 11
  */
public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        LocalDateTime inicio = begin.atStartOfDay();
        LocalDateTime fim = end.atTime(23,59,59);

     List<Users> usersMelhorRep = this.tabUsers .values().stream()
                                                .sorted(new ComparadorReputacaoDec())
                                                .limit(N)
                                                .collect(Collectors.toList());


     List<String> todasAsTags = new ArrayList<>();
       for(Users u : usersMelhorRep){
           List<Posts> postsEntreDatas = u.getPostsUser().stream()
                                                         .filter(w->w.getPostType() == 1 && w.getData().isAfter(inicio) && w.getData().isBefore(fim))
                                                         .collect(Collectors.toList());

             for(Posts p : postsEntreDatas)
               for(String s : p.getTags())
                 todasAsTags.add(s);

        }

     List<String> tagsUnicas = todasAsTags.stream().distinct().collect(Collectors.toList());
     List<Pair<String, Long>> tagsComContagem = new ArrayList<>();


     for(String s : tagsUnicas){
       long count = todasAsTags.stream().filter(t->t.equals(s)).count();
       Pair<String, Long> novo = new Pair<>(s, count);
       tagsComContagem.add(novo);
     }

     List<String> tagsMaisUsadas = tagsComContagem.stream()
                                                  .sorted(new ComparadorContagemDec())
                                                  .limit(N)
                                                  .map(Pair :: getFst)
                                                  .collect(Collectors.toList());
    List<Long> res = new ArrayList<>();

    for(String tag : tagsMaisUsadas){
       long idTag = this.tabTags.get(tag);
       res.add(idTag);
     }

     return res;
   }

 /**
  * Método clear que limpa os dados das estruturas
  */
   public void clear(){

     this.arvPostsID.clear();
     this.tabUsers.clear();
     this.tabTags.clear();
   }

}
