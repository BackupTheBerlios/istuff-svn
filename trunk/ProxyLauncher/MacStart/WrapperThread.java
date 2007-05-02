import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.swing.JTextArea;
import javax.swing.event.EventListenerList;


public class WrapperThread extends Thread implements Runnable {

	private boolean running = false;
	private Process _process;
	private String _runCommand;
	private File _workingDirectory;
	
	public boolean isRunning(){
		return running;
	}
	
	public WrapperThread (String launchCommand, String workingDirectory) {
		_runCommand = launchCommand;
		if (workingDirectory != null)
			_workingDirectory = new File (workingDirectory);
		else _workingDirectory = new File (".");
	}

	public void run() {
		String line;
		try {
			running = true;
			_process = Runtime.getRuntime().exec(_runCommand, null, _workingDirectory); // For the proxies
			System.out.println(_runCommand);
			System.out.println(_workingDirectory); 
			BufferedReader input = new BufferedReader(new InputStreamReader(_process.getInputStream()));
			while ((line = input.readLine()) != null) {
				System.out.println(line);
			}
		} catch (IOException e) {
			// Just ignore this
		}
		running = false;
		// send a message as an Event that the process has stopped
	    // This private class is used to fire MyEvents
		System.out.println("ready");
	}

	public void kill() {
		_process.destroy();
	}

} // end of class
