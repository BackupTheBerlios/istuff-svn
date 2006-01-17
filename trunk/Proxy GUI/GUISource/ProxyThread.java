import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.swing.JTextArea;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;

public class ProxyThread extends Thread implements Runnable {

	private String _className;
	private File _env;
	private String _eventHeap;
	private Process _process;
	private JTextArea _bufferText;
	private File pathToIROS;
	private ProxyNode _threadNode;
	
	public ProxyThread(ProxyNode proxyNode, String eventHeap) {
		_className = proxyNode.getClassName();
		_env = new File(proxyNode.getPathToFile());
		System.out.println("FILEPATH: "+ _env);
		_eventHeap = eventHeap;
		_bufferText = new JTextArea();
		_threadNode = proxyNode;
		// The path to the iROS package is read dynamically
		// out of the config XML file

		SAXBuilder builder = new SAXBuilder();
		File configFile = new File("configStarter.xml");
		Document docWithConfig = new Document();
		try {
			docWithConfig = builder.build(configFile);
			Element xmlFileRoot = docWithConfig.getRootElement();
			if (xmlFileRoot != null)
				pathToIROS = new File(xmlFileRoot.getChild("Libraries").getChild("iROS").getValue());
		} catch (JDOMException e) {
			e.printStackTrace();
		} catch (IOException e) {
			System.out.println("ERROR: iROS Path not specified!");
		}
	}

	public void run() {
		String cmd;
		String line;
		String libs = "";
		
		// If there are custom libraries needed for a proxy, they are in an ArrayList
		// inside the proxyNode. That "customLibraryPath" has to be constructed.
		
		// It must be differentiated between the different OS because the syntax
		// of the JAVA Compiler call is a little different.
		String separator;
		
			if (System.getProperty("os.name").contains("Windows"))
				separator = ";";
			else
				separator = ":";
			
			try {	
				for (int i = 0; i != _threadNode.getCustomLibs().size(); i++)
					libs = libs + _threadNode.getCustomLibs().get(i) + separator;
				cmd = "java -classpath " + pathToIROS + separator + libs + ". " + _className
						+ " " + _eventHeap;

			_process = Runtime.getRuntime().exec(cmd, null, _env);
			BufferedReader input = new BufferedReader(new InputStreamReader(
					_process.getInputStream()));
			while ((line = input.readLine()) != null) {
				_bufferText.append(line + " \n");
			}
		} catch (IOException e) {
			System.out.println("There was an error while launching the proxy: "
					+ _className);
		}
	}

	public void kill() {
		_process.destroy();
	}

	public void setTextArea(JTextArea textArea) {
		_bufferText = textArea;
		_bufferText.setText("");
	}
}