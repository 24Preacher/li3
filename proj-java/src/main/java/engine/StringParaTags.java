package engine;


import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

/*
* Classe que faz o parser de uma string de tags para uma lista de tags
* @author Grupo 32
* @version 12/06/2018
*/

public class StringParaTags{

  /**
   * Método que realiza o parse de uma string para um lista de tags
   */

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
