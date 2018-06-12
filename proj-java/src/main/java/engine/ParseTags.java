package engine;


import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.util.Map;
import java.util.HashMap;

/*
* Classe que implementa o parser do ficheiro tags.xml
* @author Grupo 32
* @version 12/06/2018
*/

public class ParseTags extends DefaultHandler {

      /** Map que armazena as tags*/
      private Map<String,Long> tags = null;

      /**
       * Método que obtém a estrutura das tags
       */
      public Map<String,Long> gettags() {
          return tags;
      }


      /**
       * Método que inicializa o parsing das tags
       */
      @Override
      public void startElement(String uri, String localName, String qName, Attributes attributes)
              throws SAXException {
                  long idTag = 0;
                if(tags == null){
                  tags = new HashMap<String,Long>();
                }

                		if (qName.compareTo("row") == 0){
                      if(attributes.getValue("Id")!= null)
                      idTag = Long.parseLong(attributes.getValue("Id"));
                      String nomeTag = attributes.getValue("TagName");
                      tags.put(nomeTag,idTag);
                	}
      }

      /**
       * Método que finaliza o parsing das tags
       */
      @Override
      public void endElement(String uri, String localName, String qName) throws SAXException {

      }

      @Override
      public void characters(char ch[], int start, int length) throws SAXException {

      }
  }
