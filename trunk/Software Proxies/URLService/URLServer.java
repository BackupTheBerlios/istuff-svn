import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

import iwork.eheap2.Event;
import iwork.eheap2.EventHeap;
import iwork.eheap2.EventHeapException;

/*
 * Created on Aug 9, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
/**
 * @author yu
 *
 * - Purpose
 * - Related classes:
 * - To do
 */
public class URLServer implements EventConstant{
	private static final boolean DEBUG = false;
	private EventHeap eHeap;
	private String _proxyID;
	private boolean isRunning = false;
	
	public URLServer(String heapServerName, String proxyID){
		eHeap = new EventHeap(heapServerName);
		_proxyID = proxyID;
	}
	
	
	public void startService(){
		isRunning = true;
		new URLEventThread().start();
	}
	
	
	public void stopService(){
		isRunning = false;
	}
	
	
	/**
	 * 
	 * @param urlString the url to fetch from
	 * @return the content from the specified url
	 * @throws MalformedURLException
	 * @throws IOException
	 */
	protected String getContent(String urlString) throws MalformedURLException, IOException{
		StringBuffer res = new StringBuffer();
		//e.g. "http://rss.news.yahoo.com/rss/nasashuttle"
		URL url = new URL(urlString);
		
		BufferedReader in = new BufferedReader(
                					new InputStreamReader(
                							url.openStream()));

		String inputLine;

		while ((inputLine = in.readLine()) != null){
				res.append(inputLine);
				if (DEBUG) System.out.println(inputLine);
		}
		in.close();
		return res.toString();
	}
	
	
	/**
	 * 
	 * @author yu
	 *
	 * - Purpose:  to listen for an url request event
	 * - Related classes:
	 * - To do
	 */
	class URLEventThread extends Thread{
		public void run(){
			try{
				System.out.println("URL server listening...");
				Event template = new Event(EVENT_TYPE);
				template.addField(FIELD_TYPE, TYPE_REQUEST);
				while (isRunning){
					Event incoming = eHeap.waitForEvent(template);
					if ( (incoming.getPostValueString("ProxyID").equals(_proxyID)) 
							|| (incoming.getPostValueString("ProxyID").equals("")) ) {
						String urlAsString = incoming.getPostValueString(FIELD_URL);
						
						Event outgoing = new Event(EVENT_TYPE);
						if (!DEBUG) outgoing.addField("TimeToLive", new Integer(1000));
						try{
							String res = getContent(urlAsString);
							outgoing.addField(FIELD_TYPE, TYPE_RESPONSE);
							outgoing.addField(FIELD_CONTENT, res);
						}
						catch (Exception exp){
							outgoing.addField(FIELD_TYPE, TYPE_ERROR);
							outgoing.addField(FIELD_CONTENT, exp.getMessage());
						}
						
						eHeap.putEvent(outgoing);
					}
				}
			}
			catch (EventHeapException eexp){
				eexp.printStackTrace();
			}
			catch (Exception exp){
				exp.printStackTrace();
			}
		}
	}
	
	//=======================================
	public static void main(String[] args) {
		URLServer us;

		if( args.length == 1 ){
			try{
				us = new URLServer( args[0], "" );
				us.startService();
			}catch(Exception e){
				e.printStackTrace();
			}
		} 
		else if (args.length == 2) {
			try{
				us = new URLServer( args[0], args[1] );
				us.startService();
			}catch(Exception e){
				e.printStackTrace();
			}
		}
		else{
			System.out.println("usage:  URLServerProxy <Event Heap Name> [ProxyID]");
			System.exit(-1);
		}
	}
	
	public static void printUsage(){
		System.out.println("Usage: URLServer <event heap name>");
	}
}
