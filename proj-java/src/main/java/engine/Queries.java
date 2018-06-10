

import java.time.LocalDate;

import java.util.TreeMap;
import java.util.HashMap;

import java.util.Arrays;
import java.util.Collections;
import java.util.*;


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
                                           .limit((long)N)
                                           .collect(Collectors.toList());

  return maiorNumPosts.stream().map(Users::getId).collect(Collectors.toList());
}



// Query 3
public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
  TreeMap<Long, Posts> posts = this.com.getArvPostsID();
  long respostas = 0;
  long perguntas = 0;

  LocalDateTime inicio = begin.atStartOfDay();
  LocalDateTime fim = end.atStartOfDay();
  List<Posts> postsEntreDatas = posts.values().stream()
                                              .sorted(new ComparadorDataPost())
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
                        .sorted(new ComparadorDataPost())
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
    postsU = u.getPostsUser().stream().map(Posts::getIdPost).collect(Collectors.toList());
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

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2);

    // Query 10
    public long betterAnswer(long id);

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end);
    */

}
