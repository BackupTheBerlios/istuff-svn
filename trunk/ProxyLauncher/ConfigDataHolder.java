import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Vector;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;

public class ConfigDataHolder {
	
	private static Element _xmlRoot;
	
	public static boolean existsConfigFile () {
		File configFile = new File ("configStarter.xml");
			return configFile.exists();
	}
	
	private static void loadXMLFile () {
			// Load the configuration file
			try {
				File configFile = new File("configStarter.xml");
				Document docWithConfig;// = new Document();
				SAXBuilder builder = new SAXBuilder();
				docWithConfig = builder.build(configFile);
				_xmlRoot = docWithConfig.getRootElement();
			} catch (JDOMException e) {
				System.out.println("The XML - file may be corrupt");
			} 
			catch (IOException e) {
				System.out.println("No configFile found. New file created");
			}
	}
	public static Vector <File> getSearchDirectories () {
		Vector <File> searchDirectories = new Vector <File> ();
		List directories = getXMLChildren ("SearchDirectories");
		if (directories != null)
			for (int i=0; i < directories.size(); i++) {
				Element currentElement = (Element) directories.get(i);
				File newDirectory = new File(currentElement.getValue());
				searchDirectories.add(newDirectory);
				}			
		return searchDirectories;
	}
	
	public static String getIrosLocation () {
		try {
			Element libs = getXMLChildValue ("Libraries");
				return libs.getChild("iROS").getValue();
		} catch (NullPointerException e) {
			System.out.println("iRos Entry was not found. Please check the preferences");
		}
		return null;
	}
	
	public static String getJmdnsLocation () {
		try {
			Element libs = getXMLChildValue ("Libraries");
			return libs.getChild("JmDNS").getValue();
		} catch (NullPointerException e) {
			System.out.println("JmDNS Entry was not found. Please check the preferences");
		}
		return null;
	}
	
	private static List getXMLChildren (String childName) {
		loadXMLFile();
		if (_xmlRoot != null) {
			Element searchedElement = _xmlRoot.getChild(childName);
			if (searchedElement != null) {
				List children = searchedElement.getChildren();
				return children;
			}
		}
		return null;
	}
	
	private static Element getXMLChildValue (String childName) {
		loadXMLFile();
		if (_xmlRoot != null) {
			return _xmlRoot.getChild(childName);
		}
		return null;
	}
	
	public static String getCommandSeparator () {
		if (System.getProperty("os.name").contains("Windows"))
			return ";";
		else
			return ":";
	}

}

