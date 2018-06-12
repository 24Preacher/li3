package engine;


import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.util.HashMap;
import java.util.Map;

/*
* Classe que implementa o parser do ficheiro users.xml
* @author Grupo 32
* @version 12/06/2018
*/

public class ParseUsers extends DefaultHandler {

      /** Map que armazena os utilizadores*/
      private Map<Long,Users> uHash = null;
      /** Utilizador que vai ser inserido */
      private Users u = null;

      /**
       * Método que obtém a estrutura dos utilizadores
       */
      public Map<Long,Users> getuHash() {
          return uHash;
      }

      /**
       * Método que inicializa o parsing dos utilizadores
       */
      @Override
      public void startElement(String uri, String localName, String qName, Attributes attributes)
              throws SAXException {

                int rep = 0;
                long id = 0;

                if(uHash == null){
                  uHash = new HashMap<Long,Users>();
                }

                		if (qName.compareTo("row") == 0){
                      u = new Users();
                      if(attributes.getValue("Id")!= null)
                			id = Long.parseLong(attributes.getValue("Id"));
                	    String bio = attributes.getValue("AboutMe");
                      String nome =  attributes.getValue("DisplayName");
                      if(attributes.getValue("Reputation")!= null)
                      rep = Integer.parseInt(attributes.getValue("Reputation"));
                      u.setId(id);
                      u.setNome(nome);
                      u.setBio(bio);
                      u.setReputacao(rep);
                      uHash.put(id,u);
                	}

      }

      /**
       * Método que finaliza o parsing dos utilizadores
       */
      @Override
      public void endElement(String uri, String localName, String qName) throws SAXException {

      }

      @Override
      public void characters(char ch[], int start, int length) throws SAXException {

      }
  }
