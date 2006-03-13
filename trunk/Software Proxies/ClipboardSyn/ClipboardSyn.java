import java.awt.Frame;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;
import java.io.Serializable;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import iwork.eheap2.*;
import javax.swing.*;

/*
 * Created on Mar 10, 2006
 * By eugen
 */

/**
 * @author eugen
 *
 * Purpose: Proxy checks for change in the 
 * Related classes: TODO
 * Still to come: TODO
 */
public class ClipboardSyn{
	protected boolean DEBUG  =false;

	private JFrame restartFrame;
	
	private static String EVENTTYPE = "ClipboardEvent";
	private static String FIELDNAME_CONTENTTYPE = "contenttype";
	private static String FIELDVALUE_CONTENTTYPE_STR = "string"; 
	private static String FIELDVALUE_CONTENTTYPE_FILELIST = "filelist"; 
	
	private static String FIELDNAME_MACHINENAME = "machinename";
	private static String FIELDNAME_CONTENT = "content";
	private static String FIELDNAME_CONTENT_SIZE = "contentsize"; 

	
	
	//private Frame mFrame;
	private String mMachineName;
	private Clipboard mClipboard;
	private boolean isRunning;
	private ClipToHeapThread mThread;
	private HeapToClipThread mInThread;
	
	private String oldString = "";
	private java.util.List oldList  = new java.util.Vector();
	private EventHeap mEventHeap;
	//q: is there a call back, so that I don't need a loop; works only with notifier
	//q: how to check
	//q: send the wrapped object as serializable or send the string?, the file? or the image 
	//q: define the event; field with supportedflavors, transferable as serializable ?
	//q: define sender
	
	
	public Event toEvent(String str){
		Event res = null;
		try{
			 res = new Event(EVENTTYPE);
			 res.setField(FIELDNAME_CONTENTTYPE,FIELDVALUE_CONTENTTYPE_STR,FieldValue.FORMAL);
			 res.setField(FIELDNAME_CONTENT_SIZE,new Integer(1),FieldValue.FORMAL);
			 res.setField(FIELDNAME_CONTENT + "0",str,FieldValue.FORMAL);
			 res.setField(FIELDNAME_MACHINENAME,mMachineName,FieldValue.FORMAL);
			 res.setField("TimeToLive",new Integer(1000),FieldValue.FORMAL); 
		}
		catch (EventHeapException eexp){
		}
		return res;
	}
	
	public Event toEvent(java.util.List l){
		Event res = null;
		try{
			res = new Event(EVENTTYPE);
			res.setField(FIELDNAME_CONTENTTYPE,FIELDVALUE_CONTENTTYPE_FILELIST,FieldValue.FORMAL);
			res.setField(FIELDNAME_CONTENT_SIZE,new Integer(l.size()),FieldValue.FORMAL);
			res.setField("TimeToLive",new Integer(1000),FieldValue.FORMAL); 
			int index =0;
			for (Iterator i= l.iterator(); i.hasNext();){
				Object obj = i.next();
				if (obj instanceof Serializable){
					res.setField(FIELDNAME_CONTENT + index, (Serializable)obj ,FieldValue.FORMAL);
					index++;
				}
			}
			res.setField(FIELDNAME_MACHINENAME,mMachineName,FieldValue.FORMAL);
		}
		catch (EventHeapException eexp){
		}
		return res;
	}

	
	public ClipboardSyn(String iEventHeapName, String iMachineName){
		//create event heap
		mEventHeap = new EventHeap(iEventHeapName);
		mMachineName = iMachineName;
		isRunning = false;
		mThread = null;
		mClipboard = new Frame().getToolkit().getSystemClipboard();
		restartFrame = new JFrame();
		restartFrame.setSize(180,80);
		restartFrame.setLocation(0,0);
		//JButton restartButton = new JButton("Clear clipboard for sending.");
		JButton restartButton = new JButton("Grab clipoard control."); 
		//Actually you clear the clipboard so that you can send the system's clipboard again
		//After set clipboard is used, the clipboard in java is not updated with the system's update action.
		//Setting null to null will help.
		restartButton.addActionListener(new java.awt.event.ActionListener(){
			public void	actionPerformed(java.awt.event.ActionEvent e){
				try{
					new Frame().getToolkit().getSystemClipboard().setContents(null,null);
				}
				catch (NullPointerException nexp){
				}
			}
		});
		restartFrame.getContentPane().setLayout(new java.awt.BorderLayout());
		restartFrame.getContentPane().add(restartButton, java.awt.BorderLayout.CENTER);
		restartFrame.setVisible(true);
	}
	
	
	public void start(){
		isRunning = true;
		mThread = new ClipToHeapThread();
		mInThread = new HeapToClipThread();

		mThread.start();
		mInThread.start();
	}
	
	public void stop(){
		isRunning = false;
	}

	//Don't set if recived event came from same sender
	class HeapToClipThread extends Thread implements ClipboardOwner{
		
		public void run() {
			try{
				Event template = new Event(EVENTTYPE);
				template.addField(FIELDNAME_MACHINENAME, String.class);
				template.addField(FIELDNAME_CONTENTTYPE,String.class);
				template.addField(FIELDNAME_CONTENT_SIZE, Integer.class);
				while (isRunning){
					try{
						try{
							if(DEBUG)System.out.println(mMachineName + ":Waiting for event");
							Event e = mEventHeap.waitForEvent(template);
							if (e.getPostValueString(FIELDNAME_MACHINENAME).equals(mMachineName)){
								Thread.sleep(3000);
								continue;
							}
							Transferable t  =null;
							//switch bewteen content type
							if (e.getPostValueString(FIELDNAME_CONTENTTYPE).equals(FIELDVALUE_CONTENTTYPE_STR)){
								String content = e.getPostValueString(FIELDNAME_CONTENT+"0");
								if (!content.equals(oldString)){
									if(DEBUG)System.out.println(mMachineName + ":set content " + content);
									oldString = content;
									t = new java.awt.datatransfer.StringSelection(content);
								}
							}
							else if (e.getPostValueString(FIELDNAME_CONTENTTYPE).equals(FIELDVALUE_CONTENTTYPE_FILELIST)){
								Integer numbOfFields=  (Integer)e.getPostValue(FIELDNAME_CONTENT_SIZE);
								java.util.List l = new ArrayList();
								String fileListAsString = "";
								for (int i=0; i<numbOfFields.intValue(); i++){
									
									java.io.File file = (java.io.File)e.getPostValue(FIELDNAME_CONTENT+i);
									fileListAsString =  file.getAbsolutePath() ;
									if (i<numbOfFields.intValue())fileListAsString += ";";
								}
								//t  = new TransferableFileList(l);
								System.out.println("Cannot handle files yet. Handling it as string.");
								t = new java.awt.datatransfer.StringSelection(fileListAsString);
							}							
							if (t!=null){
								new Frame().getToolkit().getSystemClipboard().setContents(t,null);
							}
						}catch (EventHeapException eexp){}
						Thread.sleep(1000);
					}
					catch (InterruptedException iExp){
					}
				}
			}
			catch (EventHeapException eexp){
				eexp.printStackTrace();
			}
		}

		/* (non-Javadoc)
		 * @see java.awt.datatransfer.ClipboardOwner#lostOwnership(java.awt.datatransfer.Clipboard, java.awt.datatransfer.Transferable)
		 */
		public void lostOwnership(Clipboard c, Transferable t) {
			// TODO Auto-generated method stub
			//Do nothing
			oldString ="";
			oldList = new ArrayList();
			System.out.println("Lost ownership");
			new Frame().getToolkit().getSystemClipboard().setContents(null,null);
		}

	}
	
	
	//Don't send if the transferable is the same 
	class ClipToHeapThread extends Thread{

		/* (non-Javadoc)
		 * @see java.lang.Runnable#run()
		 */
		public void run() {
			while (isRunning){
				try{
					try{
						if(DEBUG)System.out.println("++++++++++++++++");
						if(DEBUG)System.out.println("Check clipboard");
						Transferable t = java.awt.Toolkit.getDefaultToolkit().getSystemClipboard().getContents(null);
						Event e = null;
						if(DEBUG)System.out.println(t);
						if (t.isDataFlavorSupported(DataFlavor.stringFlavor)){
							String newString =  (String)t.getTransferData(DataFlavor.stringFlavor);
							if(DEBUG) System.out.println(mMachineName + ":old=" + oldString + " :new=" +newString);
							if (!(oldString.equals(newString))){
								e = toEvent(newString);
								oldString = newString;
							}
						}
						if (t.isDataFlavorSupported(DataFlavor.imageFlavor)){
							//System.out.println("isImageFlavor");
							//System.out.println(t.getTransferData(DataFlavor.imageFlavor) instanceof Serializable);
							
						}
						if (t.isDataFlavorSupported(DataFlavor.javaFileListFlavor)){
							//System.out.println("isjavaFileListFlavor");
							java.util.List newList = (java.util.List)t.getTransferData(DataFlavor.javaFileListFlavor);
							if (!(oldList.equals(newList))){
								e = toEvent(newList);
								oldList = new ArrayList(newList);
							}
						}
						
						if (e!=null){
							try{
								mEventHeap.putEvent(e);
							}
							catch (EventHeapException eexp){
								eexp.printStackTrace();
							}
						}//end-if
					}
					catch (UnsupportedFlavorException fexp){
						if(DEBUG)System.out.println("unsuported flavor");
					}
					catch (IOException ioexp){
						if(DEBUG)System.out.println("io exception");
					}
					Thread.sleep(1000);
				}
				catch (InterruptedException iExp){
				}
			}
		}
		
	}
	
		
	//Does not work right now; seems like I have to use NSArray.
	class TransferableFileList implements Transferable, ClipboardOwner{
		List mList;
		
		public TransferableFileList(List iList){
			mList = iList;
		}
		
		public Object	getTransferData(DataFlavor flavor) throws UnsupportedFlavorException{
			if (flavor.equals(java.awt.datatransfer.DataFlavor.javaFileListFlavor )) return mList;
			else if (flavor.equals(java.awt.datatransfer.DataFlavor.stringFlavor  )) {
				String res = "";
				for (Iterator i = mList.iterator(); i.hasNext();){
					java.io.File file = (java.io.File)i.next();
					res += file.getName();
					if (i.hasNext()) res += "\n";
 				}
				return res;
			}
			else throw new UnsupportedFlavorException(flavor);
			
		}
        public  DataFlavor[]	getTransferDataFlavors(){
			return new DataFlavor[] {java.awt.datatransfer.DataFlavor.stringFlavor, java.awt.datatransfer.DataFlavor.javaFileListFlavor};
		}
        public boolean	isDataFlavorSupported(DataFlavor flavor){
			if (flavor.equals(java.awt.datatransfer.DataFlavor.javaFileListFlavor )) return true;
			else if (flavor.equals(java.awt.datatransfer.DataFlavor.stringFlavor  )) return true;
			return false;
		}
		
		public void lostOwnership(Clipboard c, Transferable t) { 
			mList = null; 
		}
	}
	
	
	/*class MyImage extends Canvas implements Serializable{
	//see http://www.dcs.shef.ac.uk/~tom/Java/Power/GraphicButton.java
	}*/

	public static void main(String[] args) {
		if (args.length<2) printUsage();
		else{
			ClipboardSyn l = new ClipboardSyn(args[0], args[1]);
			l.start();
		}
	}
	
	public static void printUsage() {
		System.out.println("Usage: ClipboardSyn <Eventheap> <MachineName>");
	}
}


