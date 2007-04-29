import java.util.*;
import iwork.eheap2.*;
import java.awt.Robot;
import java.awt.Point;
import java.awt.AWTException;
import java.awt.event.InputEvent;
import java.awt.Toolkit;
import java.awt.Dimension;

/**
*@author: Eugen Yu
Reacts to the PointRightEvents and simulate multiple cursors
*/

//arg:  ip of machine
public class MultiPointerServer{
	private EventHeap mEventHeap;
	private String mMachineName = "";
	private Hashtable nameToPointTable;
	private boolean isRunning;
	
	private Robot robot = null;

	private EventListeningThread  eventListeningThread;
	private ShowCursorThread showCursorThread;
	
		
	//States to create drag acion, while someone is doing drag and drop do not draw other's pointer 
	private String srcThatIsDragging = "";
	private boolean leftIsDown = false;
	private boolean middleIsDown = false;
	private boolean rightIsDown = false;
	
	private static int LEAVE_MIN_X = 0;
	private static int LEAVE_MAX_X = 0;
	private static int LEAVE_MIN_Y = 0;
	private static int LEAVE_MAX_Y = 0;
	
	public MultiPointerServer(String iEventHeapName, String iMachineName){
		try{
			mMachineName = iMachineName;
			mEventHeap = new EventHeap(iEventHeapName);
			nameToPointTable = new Hashtable();
			isRunning = false;
			robot = new Robot();
			
			Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
			LEAVE_MAX_X = dim.width;
			LEAVE_MAX_Y = dim.height;
		}
		catch (AWTException robotExp){
			System.out.println(robotExp);
			System.exit(-1);
		}
	}
	
	
	public void start(){
		isRunning = true;
		eventListeningThread = new EventListeningThread();
		showCursorThread = new ShowCursorThread ();	
		eventListeningThread.start();
		showCursorThread.start();
	}
	
	public void stop(){
		isRunning = false;		
	}

	//Listens for pointright events
	class EventListeningThread extends Thread{
		public void run(){
			try{
				Event tEvent = new Event("PointRightEvent");
				tEvent.addField("Screen", mMachineName);
				//This target
				tEvent.addField("PointRightEventType", "MouseEvent");
				//SrcMachine
				tEvent.addField("srcMachineName", String.class);
				//To distinguish unmarked 
				tEvent.addField("level", Integer.class);
				//This type of event use Screen to determine target
				//tEvent.addField("Target", String.class);
				while (isRunning){
					try{
						Event iEvent =  mEventHeap.waitForEvent(tEvent);
						
						Integer level = (Integer)iEvent.getPostValue("level");
						if (level.intValue()<1) continue;
					
						String Target = (String)iEvent.getPostValueString("Screen");
						if (!Target.equals(mMachineName)) continue;

						

						//Check if source is in list exists
						String srcMachineName  = iEvent.getPostValueString("srcMachineName");
						//System.pi
						//If yes updatet the point that is associated by 
						//else create a new name->point mapping
						boolean leftButtonPressed = ((Integer)iEvent.getPostValue("LeftButton")).equals(new Integer(1));
						boolean middeButtonPressed = ((Integer)iEvent.getPostValue("MiddleButton")).equals(new Integer(1));
						boolean rightButtonPressed = ((Integer)iEvent.getPostValue("RightButton")).equals(new Integer(1));
						
						//process postion events
						Point newPoint = updatePoint(iEvent);
						if (newPoint !=null)
							nameToPointTable.put(srcMachineName,  newPoint);
						else
							nameToPointTable.remove(srcMachineName);
							
						//process click events
						if (leftButtonPressed ||middeButtonPressed || rightButtonPressed){
							srcThatIsDragging = srcMachineName;
							handleButtonClickDown(leftButtonPressed, leftIsDown,InputEvent.BUTTON1_MASK);
							handleButtonClickDown(middeButtonPressed, middleIsDown,InputEvent.BUTTON2_MASK);
							handleButtonClickDown(rightButtonPressed, rightIsDown,InputEvent.BUTTON3_MASK);
						}
						else{
							if (srcThatIsDragging.equals(srcMachineName)){
								 handleButtonClickUp(leftIsDown,InputEvent.BUTTON1_MASK);
								 handleButtonClickUp(middleIsDown,InputEvent.BUTTON2_MASK);
								 handleButtonClickUp(rightIsDown,InputEvent.BUTTON3_MASK);
							}//end-if
						}
					}
					catch (EventHeapException eexpWait){
					}
				}//end-while
			}
			catch (EventHeapException eexp){
			}
		}
	}
	
	
	protected void handleButtonClickDown(boolean buttonDownInCurrentEvent, boolean buttonDownInPastEvents, int buttonKeyToActivate){
		if (buttonDownInCurrentEvent){
			if (buttonDownInPastEvents){
				//Can resent special events back to the eventheap
				System.out.println("Drag");
			}
			else{
				//Set the states to create semi modal
				switch (buttonKeyToActivate){
					case InputEvent.BUTTON1_MASK:{
						leftIsDown = true;
						break;
					}
					case InputEvent.BUTTON2_MASK:{
						middleIsDown = true;
						break;
					}
					case InputEvent.BUTTON3_MASK:{
						rightIsDown = true;
						break;
					}

				}
				robot.mousePress(buttonKeyToActivate);
			}
		}
	}
	
	
	protected void handleButtonClickUp( boolean buttonDownInPastEvents, int buttonKeyToActivate){
		if (buttonDownInPastEvents){
				robot.mouseRelease(buttonKeyToActivate);
				switch (buttonKeyToActivate){
					case InputEvent.BUTTON1_MASK:{
						leftIsDown = false;
						break;
					}
					case InputEvent.BUTTON2_MASK:{
						middleIsDown = false;
						break;
					}
					case InputEvent.BUTTON3_MASK:{
						rightIsDown = false;
						break;
					}
				}
		}
	}
		
	//Deal with absolute or relative cursor update
	public Point updatePoint(Event iEvent) throws EventHeapException{
		String srcMachineName  = iEvent.getPostValueString("srcMachineName");
		Point res = new Point(0,0);
		if (nameToPointTable.containsKey(srcMachineName)){
			res = (Point)nameToPointTable.get(srcMachineName);
		}
		
		//Later distinguish between relative and aboslute creation
		Integer pos_x = (Integer)iEvent.getPostValue("X");
		Integer pos_y = (Integer)iEvent.getPostValue("Y");
		if (pos_x.intValue() <= LEAVE_MIN_X || pos_x.intValue() >= LEAVE_MAX_X 
			|| pos_y.intValue() <= LEAVE_MIN_Y || pos_y.intValue() >= LEAVE_MAX_Y){
			res = null;
		}
		else{
			res  = new Point(pos_x.intValue(), pos_y.intValue() );
		}

		return res;
	}


	//Traverse through list and use robot to set the pointer
	class ShowCursorThread extends Thread{
		public void run(){
			while (isRunning){
				if (leftIsDown ||  middleIsDown || rightIsDown){
					Point p  = (Point)nameToPointTable.get(srcThatIsDragging);
					robot.mouseMove(p.x, p.y);
				}
				else{
					for (Enumeration e=nameToPointTable.keys(); e.hasMoreElements();){
						String key = (String)e.nextElement();
						Point p  = (Point)nameToPointTable.get(key);
						robot.mouseMove(p.x, p.y);
					}//end-for
				}
			}
		}//end-run
	}
	
	
	
	public static void main(String argv[]){
		if(argv.length >= 2){
			MultiPointerServer mps = new MultiPointerServer(argv[0], argv[1]);
			mps.start();
		} else {
			System.out.println("Usage: MultiPointerServer <Event Heap Name> or <Machine Name> not provided");
		} 
	}
	
}
