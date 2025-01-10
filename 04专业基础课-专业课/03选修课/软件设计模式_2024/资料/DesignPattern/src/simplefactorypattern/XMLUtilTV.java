package simplefactorypattern;

import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.SAXException;
import java.io.*;

public class XMLUtilTV
{
	public static String getBrandName()
	{
		try
		{
			DocumentBuilderFactory dFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder builder = dFactory.newDocumentBuilder();
			Document doc;							
			doc = builder.parse(new File("SimpleFactoryPattern.xml")); 
		
			NodeList nl = doc.getElementsByTagName("brandName");
            Node classNode = nl.item(0).getFirstChild();
            String brandName = classNode.getNodeValue().trim();
            return brandName;
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
}