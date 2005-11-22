import iwork.eheap2.*;
import java.io.*;
import java.lang.*;
import java.util.*;

public class motionProxy{
    public static void main(String argv[]){
		String incoming;
		if(argv.length != 1){
			System.out.println("Usage: java motionProxy eventHeapServerName");
			System.exit(-1);
		}
		EventHeap eh = new EventHeap(argv[0]);
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		//InputStreamReader in = new InputStreamReader(System.in);
		try{
			incoming = in.readLine();
			while( true ){
					Event e = new Event("Powerbook_Tilt");
					System.out.println(incoming);
					StringTokenizer st = new StringTokenizer(incoming);
					if(st.countTokens() == 3){
						String x = st.nextToken();
						e.addField("X", new Integer(x.trim()));
						String y = st.nextToken();
						e.addField("Y", new Integer(y.trim()));
						String z = st.nextToken();
						e.addField("Z", new Integer(z.trim()));
						
						e.setTimeToLive(500); // 500 ms
						eh.putEvent(e);
					}else{
						System.out.println("motionProxy: error, unknown data format: " + incoming);
					}
					incoming = in.readLine();
			}
		} catch(Exception ex){ ex.printStackTrace(); }
	
    }
}
