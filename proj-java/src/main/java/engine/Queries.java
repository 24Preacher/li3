package engine;

import java.time.LocalDate;

import java.util.TreeMap;
import java.util.HashMap;
import common.Pair;

import engine.Posts;
import engine.Users;
import engine.TCD_Community;

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
      String titulo, nome;

      Posts p = posts.get(id);
      if(p != null){
        if(p.getPostType() == 1){
          titulo = p.getTitulo();
          nome = users.get(p.getIdAutor()).getNome();
        }
        else {
          Post p1 = posts.get(p.getIdPai());
          titulo = p1.getTitulo();
          nome = users.get(p1.getIdAutor()).getNome();
        }
      }
      //else throw new NaoExistePostException

      return new Pair(titulo, nome);
  }


    /*
    // Query 2
    public List<Long> topMostActive(int N);
    */

    /*
    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end);

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end);

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id);

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
