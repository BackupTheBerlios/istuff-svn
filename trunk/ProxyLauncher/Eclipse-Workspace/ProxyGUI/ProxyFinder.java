import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Stack;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.input.SAXBuilder;

	public class ProxyFinder {

	  public List<File> files = new ArrayList<File>();
	  private ProxyTree _proxyTree;
	  private SAXBuilder builder = new SAXBuilder();
	 
	  public ProxyFinder () {
		  _proxyTree = new ProxyTree();
	  }
	  
	  public ProxyTree getProxyTree (File startDir, String searchFileName){
		  //	 This method recursively searches a starting directory for
		  // subdirectories including Event Heap proxy files
		  // described by xml files in each directory.
		  List<Element> customLibs;
		  Element xmlFileRoot;
		  ProxyNode newNode;
		  Stack<File> dirs = new Stack<File>();
		  
	      if ( startDir.isDirectory() )
	      dirs.push( startDir);
	     
	    while ( dirs.size() > 0 )
	    {
	      File currentDir = dirs.pop();
	      // Insert current directory as a node node into the tree
	      for ( File file : currentDir.listFiles() )
	      {
	        if ( file.isDirectory() )
	        	dirs.push( file ); 
	        else
	        	if ( file.getName().equals(searchFileName))
	        	{
	        		files.add( file );
	        		// Here the XML tags should be inserted in the tree structure
	        		Document docForNode = new Document();
	        		try {
	        			docForNode = builder.build(file);
	        		} catch (Exception e) {
	        			System.out.println("Problem with the XML-File: " + file 
	        					+ ". File could not be read");
	        		}
	        		
	        		// TODO: Now a way to precheck the XML descriptions is needed.
	        		
	        		newNode = new ProxyNode();
	        		xmlFileRoot = docForNode.getRootElement();
	        		customLibs = xmlFileRoot.getChild("CustomLibs").getChildren();
	        		// Check wether the proxy can be run at all
	        				// Fill the node with information
	        	 			newNode.setName(xmlFileRoot.getChildText("name"));
	        	 			newNode.setKind(xmlFileRoot.getChildText("kind"));
	        	 			newNode.setClassName(xmlFileRoot.getChildText("ClassName"));
	        				newNode.setproxyClass(xmlFileRoot.getChildText("proxyClass"));
	        	 			newNode.setComment(xmlFileRoot.getChildText("comment"));
	        	 			newNode.setPathToFile(file.getParentFile().toString() + File.separatorChar);
	        	 			
	        	 			for (int i = 0; i != customLibs.size(); i++)
	        	 				newNode.addLibToList(customLibs.get(i).getValue());
	        	 			
	        	 			// Now the new node is complete is insertet into the tree.
	        	 			_proxyTree.insertNode(newNode);
	         }
	      }
	    }
	    
	    return _proxyTree;
	  }
	
	  public List<File> getFoundFiles () {
		  return files;
	  }
	  	  
} // end of class
