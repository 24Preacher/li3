package engine;

import java.time.LocalDate;

import java.util.TreeMap;
import java.util.HashMap;
import common.Pair;

import engine.Posts;
import engine.Users;
import engine.TCD_Community;

public class queries
{

    //load
    //public void load(String dumpPath);

    //query 1


    public Pair<String,String> infoFromPost(long id)
    {

      TreeMap<Long,Posts> posts = getArvPostsID();
      HashMap<Long,Users> users = getTabUsers();
      String title = "";
      String name = "";

      if(posts.containsKey(id))
      {
          if(posts.getPostType(id) == 1)
          {
              title = posts.getTitulo(id);
              name = users.getName(posts.getIdAutor(id));
          }
          else {
              name = users.getName(posts.getIdPai(id));
          }
        return new Pair(title, name);
      }
      else System.out.println("ID not found lel");
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
