import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.swing.JTextArea;
import javax.swing.event.EventListenerList;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;

public class ProxyThread extends Thread implements Runnable {

	private Process _process;
	private JTextArea _bufferText;
	private String _runCommand;
	private File _workingDirectory;
	
    // Create the a custom listener list
    protected EventListenerList _MyListenerList =
    		new EventListenerList();
	
	public ProxyThread (String launchCommand, String workingDirectory) {
		_runCommand = launchCommand;
		if (workingDirectory != null)
			_workingDirectory = new File (workingDirectory);
	}

	public void run() {
		String line;
		try {
			if (_workingDirectory == null)
				_process = Runtime.getRuntime().exec(_runCommand); // For the Event Heap and Event Logger
			else
				_process = Runtime.getRuntime().exec(_runCommand, null, _workingDirectory); // For the proxies
			System.out.println(_runCommand);
			System.out.println(_workingDirectory); 
			BufferedReader input = new BufferedReader(new InputStreamReader(
					_process.getInputStream()));
			while ((line = input.readLine()) != null) {
				_bufferText.append(line + " \n");
			}
		} catch (IOException e) {
			// Just ignore this
		}
		// send a message as an Event that the process has stopped
	    // This private class is used to fire MyEvents
		System.out.println("ready");
//		FireActionEvent.fireEvent (new ActionEvent(this, ActionEvent.ACTION_PERFORMED, 
//				"Process quit"), _MyListenerList);
	}

	public void kill() {
		_process.destroy();
	}

//	public void setTextArea(JTextArea textArea) {
//		_bufferText = textArea;
//		_bufferText.setText("");
//	}
	
	 
    // This methods allows classes to register for MyEvents
//    public void addProcessQuitEventListener(ActionListener listener) {
//        _MyListenerList.add(ActionListener.class, listener);
//    }

} // end of class
