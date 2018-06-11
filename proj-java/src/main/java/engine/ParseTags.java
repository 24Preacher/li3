package engine;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class ParseTags extends DefaultHandler {


      private HashMap<String,Long> tags = null;
      private Tags t = null;

      public Map<String,Long> gettags() {
          return tags;
      }


      @Override
      public void startElement(String uri, String localName, String qName, Attributes attributes)
              throws SAXException {
                if(tags == null){
                  tags = new HashMap<String,Long>();
                }

                		if (qName.compareTo("row") == 0){
                      if(attributes.getValue("ID")!= null)
                      long idTag = Long.parseLong(attributes.getValue("ID"));
                      String nomeTag = attributes.getValue("TagName");
                      tags.put(nomeTag,idTag);
                	}
      }

      @Override
      public void endElement(String uri, String localName, String qName) throws SAXException {

      }

      @Override
      public void characters(char ch[], int start, int length) throws SAXException {

      }
  }
