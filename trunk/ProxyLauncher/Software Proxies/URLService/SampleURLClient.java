import iwork.eheap2.Event;
import iwork.eheap2.EventHeap;

/*
 * Created on Aug 9, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
/**
 * @author yu
 *
 * - Purpose: Demonstrate how to send a event to fetch webcontebnt of the web so that the user can
 * imagin how physical interface can react on web informations. 
 */
public class SampleURLClient {
	private static final boolean DEBUG = false;
	private EventHeap eHeap;
	
	public SampleURLClient(String servername){
		try{
			eHeap = new EventHeap(servername);
		
			Event request = new Event("URL_SERVICE");
			request.addField("type","request");
			request.addField("url","http://www.wdr.de/studio/aachen/allgemein/wetter/?bereich=lokalzeit");
			if (!DEBUG) request.addField("TimeToLive", new Integer(1000));
			//Send
			eHeap.putEvent(request);
			
			Event responseTemplate = new Event("URL_SERVICE");
			responseTemplate.addField("type","response");
			//Wait for response
			Event response = eHeap.waitForEvent(responseTemplate);
		
			//Analysis
			if (response.getPostValueString("type").equalsIgnoreCase("response")){
				String content = response.getPostValueString("content");
				String parts[] = content.split("\u0026deg;C");
				//for (int i=0; i<parts.length; i++)
///					System.out.println(parts[i]);
				String temperatureString = parts[0].substring(parts[0].lastIndexOf(">")+1,parts[0].length());
				
//				response
				System.out.println("The temperatur in Aachen is " + temperatureString + "C");
			}
			else if (response.getPostValueString("type").equalsIgnoreCase("error")){
				System.out.println(response.getPostValueString("content"));
			}
			
			
		}
		catch (Exception exp){
			exp.printStackTrace();
		}
	}
	
	
	public static void main(String[] args) {
		SampleURLClient uc;
		
		if( args.length == 1 ){
			try{
				uc = new SampleURLClient( args[0] );
			}catch(Exception e){
				e.printStackTrace();
			}
		}  
		else{
			printUsage();
			System.exit(-1);
		}
	}
	
	public static void printUsage(){
		System.out.println("Usage: SampleURLClient <event heap name>");
	}
}
