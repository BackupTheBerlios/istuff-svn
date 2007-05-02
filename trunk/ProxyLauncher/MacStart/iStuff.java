import java.io.*;
import java.lang.*;

public class iStuff{
	
/*	private boolean running = false;
	private Process process;
	
	public iStuff() {
		
	}
	
	public boolean isRunning(){
		return running;
	}
	
	public void run() {
		String line;
		try {
			running = true;
			String runCommand = "ls -al";
			File workingDirectoryFile = new File(".");
			String workingDirectory = workingDirectoryFile.toURL().toString();
			
			process = Runtime.getRuntime().exec(runCommand, null, workingDirectory); // For the proxies
			System.out.println(runCommand);
			System.out.println(workingDirectory); 
			
			BufferedReader input = new BufferedReader(new InputStreamReader(process.getInputStream()));
			while ((line = input.readLine()) != null) {
				System.out.println(line);
			}
		}
		catch (IOException e){
			// Just ignore this
		}
        // This private class is used to fire MyEvents
		System.out.println("EOP");
	}	
*/	
	public static void main(String args[]) {
		WrapperThread wrapper = new WrapperThread("java -classpath ./:./iStuff.jar -jar iStuff.jar",".");
		wrapper.start();
	 }

}