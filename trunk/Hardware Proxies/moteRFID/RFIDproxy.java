
import java.io.*;
import java.util.*;
import iwork.eheap2.*;

public class RFIDproxy implements RFIDListener {
	RFID rfid;
	//fakeRFID rfid;
	EventHeap eheap;
	String lastID = "";
	public static String START_TAG =	"314530303738314243433139353735333300000000000001007E";
	public static String NEXT_TAG =		"314530303738314243433139353339363400000000000001007E";
	public static String PREV_TAG =		"314530303738314243433139353041343000000000000001007E";
	public static String URL =			"http://coltrane.informatik.rwth-aachen.de/~ballagas/talks/talk.htm";
	public static long TIMEOUT = 1000; // ms
	long lastReadTime;
	String OSname;

	RFIDproxy( String eheapName, String comPort ){
		eheap = new EventHeap( eheapName );
		rfid = new RFID( comPort );
		//rfid = new fakeRFID( comPort );
		rfid.register(this);
		OSname = System.getProperty("os.name");
	}
	
	
	// BlueSentry has new data
	public void callback(String tagID){
						System.out.println("RFID proxy: " + tagID);
			long curTime = System.currentTimeMillis();

			if(tagID.equals(lastID)){
				if(curTime - lastReadTime > TIMEOUT){
					decodeID(tagID);
				}
			} else {
				decodeID(tagID);
				lastID = tagID;				
			}
			lastReadTime = curTime;
			
			//Event e = new Event("RFID");
			//e.addField("id", tagID );
			//eheap.putEvent( e );
	}
	
	public void decodeID(String tagID){
		try{
			Event e = new Event("SlideController");
			
			if(tagID.equals(NEXT_TAG)){
				e.addField("command", "next");
			}else if(tagID.equals(PREV_TAG)){
				e.addField("command", "prev");
			}else if(tagID.equals(START_TAG)){
				e.addField("command", "open");
				e.addField("url", URL);
			}else {
				System.out.println("RFID proxy:  Unknown tag: " + tagID);
				return;
			}
			eheap.putEvent(e);
		}catch(Exception ex){
			ex.printStackTrace();
		}
	}
	
    public static void main(String[] args) {	
		RFIDproxy bs;
		
		if( args.length == 2 )
			bs = new RFIDproxy( args[0], args[1] );
		else
			System.out.println("Usage: RFIDproxy <event heap name> <comm port>");
	}
}


