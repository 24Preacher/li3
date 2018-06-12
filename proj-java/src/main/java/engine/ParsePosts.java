package engine;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;
import java.util.TreeMap;
import java.util.Map;
import java.util.Locale;
import java.util.ArrayList;
import java.util.List;


/*
* Classe que implementa o parser do ficheiro posts.xml
* @author Grupo 32
* @version 12/06/2018
*/

public class ParsePosts extends DefaultHandler {

      /** Map que armazena os posts*/
      private Map<Long,Posts> posts = null;
      /** Post que vai ser inserido */
      private Posts p = null;

      /**
       * Método que obtém a estrutura dos posts
       */
      public Map<Long,Posts> getPosts() {
          return posts;
      }


      /**
       * Método que inicializa o parsing dos posts
       */
      @Override
      public void startElement(String uri, String localName, String qName, Attributes attributes)
              throws SAXException {

                  Long id = 0L, ownerId = 0L, parentId = 0L;
                  int commentCount = 0, score = 0, answerCount = 0;
                  short postTypeId = 0;
                  String tags = " ", date = " ", titulo = " ";

                if(posts == null){
                  posts = new TreeMap<Long,Posts>();
                }

                		if (qName.compareTo("row") == 0){
                      if(attributes.getValue("Id")!= null)
                      id = Long.parseLong(attributes.getValue("Id"));
                      if(attributes.getValue("OwnerUserId") != null)
                      ownerId = Long.parseLong(attributes.getValue("OwnerUserId"));
                      if(attributes.getValue("ParentId") != null)
                      parentId = Long.parseLong(attributes.getValue("ParentId"));
                      if(attributes.getValue("CommentCount") != null)
                      commentCount = Integer.parseInt(attributes.getValue("CommentCount"));
                      if(attributes.getValue("Score") != null)
                      score = Integer.parseInt(attributes.getValue("Score"));
                      if(attributes.getValue("PostTypeId") != null)
                      postTypeId = Short.parseShort(attributes.getValue("PostTypeId"));
                      if(attributes.getValue("Title") != null)
                      titulo = attributes.getValue("Title");
                      if(attributes.getValue("AnswerCount") != null)
                      answerCount = Integer.parseInt(attributes.getValue("AnswerCount"));
                      date = attributes.getValue("CreationDate");
                      DateTimeFormatter data = DateTimeFormatter.ofPattern("yyyy-MM-dd'T'HH:mm:ss.SSS", Locale.ENGLISH);
                      LocalDateTime creation_date = LocalDateTime.parse(date, data);
                      tags = attributes.getValue("Tags");
                      List<String> tagg = new ArrayList<>();
                      StringParaTags t = new StringParaTags();
                      tagg = t.parser(tags);

                      p = new Posts(id,ownerId,titulo,creation_date,postTypeId,parentId,commentCount,answerCount,score,tagg);

                      posts.put(id,p);
                	}
      }


      /**
       * Método que finaliza o parsing dos posts
       */
      @Override
      public void endElement(String uri, String localName, String qName) throws SAXException {

      }

      @Override
      public void characters(char ch[], int start, int length) throws SAXException {

      }
  }
