package engine;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.TreeSet;
import java.util.Set;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeMap;

import java.util.stream.Collectors;

import common.Pair;


public class Queries
{
  private TCD_Community com;

    //load
    //public void load(String dumpPath);

    //query 1


public Pair<String,String> infoFromPost(long id)
{

  TreeMap<Long,Posts> posts = this.com.getArvPostsID();
  HashMap<Long,Users> users = this.com.getTabUsers();
  String titulo = " ", nome = " ";

  Posts p = posts.get(id);
  if(p != null){
    if(p.getPostType() == 1){
      titulo = p.getTitulo();
      nome = users.get(p.getIdAutor()).getNome();
    }
    else {
      Posts p1 = posts.get(p.getIdPai());
      titulo = p1.getTitulo();
      nome = users.get(p1.getIdAutor()).getNome();
    }
  }
  //else throw new NaoExistePostException

  return new Pair<>(titulo, nome);
}



// Query 2
public List<Long> topMostActive(int N){
  HashMap<Long, Users> users = this.com.getTabUsers();
  List<Users> maiorNumPosts= users.values().stream()
                                           .sorted(new ComparadorNumPosts())
                                           .limit(N)
                                           .collect(Collectors.toList());

  return maiorNumPosts.stream().map(Users::getId).collect(Collectors.toList());
}



// Query 3
public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
  TreeMap<Long, Posts> posts = this.com.getArvPostsID();
  long respostas = 0;
  long perguntas = 0;

  LocalDateTime inicio = begin.atStartOfDay();
  LocalDateTime fim = end.atEndOfDay();
  List<Posts> postsEntreDatas = posts.values().stream()
                                              .filter(p->p.getData().isAfter(inicio) && p.getData().isBefore(fim))
                                              .collect(Collectors.toList());

  for(Posts p : postsEntreDatas)
    if(p.getPostType() == 1)
      perguntas++;
    else if (p.getPostType() == 2)
      respostas++;

  return new Pair<>(perguntas, respostas);
}


// Query 4
public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
  TreeMap<Long, Posts> posts = this.com.getArvPostsID();
  LocalDateTime inicio = begin.atStartOfDay();
  LocalDateTime fim = end.atStartOfDay();

  return  posts.values().stream()
                        .filter(p->p.getData().isAfter(inicio) && p.getData().isBefore(fim) && p.getTags().contains(tag))
                        .sorted(new ComparadorDataPost().reversed())
                        .map(Posts :: getIdPost)
                        .collect(Collectors.toList());

}


// Query 5
public Pair<String, List<Long>> getUserInfo(long id) {
  HashMap<Long,Users> users = this.com.getTabUsers();
  String nome = " ";
  List<Long> postsU = new ArrayList<>();

  Users u = users.get(id);
  if(u != null) {
    nome = u.getNome();
    postsU = u.getPostsUser().stream()
                             .sorted(new ComparadorDataPost().reversed())
                             .limit(10)
                             .map(Posts::getIdPost)
                             .collect(Collectors.toList());
  }
  //else throw new UserNaoExisteException
  return new Pair<>(nome, postsU);
}

/*
    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end);

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end);

    // Query 8
    public List<Long> containsWord(int N, String word);
*/
    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2){
      HashMap<Long, Users> users = this.com.getTabUsers();
      TreeMap<Long, Posts> posts = this.com.getArvPostsID();
      Set<Posts> aux = new TreeSet<>(new ComparadorDataPost());

      Set<Posts> respostasUser1 = users.get(id1).getPostsUser().stream().filter(p->p.getPostType() == 2).collect(Collectors.toSet());
      Set<Posts> respostasUser2 = users.get(id2).getPostsUser().stream().filter(p->p.getPostType() == 2).collect(Collectors.toSet());

      Set<Posts> perguntasUser1 = users.get(id1).getPostsUser().stream().filter(p->p.getPostType() == 1).collect(Collectors.toSet());
      Set<Posts> perguntasUser2 = users.get(id2).getPostsUser().stream().filter(p->p.getPostType() == 1).collect(Collectors.toSet());

      //1 responder ao 2
      for(Posts r1 : respostasUser1){
          Posts pai1 = posts.get(r1.getIdPai());
          if(perguntasUser2.contains(pai1))
            aux.add(pai1.clone());
      }
      //2 responder ao 1
      for(Posts r2 : respostasUser2){
        Posts pai2 = posts.get(r2.getIdPai());
          if(perguntasUser1.contains(pai2))
            aux.add(pai2.clone());
      }
      //1 e 2 responderem ao mm post
      List<Long> idsPai1 = respostasUser1.stream().map(Posts::getIdPai).collect(Collectors.toList());
      List<Long> idsPai2 = respostasUser2.stream().map(Posts::getIdPai).collect(Collectors.toList());
      for(Long l1 : idsPai1){
        if(idsPai2.contains(l1))
          aux.add(posts.get(l1).clone());
      }

      return aux.stream().sorted(new ComparadorDataPost().reversed())
                         .limit(N)
                         .map(Posts::getIdPost)
                         .collect(Collectors.toList());
    }
/*
    // Query 10
    public long betterAnswer(long id);
*/
    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        HashMap<Long, Users> users = this.com.getTabUsers();
        HashMap<String, Long> tags = this.com.getTabTags();
        LocalDateTime inicio = begin.atStartOfDay();
        LocalDateTime fim = end.atEndOfDay();

     List<Users> usersMelhorRep = users.values().stream()
                                                .sorted(new ComparadorReputacaoDec())
                                                .limit(N)
                                                .collect(Collectors.toList());
     //busca tds as tags em tds os posts entre aquelas datas
     List<String> todasAsTags = new ArrayList<>();
       for(Users u : usersMelhorRep){
           List<Posts> postsEntreDatas = u.getPostsUser().stream()
                                                         .filter(w->w.getData().isAfter(inicio) && w.getData().isBefore(fim))
                                                         .collect(Collectors.toList());
             for(Posts p : postsEntreDatas)
               for(String s : p.getTags())
                   todasAsTags.add(s);
           }
     //tags sem repetidos
     List<String> tagsUnicas = todasAsTags.stream().distinct().collect(Collectors.toList());
     List<Pair<String, Long>> tagsComContagem = new ArrayList<>();

     //faz a contagem e insere um par com a tag e a contagem
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
       long idTag = tags.get(tag);
       res.add(idTag);
     }
     return res;
   }

}
