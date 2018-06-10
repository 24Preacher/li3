package engine;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class parser {

   public static void ParseUsers(String dumpPath) {


     SAXParserFactory factory = SAXParserFactory.newInstance();
     SAXParser saxParser2;

    try {
          SAXParser saxParser2 = factory.newSAXParser();
          saxParser.parse(PathArq, this);
          DefaultHandler handler = new DefaultHandler() {


	  public void startElement(String uri, String localName,String qName, Attributes attributes) throws SAXException {


		if (qName.compareTo("row") == 0){
			long id = Long.parseLong(attributes.getValue("ID"));
	    String bio = attributes.getValue("AboutMe");
      String nome =  attributes.getValue("DisplayName");
      int rep = Integer.parseInt(attributes.getValue("Reputation"));
	}

	public void endElement(String uri, String localName,String qName) throws SAXException {

	}


	public void characters(char ch[], int start, int length) throws SAXException {

	}
}
}
}
}


public static void ParsePosts(String dumpPath) {

     SAXParserFactory factory = SAXParserFactory.newInstance();
     SAXParser saxParser2;

    try {
          SAXParser saxParser2 = factory.newSAXParser();
          saxParser.parse(PathArq, this);
          DefaultHandler handler = new DefaultHandler() {


 public void startElement(String uri, String localName,String qName, Attributes attributes) throws SAXException {


   if (qName.compareTo("row") == 0) {
   long id = Long.parseLong(attributes.getValue("ID"));
   long ownerId = Long.parseLong(attributes.getValue("OwnerUserId"));
   long parentId = Long.parseLong(attributes.getValue("ParentId"));
   int commentCount = Integer.parseInt(attributes.getValue("CommentCount"));
   int score = Integer.parseInt(attributes.getValue("Score"));
   short postTypeId = Short.parseShor(attributes.getValue("PostTypeId"));
   int answerCount = Integer.parseInt(attributes.getValue("AnswerCount"));
   String date = attributes.getValue("CreationDate");
   DataTimeFormatter data = DataTimeFormatter.forPattern("YYYY-MM-DD");
   String tags = attributes.getValue("Tags");
   String titulo = attributes.getValue("Title");
 }

 public void endElement(String uri, String localName,String qName) throws SAXException {

 }


 public void characters(char ch[], int start, int length) throws SAXException {

 }
}
}
}
}

/*public static void main()
{
  ParseUsers("/home/helena/Downloads/dump/android/Users.xml");
  ParsePosts("/home/helena/Downloads/dump/android/Posts.xml");

}
*/
