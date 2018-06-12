package engine;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ParsePosts extends DefaultHandler {


      private TreeMap<Long,Posts> posts = null;
      private Posts p = null;

      public Map<Long,Posts> getPosts() {
          return posts;
      }


      @Override
      public void startElement(String uri, String localName, String qName, Attributes attributes)
              throws SAXException {
                if(posts == null){
                  posts = new TreeMap<Long,Posts>();
                }

                		if (qName.compareTo("row") == 0){
                      if(attributes.getValue("ID")!= null)
                      long id = Long.parseLong(attributes.getValue("ID"));
                      if(attributes.getValue("OwnerUserId") != null)
                      long ownerId = Long.parseLong(attributes.getValue("OwnerUserId"));
                      if(attributes.getValue("ParentId") != null)
                      long parentId = Long.parseLong(attributes.getValue("ParentId"));
                      if(attributes.getValue("CommentCount") != null)
                      int commentCount = Integer.parseInt(attributes.getValue("CommentCount"));
                      if(attributes.getValue("Score") != null)
                      int score = Integer.parseInt(attributes.getValue("Score"));
                      if(attributes.getValue("PostTypeId") != null)
                      short postTypeId = Short.parseShor(attributes.getValue("PostTypeId"));
                      if(attributes.getValue("AnswerCount") != null)
                      int answerCount = Integer.parseInt(attributes.getValue("AnswerCount"));
                      if(attributes.getValue("CreationDate")
                      String date = attributes.getValue("CreationDate");
                      DataTimeFormatter data = DataTimeFormatter.forPattern("YYYY-MM-DD");
                      if(attributes.getValue("Tags")!= null)
                      String tags = attributes.getValue("Tags");
                      if(attributes.getValue("Title")!= null)
                      String titulo = attributes.getValue("Title");
                      p.setIdPost(id);
                      p.setIdAutor(nome);
                      p.setTitulo(bio);
                      p.setData(rep);
                      p.setPostType(postTypeId);
                      p.setIdPai(parentID);
                      p.setComentarios(commentCount);
                      p.setRespostas(answerCount);
                      p.setVotos(score);
                      p.setTags(tags);
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
