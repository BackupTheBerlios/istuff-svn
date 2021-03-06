import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.TreeSet;
import java.io.*;
import javax.swing.event.EventListenerList;

import org.jdom.Element;

public class ProxyNode implements Cloneable, ActionListener {

	private String _kind; // Hardware, Software, Category
	private String _name; // Name of the Proxy / Category
	private String _proxyClass; // Class that the Proxy belongs to
	private String _className; // Prefix of the executable
	private String _comment;
	private String _pathToFile;
	private String _proxyID;
	private ArrayList <String> _customLibs;
	private ArrayList <String> _additionalParameters;
	private LinkedList<ProxyNode> _successors;
	private ListIterator<ProxyNode> _si;
	private boolean _isNew;
	private boolean _running;
	private ProxyThread _correspondingThread;
	private int _instanceNumber = 0;
    protected EventListenerList _myListenerList =
		new EventListenerList();
    protected TreeSet _instanceNumbers = new TreeSet();
	
	public ProxyNode() {
		_successors = new LinkedList<ProxyNode>();
		_si = _successors.listIterator();
		_isNew = true;
		_running = false;
		_customLibs = new ArrayList<String>();
		_additionalParameters = new ArrayList<String>();
		//_instanceNumbers = new TreeSet();
	}
	
	public ProxyNode(String kind, String name, String proxyClass,
			String className) {
		_successors = new LinkedList<ProxyNode>();
		_si	= _successors.listIterator();
		_kind = kind;
		_name = name;
		_proxyClass = proxyClass;
		_className = className;
		_isNew = true;
		_running = false;
		_customLibs = new ArrayList<String>();
		_additionalParameters = new ArrayList<String>();
		_proxyID = _name + "ID";
		//_instanceNumbers = new TreeSet();
	}

	
	public void addLibToList (String relativePath){
		_customLibs.add(relativePath);
	}
	
	public void addParameterToList (String parameter) {
		_additionalParameters.add(parameter);
	}
	
	public ArrayList <String> getCustomLibs () {
		return _customLibs;
	}
	
	public ArrayList <String> getAdditionalParameters () {
		return _additionalParameters;
	}
	
	public void setKind(String kind) {
		_kind = kind;
	}

	public void setName(String name) {
		_name = name;
		_proxyID = _name + "_";
	}

	public void setproxyClass(String proxyClass) {
		_proxyClass = proxyClass;
	}

	public void setClassName(String className) {
		_className = className;
	}

	public String getKind() {
		return _kind;
	}

	public String getName() {
		return _name;
	}

	public String getProxyClass() {
		return _proxyClass;
	}

	public String getClassName() {
		return _className;
	}

	public void setComment(String comment) {
		_comment = comment;
	}

	public void addSuccessor(ProxyNode successor) {
		// Add elements in a sorted way:
		// idea: go through the list and if a an element is larger
		// than the one to be inserted, insert the new element in front
		// of the larger element.
		// Otherwise insert the element at the end of the list

		ListIterator<ProxyNode> iter = getSuccessors().listIterator();
		if (iter.hasNext()) {
			// ProxyNode currentNode = iter.next();
		}

		while (iter.hasNext()) {
			if (successor.getName().compareTo(iter.next().getName()) < 0) {
				iter.previous();
				break;
			}
		}
		// The correct place for the new element was found
		// Now add the element
		iter.add(successor);
	}

	public String getComment() {
		return _comment;
	}

	public ProxyNode getNext() {
		if (_si.hasNext())
			return _si.next();
		return null;
	}

	public LinkedList<ProxyNode> getSuccessors() {
		return _successors;
	}

	public ListIterator<ProxyNode> getIterator() {
		return _si;
	}

	public boolean hasSuccessors() {
		if (_successors.isEmpty()) {
			System.out.println("Has no successors " + this);
			return false;
		}
		else{
			System.out.println("Has succesors " + getSuccessors());
		
			return true;
			}
	}

	public void setPathToFile(String pathToFile) {
		_pathToFile = pathToFile;
	}

	public String getPathToFile() {
		return _pathToFile;
	}

	public boolean isRunning() {
		return _running;
	}

	public void setIsRunning(boolean running) {
		_running = running;
	}

	public void setIsNew(boolean bool) {
		_isNew = bool;
	}

	public boolean isNew() {
		return (_isNew);
	}

	public void startProxy(String eventHeap) throws IOException {
		_running = true;
		// File is found
		
		// Construct the launch command:
		String libs = "";
		String additionalParameters = "";
		
		// If there are custom libraries needed for a proxy, they are in an ArrayList
		// inside the proxyNode. That "customLibraryPath" has to be constructed.
		String separator = ConfigDataHolder.getCommandSeparator();
		
		// It must be differentiated between the different OS because the syntax
		// of the JAVA Compiler call is a little different.
		if (getCustomLibs().get(0).equals("")){
			System.out.println(getCustomLibs()+"Libs empty");
			libs = "";
		}
		else
			for (int i = 0; i < getCustomLibs().size(); i++){
					libs = libs + getCustomLibs().get(i) + separator;
					System.out.println("Libs: "+ libs);
			}
			
		// Get additional parameters from the list
		if (getAdditionalParameters().get(0).equals("")){
			System.out.println("Paramtersempty");
			System.out.println(getAdditionalParameters());
			additionalParameters = "";
		}
		else
			for	(int i = 0; i < getAdditionalParameters().size(); i++)
				additionalParameters = additionalParameters + getAdditionalParameters().get(i) + " ";
		
		String myPath = "";
		try{
			myPath = new File(".").toURL().toString();
			myPath = myPath.substring(5);
		}
		catch(Exception e){
		
		}
		String launchCommand2= "java -classpath "
			+ myPath + "iStuff.jar"
			+ separator
			+ libs
			+ ". "
			+ getClassName()
			+ " " 
			+ eventHeap  // first parameter Event Heap to connect to
			+ " "
			+ additionalParameters
			//+ " "
			+ getProxyID();  // second optional parameter ProxyID
			
		String launchCommand = "java -classpath "
			+ ConfigDataHolder.getIrosLocation()
			+ separator
			+ libs
			+ ". "
			+ getClassName()
			+ " " 
			+ eventHeap  // first parameter Event Heap to connect to
			+ " "
			+ additionalParameters
			//+ " "
			+ getProxyID();  // second optional parameter ProxyID
			
		_correspondingThread = new ProxyThread(launchCommand2, getPathToFile());
		_correspondingThread.start();
	}

	public void stopProxy() {
		try {
			if (_correspondingThread != null)
				_correspondingThread.kill();
		} catch (Exception err) {
			err.printStackTrace();
		}
	}

	public ProxyThread getCorrespondingThread() {
		return _correspondingThread;
	}

	public String getProxyID() {
		return _proxyID;
	}

	public void setProxyID(String proxyid) {
		_proxyID = proxyid;
	}
	
	public String toString() {
			return _name;
	}
	
	public ProxyNode clone () {
		int i = 1;
		while (_instanceNumbers.contains(i)){
			i++;
		}
		_instanceNumbers.add(i);
		
		ProxyNode cloneNode = new ProxyNode ();
		cloneNode.setClassName(_className);
		cloneNode.setComment(_comment);
		cloneNode.setIsNew(_isNew);
		cloneNode.setIsRunning(_running);
		cloneNode.setKind(_kind);
		cloneNode.setName(_name);
		cloneNode.setPathToFile(_pathToFile);
		cloneNode.setproxyClass(_proxyClass);
		cloneNode.setProxyID(_proxyID + i);
		cloneNode._customLibs= _customLibs;
		cloneNode._additionalParameters = _additionalParameters;
		cloneNode._instanceNumber = i;
		
		return cloneNode;
	}
	
	public int getInstanceNumber () {
		return _instanceNumber;
	}

	
    // This method allows other classes to register for MyEvents
    public void addProxyDecreaseInstanceListener(ActionListener listener) {
    		_myListenerList.add(ActionListener.class, listener);
    }

	public void actionPerformed(ActionEvent arg0) {
		Integer number = (Integer) arg0.getSource();
		_instanceNumbers.remove(number);
	}
	
	public void fireEventRemoved () {
		FireActionEvent.fireEvent (new ActionEvent (new Integer(_instanceNumber),
				ActionEvent.ACTION_PERFORMED,"Remove instance number"), _myListenerList);
	}
}
