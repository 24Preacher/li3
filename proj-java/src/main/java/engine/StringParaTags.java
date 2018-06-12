package engine;


import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;



public class StringParaTags{

  public List<String> parser(String tag){
    List<String> r = new ArrayList<String>();

    if(tag!=null){
      StringTokenizer toke = new StringTokenizer(tag, ";<>");
      while(toke.hasMoreElements()) {
        String token = toke.nextToken();
        if(!(token.equals("gt")) && (!(token.equals("lt"))) && (!(token.equals("Tags=\"")))
        && (!(token.equals("\"")))){
          r.add(token);
        }
      }
    }
    return r;
  }
}
