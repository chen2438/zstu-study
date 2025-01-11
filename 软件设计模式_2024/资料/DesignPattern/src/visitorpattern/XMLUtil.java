package visitorpattern;

import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.SAXException;
import java.io.*;

public class XMLUtil
{
	public static Object getBean()
	{
		try
		{
			DocumentBuilderFactory dFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder builder = dFactory.newDocumentBuilder();
			Document doc;							
			doc = builder.parse(new File("VisitorPattern.xml")); 
			
			NodeList nl = doc.getElementsByTagName("className");
            Node classNode = nl.item(0).getFirstChild();
            String cName = classNode.getNodeValue();
            
            Class c = Class.forName(cName);
	  	    Object obj = c.getDeclaredConstructor().newInstance();
            return obj;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
}