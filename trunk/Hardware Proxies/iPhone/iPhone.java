/**
 * $Id: iPhone.java,v 1.3 2004/06/30 12:47:55 rohs Exp $
 *
 *  Name     : iPhone
 *  Part of  : iPhone
 *  Created  : 16.05.2005 Rafael Ballagas
 *  Copyright: (c) 2005 RWTH Aachen
 **/
import iwork.eheap2.*;

public class iPhone implements SymbianInputListener, Runnable{
	private final static boolean DEBUG = true;
	private String _proxyID;
	
	private SymbianInputDevice sid;
	private EventHeap eh;

	public iPhone(String EventHeapServer, String proxyID, String comPort, boolean isRotationEnabled) {
		_proxyID = proxyID;
		
		sid = new SymbianInputDevice(comPort, this);
		sid.setRotationEnabled(isRotationEnabled);
		eh = new EventHeap(EventHeapServer);
	}


    public void translationCallback(int dX, int dY){
		/* add any value acceleration here */
		if(DEBUG)
			System.out.println("iPhone translationCallback: dX = " + dX + ", dY = " + dY);
		
		/* post an event to the EventHeap */
		try{
			Event e = new Event("iPhone");
			e.addField("ProxyID", _proxyID);
			e.addField("type","translation");
			e.addField("dX", new Integer(dX));
			e.addField("dY", new Integer(dY));
			if (eh.isConnected()) 
				eh.putEvent(e);
		}catch(Exception ex){
			ex.printStackTrace();
		}
	}
	
	public void rotationCallback(int angle){
		/* add any value acceleration here */
		double rotZ = -0.4 * angle * Math.PI / 180;
		if(DEBUG)
			System.out.println("iPhone rotationCallback: angle = " + rotZ);
		
		/* post an event to the EventHeap */
		try{
			Event e = new Event("iPhone");
			e.addField("ProxyID", _proxyID);
			e.addField("type","rotation");
			e.addField("angle", new Double(rotZ));	
			eh.putEvent(e);
		}catch(Exception ex){
			ex.printStackTrace();
		}
	}
	
	public void clickCallback(boolean isPressed){
		if(DEBUG)
			System.out.println("iPhone clickCallback " + isPressed);
		
		/* post an event to the EventHeap */
		try{
			Event e = new Event("iPhone");
			e.addField("ProxyID", _proxyID);
			e.addField("type","click");
			if(isPressed)
				e.addField("state","pressed");
			else
				e.addField("state","unpressed");
			eh.putEvent(e);
		}catch(Exception ex){
			ex.printStackTrace();
		}
	}
	
	public void codeCallback(String code, int targetX, int targetY){
		if(DEBUG)
			System.out.println("iPhone codeCallback: code = " + code + ", targetX = " + targetX + ", targetY = " + targetY);
		
		/* post an event to the EventHeap */
		try{
			Event e = new Event("iPhone");
			e.addField("ProxyID", _proxyID);
			e.addField("type", "code");
			e.addField("code", code);
			e.addField("targetX", new Integer(targetX));
			e.addField("targetY", new Integer(targetY));
			eh.putEvent(e);
		}catch(Exception ex){
			ex.printStackTrace();
		}
	}
	
	public void run(){
		while(true){
			sid.pollAndProcessInput();
		}
	}

	public static void main(String argv[]){
		// Arguments: <EventHeapServer> [ProxyID] <COMPort> [rotation parameter]
		iPhone phone;
		if(argv.length == 2){  // Minimum number of arguments: Only EventHeap and COMPort provided
			phone = new iPhone(argv[0],"",argv[1], true);
			phone.run();
		}else if(argv.length == 3 && argv[2].compareTo("-r") == 0){ // Then the parameter was supplied
			phone = new iPhone(argv[0],"", argv[1], false);
			phone.run();
		}
		else if	(argv.length == 3 && argv[2].compareTo("-r") != 0){ // otherwise only a ProxyID was given and no -r parameter
				phone = new iPhone (argv[0], argv [1], argv [2], false);
			}
		else {
			System.out.println("Usage: java iPhone <Event Heap Server> <Comm Port> [ProxyID] [-r]\n" +
						"\t<Event Heap Server> = network address of the Event Heap Server, examples: localhost, iroom.stanford.edu" +
						"\t <ProxyID =  An ID to be provided with each generated event in order to identify the sending device" +
						"\t<Comm Port> = the serial port address for the phone, examples: \"/dev/tty.Nokia6600\", \"COM3\"\n"+
						"\t[-r] = deactivates rotation capabilities of the sweep interaction. For use with \"iPhone-no-rotation.sis\"");
		}
	}

}
