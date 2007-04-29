import iwork.eheap2.*;
import java.awt.Robot;
import java.awt.AWTException;

/**
*@author: Eugen Yu
Reacts to the ScrollEvent from the PointRightEvents
*/

//arg:  ip of machine
public class ScrollEventServer{
	private EventHeap mEventHeap;
	private String mMachineName = "";
	private boolean isRunning;
	
	private Robot robot = null;

	private ScrollListeningThread scrollListeningThread;
	
		
	//States to create drag acion, while someone is doing drag and drop do not draw other's pointer 
	
	public ScrollEventServer(String iEventHeapName, String iMachineName){
		try{
			mMachineName = iMachineName;
			mEventHeap = new EventHeap(iEventHeapName);
			isRunning = false;
			robot = new Robot();
		}
		catch (AWTException robotExp){
			System.out.println(robotExp);
			System.exit(-1);
		}
	}
	
	
	public void start(){
		isRunning = true;
		scrollListeningThread = new ScrollListeningThread();	
		scrollListeningThread.start();
	}
	
	public void stop(){
		isRunning = false;		
	}
	
	
	class ScrollListeningThread extends Thread{
		public void run(){
			try{
				Event tEvent = new Event("PointRightEvent");
				tEvent.addField("Screen", mMachineName);
				//This target
				tEvent.addField("PointRightEventType", "ScrollEvent");
				//SrcMachine
				tEvent.addField("srcMachineName", String.class);
				tEvent.addField("level", Integer.class);
				//This type of events use Screen to determine target, later on use Target to determine machine and Screen to determine output device!!
				//tEvent.addField("Target", String.class);
				while (isRunning){
					try{
						Event iEvent =  mEventHeap.waitForEvent(tEvent);

						Integer level = (Integer)iEvent.getPostValue("level");
						if (level.intValue()<1) continue;
						
						String Target = (String)iEvent.getPostValueString("Screen");
						if (!Target.equals(mMachineName)) continue;
					
						Integer value = (Integer)iEvent.getPostValue("Value");
						robot.mouseWheel(value.intValue());
					}
					catch (EventHeapException eexpWait){
					}
				}//end-while
			}
			catch (EventHeapException eexp){
			}
		}
	}
	
	
	public static void main(String argv[]){
		if(argv.length >= 2){
			ScrollEventServer ses = new ScrollEventServer(argv[0], argv[1]);
			ses.start();
		} else {
			System.out.println("Usage: ScrollEventServer <Event Heap Name> or <Machine Name> not provided");
		} 
	}
	
}
