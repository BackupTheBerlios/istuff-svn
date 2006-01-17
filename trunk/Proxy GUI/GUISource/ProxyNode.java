import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Vector;

public class ProxyNode {

	private String _kind; // Hardware, Software, Category
	private String _name; // Name of the Proxy / Category
	private String _proxyClass; // Class that the Proxy belongs to
	private String _className; // Prefix of the executable
	private String _comment;
	private String _pathToFile;
	private ArrayList <String> _customLibs;
	private LinkedList<ProxyNode> _successors;
	private ListIterator<ProxyNode> _si;
	private boolean _isNew;
	private boolean _running;
	private ProxyThread _correspondingThread;

	public ProxyNode() {
		_successors = new LinkedList<ProxyNode>();
		_si = _successors.listIterator();
		_isNew = true;
		_running = false;
		_customLibs = new ArrayList<String>();
	}

	public ProxyNode(String kind, String name, String proxyClass,
			String className) {
		_successors = new LinkedList<ProxyNode>();
		_si = _successors.listIterator();
		_kind = kind;
		_name = name;
		_proxyClass = proxyClass;
		_className = className;
		_isNew = true;
		_running = false;
		_customLibs = new ArrayList<String>();
	}

	public void addLibToList (String relativePath){
		_customLibs.add(relativePath);
	}
	
	public ArrayList <String> getCustomLibs () {
		return _customLibs;
	}
	
	public void setKind(String kind) {
		_kind = kind;
	}

	public void setName(String name) {
		_name = name;
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

	public String getproxyClass() {
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
		// idea: go through the list an if a an element is larger
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
		if (_successors.isEmpty())
			return false;
		else
			return true;
	}

	public void setPathToFile(String pathToFile) {
		_pathToFile = pathToFile;
	}

	public String getPathToFile() {
		return _pathToFile;
	}

	public boolean isLeave() {
		if (this.hasSuccessors())
			return false;
		return true;
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
		_correspondingThread = new ProxyThread(this, eventHeap);
		_correspondingThread.start();
	}

	public void stopProxy() {
		try {
			_correspondingThread.kill();
		} catch (Exception err) {
			err.printStackTrace();
		}
	}

	public ProxyThread getCorrespondingThread() {
		return _correspondingThread;
	}

}