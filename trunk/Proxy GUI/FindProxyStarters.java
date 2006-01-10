import java.io.*;
import java.util.*;

import org.jdom.*;
import org.jdom.input.SAXBuilder;

import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;

	public class FindProxyStarters {

	  public List<File> files = new ArrayList<File>( 1024 );
	  private ProxyTree _proxyTree;// = new ProxyTree();
	  private SAXBuilder builder = new SAXBuilder();
	  private String os_extension;
	  
	  public FindProxyStarters (){//File startdir, String fileName, ProxyTree proxyTree)  
	  
		  //This method recursively searches a starting directory for
		  // subdirectories including Event Heap proxy files
		  // These directories are in this approach indicated by
		  // an XML-file defined by the parameter "filename"
		  // The XML files are used for later purposes as comments or
		  // different start files
		  // TODO Add a check wether the proxy can be run under the current OS
		  // idea: search if there is a file Exec.Prefix.bat or .sh
		  
		  // check the current OS the Proxy Starter is running under
		  // and set the corresponding file extension
		  String osName = System.getProperty("os.name");
		  if (osName.contains("Windows"))
			  os_extension = ".bat";
		  else
			  os_extension = ".sh";
		  
		  _proxyTree = new ProxyTree();
	  }
	  
	  public ProxyTree getProxyTree (File startDir, String searchFileName){
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
	        		//NOTE: The XML-reading works.
	        		// TODO: Now a way to precheck the XML descriptions is needed.
	        		// That can be postponed
	        		
	        		
	        		ProxyNode newNode = new ProxyNode();
	        		Element xmlFileRoot = docForNode.getRootElement();
	        		String execPrefix = xmlFileRoot.getChildText("execPrefix");
	        		
	        		// Check wether the proxy can be run at all
	        		for ( File searchFile : currentDir.listFiles() )
	        		{
	        			if (searchFile.getName().equals(execPrefix.concat(os_extension)))//== ("run.bat"));//execPrefix.concat(".bat")));
	        			{
	        				System.out.println("EQUALS!!!   " + searchFile.getName() + " equals " + execPrefix.concat(".bat"));
	        				
	        				
	        				// Fill the node with information
	        				newNode.setName(xmlFileRoot.getChildText("name"));
	        				newNode.setKind(xmlFileRoot.getChildText("kind"));
	        				newNode.setExecutableName(execPrefix);
	        				newNode.setproxyClass(xmlFileRoot.getChildText("proxyClass"));
	        				newNode.setComment(xmlFileRoot.getChildText("comment"));
	        				newNode.setPathToFile(file);
	        				
	        				// Now the new node is completeand is insertet into the tree.
	        				_proxyTree.insertNode(newNode);
	        				
	        				//Maybe I can make use of the other constructor later when
	        				// directly reading out the XML tags.
	        				//With this tree model it will also be possible to add
	        				// other directories including proxies, too
	        				// The tree abstracts from the actual location on the hard drive
	        				// because it makes use of the XML files.
	        				// For the user, only information directly concerning the
	        				// proxies is relevant.
	        			}
	        		}
	        	}
	      	}
	     }
	    
	    // The following loops are only for debugging purposes
	    // They print out inserted proxies 
	    for ( Iterator<ProxyNode> i = _proxyTree.getTreeRoot().getSuccessors().iterator(); i.hasNext();)
	    {
	    	ProxyNode temp = (ProxyNode) i.next();
	    	System.out.println("Kind found: " + temp.getKind());
	    	//Iterator iii = temp.getSuccessors().iterator();
	    	for (Iterator<ProxyNode> i2 = temp.getSuccessors().iterator(); i2.hasNext();)
	    	{
	    		ProxyNode temp2 = (ProxyNode) i2.next();
	    		System.out.println("ProxyClass found: " + temp2.getproxyClass());
	    		for (Iterator<ProxyNode> i3 = temp2.getSuccessors().iterator(); i3.hasNext();)
	    		{
	    			ProxyNode temp3 = (ProxyNode) i3.next();
	    			System.out.println("Proxy found: " + temp3.getName());
	    		}
	    	}
	    	
	    }
	    return _proxyTree;
	  }
	
	  public List<File> getFoundFiles () {
		  return files;
	  }
	  	  
	  public JTree getTreeStructure (){
		  DefaultMutableTreeNode root = new DefaultMutableTreeNode ("Reiny's Proxy Launcher");
		  JTree structureTree = new JTree(root);
		  DefaultMutableTreeNode node1 = new DefaultMutableTreeNode("EBENE1");
		  root.add(node1);
		  //structureTree.add(root);
		  
		  return structureTree;
	  }
	  

	}
	
	
	
	
	/*  public void print()
	  {
	    System.out.println( "Found " + files.size() + " file" +
	                         (files.size() == 1 ? "." : "s.") );

	    for ( File f : files )
	      System.out.println( f.getAbsolutePath() );
	  }
*/
	/*  private static boolean match( String s, String suffixes[] ) 
//	 In Java 5 ... m�glich
	  {
	   /* for ( String suffix : suffixes )
	      if ( s.length() >= suffix.length() &&
	           //s.substring(s.length() � suffix.length(),
	                       s.length()).equalsIgnoreCase(suffix) )*/
	  //      return true;

	    //return false;
	  //}*/
	