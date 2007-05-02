import javax.swing.JOptionPane;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.output.Format;
import org.jdom.output.XMLOutputter;


/*
 * CreateConfigFile.java
 *
 * Created on February 27, 2007, 5:01 PM by Siddhu
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 * Class: CreateConfigFile
 * Author: Siddhu
 * Function: The first time the application is run on any computer, there is no Configstarter.xml, and this class' constructor is used
 * to create the XML file. 
 */
public class CreateConfigFile {
    boolean success;
    /** Creates a new instance of CreateConfigFile */
    public CreateConfigFile() {
       success = saveConfigFile();
       if(!success)
           JOptionPane.showMessageDialog(null,"Error. Configuration file was not created. Are you sure you have write privileges on this folder?");
    }
    /* Method: saveConfigFile()
     * Function: Creates XML file called ConfigStarter.xml, and  saves it. Called whenever the app is executed the first time on any computer
     * Author: Siddhu
     */
    public boolean saveConfigFile()
    {
        //File configFile = new File("configStarter.xml");
        // save the xml inside the userdir
        try
        {
        	String path = System.getProperty("user.dir");
        	if      (System.getProperty("os.name").contains("Mac"))
        			path = path+"/Library/iStuff/";
        	else if (System.getProperty("os.name").contains("Linux"))
        			path = path+"/.iStuff/";
        	else		path = path+"\\iStuff\\";
        	File configFile = new File(path+"configStarter.xml");
        	File configPath = new File(path);
        	
        	System.out.println("File to save: "+configFile.toURL()+"\nin path: "+path);
        	
        	if (!configPath.mkdirs()){
        	JOptionPane.showMessageDialog(null,
        		"Could not create the default configuration folder inside the user-space.");
        	}
        	else System.out.println("Created the directory-tree: "+configPath.toURL());
        
        
            /* create an XML file with the following format
             * <Configuration>
             *      <Libraries>
             *          <iROS>...</iROS>
             *          <JmDNS>...</JmDNS>
             *      </Libraries>
             *      <SearchDirectories>
             *          <directory>...</directory>
             *          <directory>...</directory>
             *          .
             *          .
             *          .
             *      </SearchDirectories>
             * </Configuration>
             * where ... = user directory/lib
             */
            
            Element root = new Element ("Configuration");
            Document configDoc = new Document(root);
            // Now add all the settings:
            root.addContent(new Element ("Libraries"));
            root.addContent(new Element ("SearchDirectories"));
		
            Element libraries =  root.getChild("Libraries");
            
            //if OS the app is running on is MacOS or Linux, then use the forward slash, if not using backward slash.
            if ((System.getProperty("os.name").contains("Mac")) || (System.getProperty("os.name").contains("Linux")))
            {
                libraries.addContent((new Element ("iROS")).addContent(""+ System.getProperty("user.dir") + "/"));
                libraries.addContent((new Element ("JmDNS")).addContent(""+ System.getProperty("user.dir") + "/"));
            }
            else
            {
                libraries.addContent((new Element ("iROS")).addContent(""+ System.getProperty("user.dir") + "\\"));
                libraries.addContent((new Element ("JmDNS")).addContent(""+ System.getProperty("user.dir") + "\\"));

            }
            
            //now add the search directories
            Element searchDirs = root.getChild("SearchDirectories");
            
            //if OS the app is running on is MacOS or Linux, then use the forward slash, if not using backward slash.
            if ((System.getProperty("os.name").contains("Mac")) || (System.getProperty("os.name").contains("Linux")))
            {
//                searchDirs.addContent((new Element ("directory")).addContent(""+ System.getProperty("user.dir") + "/Hardware Proxies"));
//                searchDirs.addContent((new Element ("directory")).addContent(""+ System.getProperty("user.dir") + "/Software Proxies"));
                searchDirs.addContent((new Element ("directory")).addContent("./Hardware Proxies"));
                searchDirs.addContent((new Element ("directory")).addContent("./Software Proxies"));
            }
            else
            {
//                searchDirs.addContent((new Element ("directory")).addContent(""+ System.getProperty("user.dir") + "\\Hardware Proxies"));
//                searchDirs.addContent((new Element ("directory")).addContent(""+ System.getProperty("user.dir") + "\\Software Proxies"));
                searchDirs.addContent((new Element ("directory")).addContent(".\\Hardware Proxies"));
                searchDirs.addContent((new Element ("directory")).addContent(".\\Software Proxies"));
            }
            
            //Commit the new configstarter.xml file.
            XMLOutputter outputter = new XMLOutputter(Format.getPrettyFormat());
            FileWriter writer = new FileWriter(configFile);
	    outputter.output(configDoc,writer);
	    writer.close();
        }
        catch(IOException e)
        {
            return false; //failure. Return false. The Constructor will display the error message. Q: Is it bad to include this kinda code in the constructor?
        }
        return true; //Yay!
    }
}
