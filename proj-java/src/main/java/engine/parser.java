package engine;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class parser {

   public static void ParseUsers(String argv[]) {

    try {

	SAXParserFactory factory = SAXParserFactory.newInstance();
	SAXParser saxParser = factory.newSAXParser();

	DefaultHandler handler = new DefaultHandler() {

	boolean bid = false;
	boolean bbio = false;
	boolean bname = false;
  boolean brep = false;



	public void startElement(String uri, String localName,String qName, Attributes attributes) throws SAXException {


		if (qName.equalsIgnoreCase("Id")) {
			bid = true;
		}

		if (qName.equalsIgnoreCase("AboutMe")) {
			bbio = true;
		}

		if (qName.equalsIgnoreCase("DisplayName")) {
			bname = true;
		}

		if (qName.equalsIgnoreCase("Reputation")) {
			brep = true;
		}

	}

	public void endElement(String uri, String localName,String qName) throws SAXException {

	}


	public void characters(char ch[], int start, int length) throws SAXException {

		if (bid) {
			System.out.println("ID : " + new String(ch, start, length));
			bid = false;
		}

		if (bbio) {
			System.out.println("Bio : " + new String(ch, start, length));
			bbio = false;
		}

		if (bname) {
			System.out.println("Nome : " + new String(ch, start, length));
			bname = false;
		}

		if (brep) {
			System.out.println("Reputação : " + new String(ch, start, length));
			brep = false;
		}

	}

     };

       saxParser.parse("c:\\Users.xml", handler);

     } catch (Exception e) {
       e.printStackTrace();
     }

   }





   public static void ParsePosts(String argv[]) {

    try {

 SAXParserFactory factory = SAXParserFactory.newInstance();
 SAXParser saxParser = factory.newSAXParser();

 DefaultHandler handler = new DefaultHandler() {

 boolean bid = false;
 boolean bownerid = false;
 boolean bparentid = false;
  boolean bcommentcout = false;
  boolean bscore = false;
  boolean bposttype = false;
  boolean banswercount = false;
  boolean bcreationdate = false;
  boolean btags = false;
  boolean btitle = false;



 public void startElement(String uri, String localName,String qName, Attributes attributes) throws SAXException {


   if (qName.equalsIgnoreCase("Id")) {
     bid = true;
   }

   if (qName.equalsIgnoreCase("OwnerUserId")) {
     bownerid = true;
   }

   if (qName.equalsIgnoreCase("ParentId")) {
     bparentid = true;
   }

   if (qName.equalsIgnoreCase("CommentCount")) {
     bcommentcout = true;
   }

    if (qName.equalsIgnoreCase("Score")) {
     bscore = true;
   }

    if (qName.equalsIgnoreCase("PostTypeId")) {
     bposttype = true;
   }

    if (qName.equalsIgnoreCase("AnswerCount")) {
     banswercount = true;
   }

    if (qName.equalsIgnoreCase("CreationDate")) {
     bcreationdate = true;
   }

    if (qName.equalsIgnoreCase("Tags")) {
     btags = true;
   }

    if (qName.equalsIgnoreCase("Title")) {
     btitle = true;
   }



 }

 public void endElement(String uri, String localName,String qName) throws SAXException {

 }


 public void characters(char ch[], int start, int length) throws SAXException {

   if (bid) {
     System.out.println("PostId : " + new String(ch, start, length));
     bid = false;
   }

   if (bownerid) {
     System.out.println("OwnerId : " + new String(ch, start, length));
     bownerid = false;
   }

   if (bparentid) {
     System.out.println("ParentId : " + new String(ch, start, length));
     bparentid = false;
   }

   if (bcommentcout) {
     System.out.println("CommentCount : " + new String(ch, start, length));
     bcommentcout = false;
   }

    if (bscore) {
     System.out.println("Score : " + new String(ch, start, length));
     bscore = false;
   }

    if (bposttype) {
     System.out.println("PostTypeId : " + new String(ch, start, length));
     bposttype = false;
   }

    if (banswercount) {
     System.out.println("AnswerCount : " + new String(ch, start, length));
     banswercount = false;
   }

    if (bcreationdate) {
     System.out.println("CreationDate : " + new String(ch, start, length));
     bcreationdate = false;
   }

    if (btags) {
     System.out.println("Tags : " + new String(ch, start, length));
     btags = false;
   }

    if (btitle) {
     System.out.println("Title : " + new String(ch, start, length));
     btitle = false;
   }

 }

     };

       saxParser.parse("c:\\Posts.xml", handler);

     } catch (Exception e) {
       e.printStackTrace();
     }

   }


}
