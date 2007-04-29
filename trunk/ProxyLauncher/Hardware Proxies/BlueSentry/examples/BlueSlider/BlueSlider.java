
import java.io.*;
import java.util.*;
import iwork.eheap2.*;

public class BlueSlider implements BlueSentryListener {
	BlueSentry bs;
	EventHeap eheap;
	private int lastSliderRange;
	private String ID;
	private int count = 0;
	
	private static int SLEEP_COUNT = 200;
	private static boolean DEBUG = true;
	
	BlueSlider( String eheapName, String comPort ){
		ID = comPort;
		eheap = new EventHeap( eheapName );
		bs = new BlueSentry( comPort );
		bs.register(this);
	}
	
	// BlueSentry has new data
	public void callback(){
		try{
			int sliderData = bs.getChannel( 0 );
		
			// trim back the resolution for this hardware
			int sliderDataRange = sliderData >> 10;
			
			count++;
			
			if( sliderDataRange != lastSliderRange ){
				lastSliderRange = sliderDataRange;
				postEvent(sliderData);
				if( DEBUG )
					System.out.println( "Data: " + sliderData + "\tCount: " + count );
				count = 0;
			}
			
			/* 
			if( count > SLEEP_COUNT ){
				if( DEBUG )
					System.out.println("Night Night");
				bs.sleep();	
			}
			*/
		} catch( Exception ex ){ ex.printStackTrace(); }
	}
	
	public void postEvent( int value ){
		try{
			Event e = new Event("iStuffInputEvent");
			e.addField("Device", "Slider");
			e.addField("ID", "bluetooth-" + ID ); 
			e.addField("Value", new Integer( value ) );
			e.addField("Max", new Integer( 0xFFFF ) );
			e.addField("Min", new Integer( 0 ) );
			eheap.putEvent( e );
		}catch( Exception ex ){ ex.printStackTrace(); }
	}
	
	public OutputStream getOutputStream(){
		return bs.getOutputStream();
	}
	
    public static void main(String[] args) {	
		BlueSlider bs;
		
		if( args.length == 0 )
			bs = new BlueSlider("iw-room2", "COM3");
		else if( args.length == 1 )
			bs = new BlueSlider( args[0], "COM3" );
		else 
			bs = new BlueSlider( args[0], args[1] );

		// activate the print statements
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		// route keyboard to the bluesentry
		while( true ){
			try{
				bs.getOutputStream().write( in.readLine().getBytes() );
			} catch (Exception e) { e.printStackTrace(); }
		}
	}
}


