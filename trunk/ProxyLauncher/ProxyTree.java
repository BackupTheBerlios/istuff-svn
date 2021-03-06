import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Stack;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.input.SAXBuilder;

public class ProxyTree {

	private SAXBuilder _builder = new SAXBuilder();
	private ProxyNode _treeRoot;

	private ProxyNode currentNode;

	public ProxyTree() {
		_treeRoot = new ProxyNode();
		_treeRoot.setKind("RootProxy");
		_treeRoot.setName("EH Proxies");
		_treeRoot.setproxyClass("Virtual");
	}

	public void insertNode(ProxyNode node) {
		// Insert alphabetically
		ProxyNode predecessorNode;
		predecessorNode = searchPredecessorNode(_treeRoot, node);
		if (predecessorNode != null)
			predecessorNode.addSuccessor(node);
	}

	private ProxyNode searchPredecessorNode(ProxyNode startNode,
			ProxyNode searchNode) {
		for (Iterator<ProxyNode> i = startNode.getSuccessors().iterator(); i
				.hasNext();) {
			ProxyNode compareKindNode = (ProxyNode) i.next();
			// check if kind is already there
			if (compareKindNode.getKind().equals(searchNode.getKind())) {
				// If the kind already exists, check wether the proxy class
				// already exists
				for (ListIterator<ProxyNode> it = compareKindNode
						.getSuccessors().listIterator(); it.hasNext();) {
					ProxyNode compareProxyClassNode = it.next();
					if (compareProxyClassNode.getProxyClass().equals(
							searchNode.getProxyClass())) {
						// Now also check if a node with the same FilePath
						// is already in the tree
						for (Iterator<ProxyNode> proxyIterator = compareProxyClassNode
								.getSuccessors().iterator(); proxyIterator
								.hasNext();) {
							ProxyNode compareProxy = proxyIterator.next();
							if (compareProxy.getPathToFile().equals(
									searchNode.getPathToFile())) {
								// This means that the same node is already in
								// the tree
								return null;
							}

						}
						return compareProxyClassNode;
						// if the node does not exist in the tree, return the
						// ProxyClassNode
						// there the new node should be inserted
						// return compareKindNode;
					}

				}
				// No ProxyClass found --> Create a new one

				// Return the ProxyClassNode and insert the new node

				ProxyNode newProxyClassNode = new ProxyNode(searchNode
						.getKind(), searchNode.getProxyClass(), searchNode
						.getProxyClass(), "");
				// if the ProxyClass does not exist yet, create it
				// and return the newly created node
				compareKindNode.addSuccessor(newProxyClassNode);
				return newProxyClassNode;
			}

		}
		// In the case that the kind does not exist,
		// create new kind and proxyclass
		ProxyNode newKindNode = new ProxyNode(searchNode.getKind(), searchNode
				.getKind(), searchNode.getKind(), "");
		startNode.addSuccessor(newKindNode);
		// Now a new proxClass needs to be created as well
		// This can directly be done because the new node has no successors
		ProxyNode newProxyClassNode = new ProxyNode(searchNode.getKind(),
				searchNode.getProxyClass(), searchNode.getProxyClass(), "");
		newKindNode.addSuccessor(newProxyClassNode);
		return newProxyClassNode;
	}
	
	

	public boolean isInTree(ProxyNode searchNode) {
		for (Iterator<ProxyNode> kindIterator = getRoot().getSuccessors()
				.iterator(); kindIterator.hasNext();) {
			ProxyNode compareKindNode = (ProxyNode) kindIterator.next();
			// check if kind is already there
			if (compareKindNode.getKind().equals(searchNode.getKind()))
				return (true);
			// If the node as kind does not exists, check wether the
			// node is a proxy class
			for (Iterator<ProxyNode> pClassIterator = compareKindNode
					.getSuccessors().iterator(); pClassIterator.hasNext();) {
				ProxyNode compareProxyClassNode = (ProxyNode) pClassIterator
						.next();
				if (compareProxyClassNode.getProxyClass().equals(
						searchNode.getProxyClass()))
					return (true);
				for (Iterator<ProxyNode> proxyIterator = compareKindNode
						.getSuccessors().iterator(); proxyIterator.hasNext();) {
					ProxyNode compareProxyNode = (ProxyNode) proxyIterator
							.next();
					if (compareProxyNode.getName().equals(searchNode.getName()))
						;
					return (true);
				}
			}
		}
		return false;
	}

	public ProxyNode searchNode(ProxyNode searchNode) {
		ProxyNode currentNode = getRoot();
		if (!searchNode.equals(currentNode)) {
			for (Iterator<ProxyNode> i = currentNode.getSuccessors().iterator(); i
			.hasNext();) {
				currentNode = i.next();
				if (!searchNode.equals(currentNode)){
					for (Iterator<ProxyNode> i2 = currentNode.getSuccessors().iterator(); i2
					.hasNext();) {
						currentNode = i2.next();
						if (!searchNode.equals(currentNode)){
							for (Iterator<ProxyNode> i3 = currentNode.getSuccessors().iterator(); i3
							.hasNext();) {
								currentNode = i3.next();
								if (searchNode.equals(currentNode)){
									return currentNode;
								}
							}
						}
						else return currentNode;
					}
				}
				else return currentNode;
			}
		}
		else return currentNode;
		
		return null; // This happens if the node was not found.
	}
	
	public ProxyNode searchNodeClass(String className) {
		ProxyNode currentNode = getRoot();
		if (!className.equals(currentNode.getClassName())) {
			for (Iterator<ProxyNode> i = currentNode.getSuccessors().iterator(); i
			.hasNext();) {
				currentNode = i.next();
				if (!className.equals(currentNode.getClassName())){
					for (Iterator<ProxyNode> i2 = currentNode.getSuccessors().iterator(); i2
					.hasNext();) {
						currentNode = i2.next();
						if (!className.equals(currentNode.getClassName())){
							for (Iterator<ProxyNode> i3 = currentNode.getSuccessors().iterator(); i3
							.hasNext();) {
								currentNode = i3.next();
								if (className.equals(currentNode.getClassName())){
									return currentNode;
								}
							}
						}
						else return currentNode;
					}
				}
				else return currentNode;
			}
		}
		else return currentNode;
		
		return null; // This happens if the node was not found.
	}
		
	public ProxyNode getRoot() {
		return _treeRoot;
	}

	public ProxyNode getCurrentNode() {
		return currentNode;
	}
	
	public void addProxyDirectory (File startDir){
		  //	 This method recursively searches a starting directory for
		  // subdirectories including Event Heap proxy files
		  // described by xml files in each directory.
		String searchFileName = "proxy-description.xml";
		ProxyNode newNode;  
		List<File> files = new ArrayList<File>();
		  List customLibs;
		  List additionalParameters;
		  Element xmlFileRoot;
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
	        			docForNode = _builder.build(file);
	        			newNode = new ProxyNode();
	        			xmlFileRoot = docForNode.getRootElement();
	        			customLibs = xmlFileRoot.getChild("CustomLibs").getChildren();
	        			additionalParameters = xmlFileRoot.getChild("AdditionalParameters").getChildren();
	        				// Fill the node with information
	        				String stringWithoutSpaces = (xmlFileRoot.getChildText("name"));
	        				newNode.setName(stringWithoutSpaces.replaceAll(" ","_"));
	        	 			newNode.setKind(xmlFileRoot.getChildText("kind"));
	        	 			newNode.setClassName(xmlFileRoot.getChildText("ClassName"));
	        				newNode.setproxyClass(xmlFileRoot.getChildText("proxyClass"));
	        	 			newNode.setComment(xmlFileRoot.getChildText("comment"));
	        	 			newNode.setPathToFile(file.getParentFile().toString() + File.separatorChar);
	        	 			
	        	 			for (int i = 0; i != customLibs.size(); i++){
	        	 				newNode.addLibToList(((Element) customLibs.get(i)).getValue());
	        	 			}
	        	 			System.out.println(newNode.getName()+": "+ customLibs);
	        	 			for (int i = 0; i != additionalParameters.size(); i++){
	        	 				newNode.addParameterToList(((Element) additionalParameters.get(i)).getValue());
	        	 			}

	        	 			// Now the new node is complete is insertet into the tree.
	        	 			insertNode(newNode);
	        		} catch (Exception e) {
	        			System.out.println("Problem with the XML-File: " + file 
	        					+ ". File could not be read \n"
	        					+ "Proxy was not inserted");
	        			e.printStackTrace();
	        		}
	         }
	      }
	    }
	}

	public Object getChild(Object parentObject, int index) {
		ProxyNode parent = (ProxyNode) parentObject;
		ProxyNode child = searchNode(parent);
		try {
			return child.getSuccessors().get(index);
		} catch (Exception e){
			return null;
		}
	}

	public int getChildCount(Object parentObject) {
		ProxyNode parent = (ProxyNode) parentObject;
		ProxyNode result = searchNode(parent);
		if (result != null)
			return searchNode(parent).getSuccessors().size();
		else
			return 0;
	}

	public boolean isLeaf(Object nodeObject) {
		ProxyNode node = (ProxyNode) nodeObject;
		ProxyNode result = searchNode(node);
		if (result != null)
			return node.hasSuccessors();
		else
			return false;
	}
	
}
