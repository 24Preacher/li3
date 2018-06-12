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


public class ParsePosts extends DefaultHandler {


      private Map<Long,Posts> posts = null;
      private Posts p = null;

      public Map<Long,Posts> getPosts() {
          return posts;
      }



      @Override
      public void startElement(String uri, String localName, String qName, Attributes attributes)
              throws SAXException {

                  Long id = 0L, ownerId = 0L, parentId = 0L;
                  int commentCount = 0, score = 0, answerCount = 0;
                  short postTypeId = 0;
                  String tags, date, titulo;

                if(posts == null){
                  posts = new TreeMap<Long,Posts>();
                }

                		if (qName.compareTo("row") == 0){
                      if(attributes.getValue("ID")!= null)
                      id = Long.parseLong(attributes.getValue("ID"));
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




                      if(attributes.getValue("Title")!= null)
                      titulo = attributes.getValue("Title");

                      p.setIdPost(id);
                      p.setIdAutor(ownerId);
                      p.setTitulo(titulo);
                      p.setData(creation_date);
                      p.setPostType(postTypeId);
                      p.setIdPai(parentId);
                      p.setComentarios(commentCount);
                      p.setRespostas(answerCount);
                      p.setVotos(score);
                      p.setTags(tagg);
                      posts.put(id,p);
                	}
      }

      @Override
      public void endElement(String uri, String localName, String qName) throws SAXException {

      }

      @Override
      public void characters(char ch[], int start, int length) throws SAXException {

      }
  }
