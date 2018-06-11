package engine;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ParseUsers extends DefaultHandler {


      private HashMap<Long,Users> uHash = null;
      private Users u = null;
      public Map<Long,Users> getuHash() {
          return uHash;
      }


      @Override
      public void startElement(String uri, String localName, String qName, Attributes attributes)
              throws SAXException {
                if(uHash == null){
                  uHash = new HashMap<Long,Users>();
                }

                		if (qName.compareTo("row") == 0){
                      u = new Users();
                      if(attributes.getValue("ID")!= null)
                			long id = Long.parseLong(attributes.getValue("ID"));
                	    String bio = attributes.getValue("AboutMe");
                      String nome =  attributes.getValue("DisplayName");
                      if(attributes.getValue("ID")!= null)
                      int rep = Integer.parseInt(attributes.getValue("Reputation"));
                      u.setId(id);
                      u.setNome(nome);
                      u.setBio(bio);
                      u.setReputacao(rep);
                      uHash.put(id,u);
                	}

      }
      
      @Override
      public void endElement(String uri, String localName, String qName) throws SAXException {

      }

      @Override
      public void characters(char ch[], int start, int length) throws SAXException {

      }
  }
