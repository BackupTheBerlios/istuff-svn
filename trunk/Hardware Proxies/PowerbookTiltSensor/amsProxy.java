import iwork.eheap2.*;
import java.io.*;
import java.lang.*;

public class amsProxy{
    public static int DATA_LENGTH = 14;

    public static void main(String argv[]){
	if(argv.length != 1){
	    System.out.println("Usage: java amsProxy eventHeapServerName");
	    System.exit(-1);
	}
	EventHeap eh = new EventHeap(argv[0]);
	char[] buffer = new char[100];
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	try{
	    System.out.println(in.readLine());
		while( true ){
			int numBytes = in.read(buffer, 0, DATA_LENGTH);
			if(numBytes > 0){
				Event e = new Event("Powerbook_Tilt");
				String data = new String(buffer);
				System.out.println(data);
				System.out.flush();
				// the first 4 bytes indicate x orientation
				String x = data.substring(0, 4);
				//System.out.println("x:" + x.trim());
				// the next 5 for y
				String y = data.substring(4, 9);
				//System.out.println("y:" + y.trim());
				// and the last 5 for z
				String z = data.substring(9, 14);
				//System.out.println("z:" + z.trim());
				e.addField("X", new Integer(x.trim()));
				e.addField("Y", new Integer(y.trim()));
				e.addField("Z", new Integer(z.trim()));
				eh.putEvent(e);
				// skip the backspaces
				numBytes = in.read(buffer, 0, 14);
			}
			else{
				Thread.sleep(0);
			}
	    }
	} catch(Exception ex){ ex.printStackTrace(); }
	
    }
}
