import iwork.eheap2.*;
import java.net.*;
import java.util.ArrayList;
import java.io.*;


public class EHtoAppleScript
{
	private EventHeap eheap;
	public String hostname;
	/* EY: To operate on multiple machine on the same account, a mechanism for mutual exclusion is needed.
	   With the following line, the programm manipulates the local files on multiple machines.
	public static String SCRIPT_FILE_NAME = "/tmp/script.txt";
	*/
	public static String SCRIPT_FILE_NAME = "script.txt";
	private Event latest = null;
	
	public EHtoAppleScript(String eheapName) throws UnknownHostException{
		this(eheapName, (InetAddress.getLocalHost()).getHostName());
	}
	
	public EHtoAppleScript(String eheapName, String machineName){
		eheap = new EventHeap(eheapName);
		hostname = machineName;
		System.out.println("Launching EHtoAppleScript on " + hostname);	 
	}

	public boolean verifyPermission(Event e){
		return true;
	}
	
	public void processEvents(){
		try{
			Event e = new Event("AppleScript");
			e.addField("script", FieldType.STRING, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
			e.addField("Target", hostname);
			
			Event [] events = new Event[3];
			events[0] = e;
			events[1] = new Event("AppleScript");
			events[1].addField("script", FieldType.STRING, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
			events[1].addField("Target", "all");
			events[2] = new Event("AppleScript");
			events[2].addField("script", FieldType.STRING, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
			events[2].addField("Target", "*");
			eheap.registerForEvents(events, new EHListener());
			
			while(true){
				//Event received = eheap.waitForEvent(e);
				if( latest != null ){
					synchronized(eheap){
						if( verifyPermission(latest) ){
							execute(latest.getPostValueString("script"));
						}
						latest = null;
					}
				} else {
					Thread.sleep(100);
				}
				
			}
		} catch(Exception e){
			e.printStackTrace();
		}
	}

	/**
	To execute a script. It writes the content of "script" into a file, then uses osascript command to invoke the execution.
	*/
	public void execute(String script){
		File scriptFile = new File(SCRIPT_FILE_NAME);
		

		try{
			BufferedWriter bufWrtr = new BufferedWriter(new FileWriter(scriptFile));
			String line = null; 
			bufWrtr.write(script); 
			bufWrtr.close(); 

			ArrayList cmd = new ArrayList();
			cmd.add("/usr/bin/osascript");
			cmd.add(scriptFile.getPath());
			//Creating a process
			String[] cmdArray = (String[]) cmd.toArray(new String[0]);
			Process proc = Runtime.getRuntime().exec(cmdArray);
			
			//Execute the process
			proc.waitFor();
			
			//Creating the output after execution
			Event outEvent = new Event("AppleScript");
			StringBuffer output = new StringBuffer();
			
			if (proc.exitValue() != 0){
				outEvent.addField("type","error");
				BufferedReader err = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
				while ((line = err.readLine())!= null){
					output.append(line + "\n");
				}
			}
			else{
				outEvent.addField("type","result");
				BufferedReader out = new BufferedReader(new InputStreamReader(proc.getInputStream()));
				while ((line = out.readLine())!= null){
					output.append(line + "\n");
				}
			}
			
			
			//System.out.println(this.getClass()+":"  + output.toString());
			outEvent.addField("comment","return value of script execution");
			outEvent.addField("content",output.toString());
			outEvent.addField("TimeToLive",new Integer(2000));
			eheap.putEvent(outEvent);
			
			/* +++++++++++++++++++++++++		
			//EY: This is the old version that does not put return value back on the heap
			String exec = "osascript " + SCRIPT_FILE_NAME;
			System.out.println(exec);
          		Process proc = Runtime.getRuntime().exec(exec);

            		// get its output (your input) stream

            		DataInputStream in = new DataInputStream(
                                          proc.getInputStream());
			String str;
            		while ((str = in.readLine()) != null) {
                		System.out.println(str);
			}
			proc.waitFor();
			+++++++++++++++++++++++++*/

		} catch (IOException e) {
			e.printStackTrace();
			System.exit(0);
		} catch (Exception e){
			e.printStackTrace();
		}
		
	}

	class EHListener extends Thread implements EventCallback{
		public boolean returnEvent(Event retEvents[]){
			synchronized(eheap){
				latest = retEvents[0];
			}
			
			return true;
		}
	}

     public static void main(String[] args)
     {
		EHtoAppleScript as;
		
		if( args.length == 1 ){
			try{
				as = new EHtoAppleScript( args[0] );
				as.processEvents();
			}catch(Exception e){
				e.printStackTrace();
			}
		}   
		else if( args.length == 2){
			as = new EHtoAppleScript( args[0], args[1] );
			as.processEvents();
		}
		else{
			System.out.println("Usage: EHtoAppleScript <event heap name> [machine name]");
			System.exit(-1);
		}
     }
     
     
     
     
     class AppleScriptException extends Exception{
     	
     	public AppleScriptException(String msg){
     		super(msg);
     	}
     }
} 
