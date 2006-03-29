import java.awt.Robot;
import java.awt.event.*;
import iwork.eheap2.*;
import java.util.*;


/**
*@author: Eugen Yu
*
This keybot robot is designed for Mac OS X tiger, for windows another keycodeToVirtualKey mapping has to be used.
This is not implemented. But the implementation should looks like the method createKeycodeTable().
*/
public class KeyRobot{

	private Robot robot = null;
	private boolean running = true;
	private Hashtable keyDownTable;
	
	private Hashtable keycodeTable;
	private Hashtable metaKeycodeTable;
	private Hashtable keyToCodeCompletionTable;
	private EventHeap eheap;
	private String mMachineName;
	
	/*
	Improvement of this class:
	Sometimes the keyrealease event is not . Especially when the keyboard server is shutting down.
	So it might be useful to have a timed hastable that keeps track of what is pressed and if a certain amount of time has
	passed, it should release all pressed buttons.

	For the keykombination event. 
	*/
	
	/*
	This method process an event that encodes a key kombination.
	An example of such an event has the following fields:
		size =2;		//has to be even
		code1 = 0;		//A integer of the keyboard code
		key1  = "a";		//Show the letter of the key.
					//If the field code is not found, the porgram will try to find the appropriate keycode, this does not suppport function keys.
					//See createKeyToCodeCompletionTable()
		action1="p";		//A string, the first character is either p, meaning "pressed", or r, meaning "released".
					//Or "pr" will do both immediately after each other.

		code2=0;		//See above.
		key2="a";		//see above.
		action2="r";		//See above.				
	*/
	public void processKeyeventLevel2(Event iEvent){
		/*
		encode a key sequence
		e.g.
		shift down; command down;  n down; n up; command up; shift up;
		
		field:
		seqNum
		key_x
		action_x = {up, down, press n release}
		maybe the duration of holding?
		*/
		if (iEvent.fieldExists("size")){
			try{
				Integer mSize = (Integer)iEvent.getPostValue("size");
				for (int i=1; i<=mSize.intValue(); i++){
					boolean requiredFieldsExists = 							
							iEvent.fieldExists("action"+i) && (iEvent.fieldExists("code"+i) || iEvent.fieldExists("key"+i));
					if (requiredFieldsExists){
						//determining what action
						Object actionObj = iEvent.getPostValue("action"+i);
						String action = "r";
						if (actionObj instanceof String)
							action = (String)actionObj;
						if (action.length()==0) 
							action = "r";
						action  = action.substring(0,2);
								
						Integer code;
	
						if (iEvent.fieldExists("code"+i)){
							Object codeObj = iEvent.getPostValue("code"+i);					
							if (codeObj instanceof Integer) code = (Integer)codeObj;
							else continue;
						}
						else if (iEvent.fieldExists("key"+i)){
							String key = iEvent.getPostValueString("key"+i);
							code = (Integer)keyToCodeCompletionTable.get(key);
							if (code==null) {
								System.out.println("Not defined key" +i + ": " + key);
								continue;
							}
						}
						else
							continue;

						//Use the robot
						if (keycodeTable.containsKey(code)){
							int vkey= ((Integer)keycodeTable.get(code)).intValue();
							if (action.equalsIgnoreCase("p")){								
								robot.keyPress(vkey);
							}
							else if (action.equalsIgnoreCase("r")){
								robot.keyRelease(vkey);
							}
							else if (action.equalsIgnoreCase("pr")){
								robot.keyPress(vkey);
								robot.keyRelease(vkey);
							}
						}				
					}//if -field exists
				}//end=for
			}
			catch (EventHeapException utfdataformatExp){
			}
			catch (ClassCastException ccexp){
				System.out.println(ccexp);
			}
			catch (NullPointerException nexp){
				nexp.printStackTrace();
			}
		}else{
			System.out.println("Missing size:int field.");
		}
	}
	
	//Process each incoming event, no matter up or down
	public void processKeyevent(Event iEvent){
		if (iEvent.fieldExists("code") && iEvent.fieldExists("key")){
			try{
				boolean currentIsDown  = false;
				if (iEvent.fieldExists("isDown")){
					currentIsDown  = (((Integer)iEvent.getPostValue("isDown")).equals(new Integer(1)));
				}
				Integer code = (Integer)iEvent.getPostValue("code");
				String key = "";
				try{
					key = iEvent.getPostValueString("key");
				}
				catch (EventHeapException utfdataformatExp){
				}
				//function keys
				//f1 = 122; f2=120; f3=99; f4=118; 
				//f5=96; f6=97; f7=98; f8 =100
				//f13 = 105;
				
				//In case that a key fires a system level event, use applescript to create this event
				Event oAppleScript = new Event("AppleScript");
				oAppleScript.setField("TimeToLive",new Integer(1000), FieldValueTypes.FORMAL);
				oAppleScript.setField("Target",mMachineName, FieldValueTypes.FORMAL);
				String mScript ="";
				
				if (code.intValue()==122){  //F1
				}
				else if (code.intValue()==120){  //F2
				}
				else if (code.intValue()==99){  //F3
				}
				else if (code.intValue()==118){  //F4
				}
				else if (code.intValue()==96){ //F5
					//sendZoomInEvent();
					robot.keyPress(java.awt.event.KeyEvent.VK_META);
					robot.keyPress(java.awt.event.KeyEvent.VK_ALT);
					robot.keyPress(java.awt.event.KeyEvent.VK_MINUS);
					robot.keyRelease(java.awt.event.KeyEvent.VK_MINUS);
					robot.keyRelease(java.awt.event.KeyEvent.VK_ALT);
					robot.keyRelease(java.awt.event.KeyEvent.VK_META);
				}
				else if (code.intValue()==97){ //F6
					robot.keyPress(java.awt.event.KeyEvent.VK_META);
					robot.keyPress(java.awt.event.KeyEvent.VK_ALT);
					robot.keyPress(java.awt.event.KeyEvent.VK_EQUALS);
					robot.keyRelease(java.awt.event.KeyEvent.VK_EQUALS);
					robot.keyRelease(java.awt.event.KeyEvent.VK_ALT);
					robot.keyRelease(java.awt.event.KeyEvent.VK_META);
				}
				else if (code.intValue()==98){ //F7
				}
				else if (code.intValue()==100){ //F8
				}
				else if (code.intValue()==105 && !currentIsDown){ //F13
					robot.keyPress(java.awt.event.KeyEvent.VK_F9);
					robot.keyRelease(java.awt.event.KeyEvent.VK_F9);
					//mScript = "tell application \"System Events\" to key code 101";
					//oAppleScript.setField("script", mScript, FieldValueTypes.FORMAL);
					//eheap.putEvent(oAppleScript);
				}
				else if (code.intValue()==10 && !currentIsDown){ //¤, there is no virtual key that can be mapped to it! So use it to invoke expose
					robot.keyPress(java.awt.event.KeyEvent.VK_F9);
					robot.keyRelease(java.awt.event.KeyEvent.VK_F9);
				}
			
			
				//check in code table, use keybot to input, this must be faster than using applescript
				if (keycodeTable.containsKey(code)){
					int vkey= ((Integer)keycodeTable.get(code)).intValue();
					boolean pastIsDown = false;
					if (keyDownTable.containsKey(code)==false && currentIsDown){
							keyDownTable.put(code,code);
							robot.keyPress(vkey);
					}
					else if (keyDownTable.containsKey(code)==true && !currentIsDown){
							keyDownTable.remove(code);
							robot.keyRelease(vkey);
					}
				}
			}
			//else fall through	
			catch (EventHeapException eexp){
				eexp.printStackTrace();
			}
			catch (ClassCastException ccexp){
				ccexp.printStackTrace();
			}
			catch (NullPointerException nexp){
				nexp.printStackTrace();
			}
		}//end if
	}
	
	
	//The following table is used to fetch the key code if only the string representation is given.
	public Hashtable createKeyToCodeCompletionTable(){
		Hashtable res = new Hashtable();
		//0-9
		res.put("\"0\"",new Integer(29));
		res.put("\"1\"",new Integer(18));
		res.put("\"2\"",new Integer(19));
		res.put("\"3\"",new Integer(20));
		res.put("\"4\"",new Integer(21));
		res.put("\"5\"",new Integer(23));
		res.put("\"6\"",new Integer(22));
		res.put("\"7\"",new Integer(26));
		res.put("\"8\"",new Integer(28));
		res.put("\"9\"",new Integer(25));

		//a - z
		res.put("a",new Integer(0));
		res.put("b",new Integer(11));
		res.put("c",new Integer(8));
		res.put("d",new Integer(2));
		res.put("e",new Integer(14));
		res.put("f",new Integer(3));
		res.put("g",new Integer(5));
		res.put("h",new Integer(4));
		res.put("i",new Integer(34));
		res.put("j",new Integer(38));
		res.put("k",new Integer(40));
		res.put("l",new Integer(37));
		res.put("m",new Integer(46));
		res.put("n",new Integer(45));
		res.put("o",new Integer(31));
		res.put("p",new Integer(35));
		res.put("q",new Integer(12));
		res.put("r",new Integer(15));
		res.put("s",new Integer(1));
		res.put("t",new Integer(17));
		res.put("u",new Integer(32));
		res.put("v",new Integer(9));
		res.put("w",new Integer(13));
		res.put("x",new Integer(7));
		res.put("y",new Integer(16));
		res.put("z",new Integer(6));
		
		//ARROWS? 
		res.put("-",new Integer(27));
		//TAB
		res.put("tab",new Integer(48));
		res.put("\\t",new Integer(48));
		
		//slash, 
		res.put("/", new Integer(44));
		//period
		res.put(".",new Integer(47));
		//colon - doesnot work, same code as ; = " ";"=41
		//res.put(new Integer(41), new Integer(java.awt.event.KeyEvent.VK_COLON));
		
		//Backspace
		//res.put(new Integer(51), new Integer(java.awt.event.KeyEvent.VK_BACK_SPACE));
		//Space
		res.put("\" \"",new Integer(49));
		//Return
		res.put("ret", new Integer(36));
		res.put("\\n", new Integer(36));
		//Arrow: code(up)=126; code(left)=123; code(right)=124; code(down)=125;
		
		//ESC
		res.put("esc",new Integer(53));
		
		//SHIFT
		res.put("shift",new Integer(56));
		//res.put(new Integer(60), new Integer(java.awt.event.KeyEvent.VK_SHIFT));
		
		//Fucntion key
		//res.put(new Integer(63), new Integer(java.awt.event.KeyEvent.VK_?));
		//CONTRL
		res.put("ctrl",new Integer(59));
		//ALT
		res.put("alt", new Integer(58));
		res.put("left_alt", new Integer(58));
		res.put("right_alt", new Integer(76));
		
		//APPLE COMMAND
		res.put("cmd",new Integer(55));
		//res.put(new Integer(54), new Integer(java.awt.event.KeyEvent.VK_META));
/*
		//Still has to define the string representation of the follwing keys.		
		//back-slash
		res.put(new Integer(42), new Integer(java.awt.event.KeyEvent.VK_BACK_SLASH));
		//'
		res.put(new Integer(39), new Integer(java.awt.event.KeyEvent.VK_QUOTE));
		//`
		res.put(new Integer(50), new Integer(java.awt.event.KeyEvent.VK_BACK_QUOTE));
		//]
		res.put(new Integer(30), new Integer(java.awt.event.KeyEvent.VK_CLOSE_BRACKET));
		//[
		res.put(new Integer(33), new Integer(java.awt.event.KeyEvent.VK_OPEN_BRACKET));
		//;
		res.put(new Integer(41), new Integer(java.awt.event.KeyEvent.VK_SEMICOLON));
		//,
		res.put(new Integer(43), new Integer(java.awt.event.KeyEvent.VK_COMMA));
		//=
		res.put(new Integer(24), new Integer(java.awt.event.KeyEvent.VK_EQUALS));
		//¤
		//res.put(new Integer(10), new Integer(java.awt.event.KeyEvent.VK_?));

		
		//???- Numpad
		res.put(new Integer(78), new Integer(java.awt.event.KeyEvent.VK_SUBTRACT));
		//? Numpad before =
		//res.put(new Integer(71), new Integer(java.awt.event.KeyEvent.VK_?));
		//= Numpad
		res.put(new Integer(81), new Integer(java.awt.event.KeyEvent.VK_EQUALS));
		
		/// Numpad
		res.put(new Integer(75), new Integer(java.awt.event.KeyEvent.VK_DIVIDE));
		
		// * Numpad
		res.put(new Integer(67), new Integer(java.awt.event.KeyEvent.VK_MULTIPLY));
		
		//Page up
		res.put(new Integer(116), new Integer(java.awt.event.KeyEvent.VK_PAGE_UP));
		//Page down
		res.put(new Integer(121), new Integer(java.awt.event.KeyEvent.VK_PAGE_DOWN));
		//home
		res.put(new Integer(115), new Integer(java.awt.event.KeyEvent.VK_HOME));
		//end
		res.put(new Integer(119), new Integer(java.awt.event.KeyEvent.VK_END));
		//delete
		res.put(new Integer(117), new Integer(java.awt.event.KeyEvent.VK_DELETE));*/
		return res;
	}
	
	
	//Table mapping incoming event's keycode to virtual key code
	public Hashtable createKeycodeTable(){
		Hashtable res = new Hashtable();
		//0-9
		res.put(new Integer(29), new Integer(java.awt.event.KeyEvent.VK_0));
		res.put(new Integer(18), new Integer(java.awt.event.KeyEvent.VK_1));
		res.put(new Integer(19), new Integer(java.awt.event.KeyEvent.VK_2));
		res.put(new Integer(20), new Integer(java.awt.event.KeyEvent.VK_3));
		res.put(new Integer(21), new Integer(java.awt.event.KeyEvent.VK_4));
		res.put(new Integer(23), new Integer(java.awt.event.KeyEvent.VK_5));
		res.put(new Integer(22), new Integer(java.awt.event.KeyEvent.VK_6));
		res.put(new Integer(26), new Integer(java.awt.event.KeyEvent.VK_7));
		res.put(new Integer(28), new Integer(java.awt.event.KeyEvent.VK_8));
		res.put(new Integer(25), new Integer(java.awt.event.KeyEvent.VK_9));

		//a - z
		res.put(new Integer(0), new Integer(java.awt.event.KeyEvent.VK_A));
		res.put(new Integer(11), new Integer(java.awt.event.KeyEvent.VK_B));
		res.put(new Integer(8), new Integer(java.awt.event.KeyEvent.VK_C));
		res.put(new Integer(2), new Integer(java.awt.event.KeyEvent.VK_D));
		res.put(new Integer(14), new Integer(java.awt.event.KeyEvent.VK_E));
		res.put(new Integer(3), new Integer(java.awt.event.KeyEvent.VK_F));
		res.put(new Integer(5), new Integer(java.awt.event.KeyEvent.VK_G));
		res.put(new Integer(4), new Integer(java.awt.event.KeyEvent.VK_H));
		res.put(new Integer(34), new Integer(java.awt.event.KeyEvent.VK_I));
		res.put(new Integer(38), new Integer(java.awt.event.KeyEvent.VK_J));
		res.put(new Integer(40), new Integer(java.awt.event.KeyEvent.VK_K));
		res.put(new Integer(37), new Integer(java.awt.event.KeyEvent.VK_L));
		res.put(new Integer(46), new Integer(java.awt.event.KeyEvent.VK_M));
		res.put(new Integer(45), new Integer(java.awt.event.KeyEvent.VK_N));
		res.put(new Integer(31), new Integer(java.awt.event.KeyEvent.VK_O));
		res.put(new Integer(35), new Integer(java.awt.event.KeyEvent.VK_P));
		res.put(new Integer(12), new Integer(java.awt.event.KeyEvent.VK_Q));
		res.put(new Integer(15), new Integer(java.awt.event.KeyEvent.VK_R));
		res.put(new Integer(1), new Integer(java.awt.event.KeyEvent.VK_S));
		res.put(new Integer(17), new Integer(java.awt.event.KeyEvent.VK_T));
		res.put(new Integer(32), new Integer(java.awt.event.KeyEvent.VK_U));
		res.put(new Integer(9), new Integer(java.awt.event.KeyEvent.VK_V));
		res.put(new Integer(13), new Integer(java.awt.event.KeyEvent.VK_W));
		res.put(new Integer(7), new Integer(java.awt.event.KeyEvent.VK_X));
		res.put(new Integer(16), new Integer(java.awt.event.KeyEvent.VK_Y));
		res.put(new Integer(6), new Integer(java.awt.event.KeyEvent.VK_Z));
		
		
		res.put(new Integer(27), new Integer(java.awt.event.KeyEvent.VK_MINUS));
		res.put(new Integer(123), new Integer(java.awt.event.KeyEvent.VK_LEFT));
		res.put(new Integer(124), new Integer(java.awt.event.KeyEvent.VK_RIGHT));
		res.put(new Integer(125), new Integer(java.awt.event.KeyEvent.VK_DOWN));
		res.put(new Integer(126), new Integer(java.awt.event.KeyEvent.VK_UP));
		//TAB
		res.put(new Integer(48), new Integer(java.awt.event.KeyEvent.VK_TAB));
		
		//slash, 
		res.put(new Integer(44), new Integer(java.awt.event.KeyEvent.VK_SLASH));
		//period
		res.put(new Integer(47), new Integer(java.awt.event.KeyEvent.VK_PERIOD));
		//colon - doesnot work, same code as ; = " ";"=41
		res.put(new Integer(41), new Integer(java.awt.event.KeyEvent.VK_COLON));
		
		//Backspace
		res.put(new Integer(51), new Integer(java.awt.event.KeyEvent.VK_BACK_SPACE));
		//Space
		res.put(new Integer(49), new Integer(java.awt.event.KeyEvent.VK_SPACE));
		//Return
		res.put(new Integer(36), new Integer(java.awt.event.KeyEvent.VK_ENTER));
		//Arrow: code(up)=126; code(left)=123; code(right)=124; code(down)=125;
		
		//ESC
		res.put(new Integer(53), new Integer(java.awt.event.KeyEvent.VK_ESCAPE));
		
		//SHIFT
		res.put(new Integer(56), new Integer(java.awt.event.KeyEvent.VK_SHIFT));
		res.put(new Integer(60), new Integer(java.awt.event.KeyEvent.VK_SHIFT));
		
		//Fucntion key
		//res.put(new Integer(63), new Integer(java.awt.event.KeyEvent.VK_?));
		//CONTRL
		res.put(new Integer(59), new Integer(java.awt.event.KeyEvent.VK_CONTROL));
		//ALT
		res.put(new Integer(58), new Integer(java.awt.event.KeyEvent.VK_ALT));
		res.put(new Integer(76), new Integer(java.awt.event.KeyEvent.VK_ALT_GRAPH));
		
		//APPLE COMMAND
		res.put(new Integer(55), new Integer(java.awt.event.KeyEvent.VK_META));
		res.put(new Integer(54), new Integer(java.awt.event.KeyEvent.VK_META));
		
		//back-slash
		res.put(new Integer(42), new Integer(java.awt.event.KeyEvent.VK_BACK_SLASH));
		//'
		res.put(new Integer(39), new Integer(java.awt.event.KeyEvent.VK_QUOTE));
		//`
		res.put(new Integer(50), new Integer(java.awt.event.KeyEvent.VK_BACK_QUOTE));
		//]
		res.put(new Integer(30), new Integer(java.awt.event.KeyEvent.VK_CLOSE_BRACKET));
		//[
		res.put(new Integer(33), new Integer(java.awt.event.KeyEvent.VK_OPEN_BRACKET));
		//;
		res.put(new Integer(41), new Integer(java.awt.event.KeyEvent.VK_SEMICOLON));
		//,
		res.put(new Integer(43), new Integer(java.awt.event.KeyEvent.VK_COMMA));
		//=
		res.put(new Integer(24), new Integer(java.awt.event.KeyEvent.VK_EQUALS));
		//¤
		//res.put(new Integer(10), new Integer(java.awt.event.KeyEvent.VK_?));
		
		//Keine Wirkung: VK_FIND , VK_UNDO, VK_COPY, VK_PASTE, VK_UNDO
		
		//0 Numpad
		res.put(new Integer(82), new Integer(java.awt.event.KeyEvent.VK_NUMPAD0 ));
		//????. Numpad
		res.put(new Integer(65), new Integer(java.awt.event.KeyEvent.VK_DECIMAL));
		//????ret Numpad
		res.put(new Integer(76), new Integer(java.awt.event.KeyEvent.VK_ENTER));
		//1 Numpad
		res.put(new Integer(83), new Integer(java.awt.event.KeyEvent.VK_NUMPAD1));
		//2 Numpad
		res.put(new Integer(84), new Integer(java.awt.event.KeyEvent.VK_NUMPAD2));
		//3 Numpad
		res.put(new Integer(85), new Integer(java.awt.event.KeyEvent.VK_NUMPAD3));
		//4 Numpad
		res.put(new Integer(86), new Integer(java.awt.event.KeyEvent.VK_NUMPAD4));
		//5 Numpad
		res.put(new Integer(87), new Integer(java.awt.event.KeyEvent.VK_NUMPAD5));
		//6 Numpad
		res.put(new Integer(88), new Integer(java.awt.event.KeyEvent.VK_NUMPAD6));
		//????+ Numpad 
		res.put(new Integer(69), new Integer(java.awt.event.KeyEvent.VK_ADD));
		//7 Numpad
		res.put(new Integer(89), new Integer(java.awt.event.KeyEvent.VK_NUMPAD7));
		//8 Numpad
		res.put(new Integer(91), new Integer(java.awt.event.KeyEvent.VK_NUMPAD8));
		//9 Numpad
		res.put(new Integer(92), new Integer(java.awt.event.KeyEvent.VK_NUMPAD9));
		//???- Numpad
		res.put(new Integer(78), new Integer(java.awt.event.KeyEvent.VK_SUBTRACT));
		//? Numpad before =
		//res.put(new Integer(71), new Integer(java.awt.event.KeyEvent.VK_?));
		//= Numpad
		res.put(new Integer(81), new Integer(java.awt.event.KeyEvent.VK_EQUALS));
		
		/// Numpad
		res.put(new Integer(75), new Integer(java.awt.event.KeyEvent.VK_DIVIDE));
		
		// * Numpad
		res.put(new Integer(67), new Integer(java.awt.event.KeyEvent.VK_MULTIPLY));
		
		//Page up
		res.put(new Integer(116), new Integer(java.awt.event.KeyEvent.VK_PAGE_UP));
		//Page down
		res.put(new Integer(121), new Integer(java.awt.event.KeyEvent.VK_PAGE_DOWN));
		//home
		res.put(new Integer(115), new Integer(java.awt.event.KeyEvent.VK_HOME));
		//end
		res.put(new Integer(119), new Integer(java.awt.event.KeyEvent.VK_END));
		//delete
		res.put(new Integer(117), new Integer(java.awt.event.KeyEvent.VK_DELETE));
		

		return res;
	}
	
	
	//Not used
	public Hashtable createMetaKeycodeTable(){
		Hashtable res = new Hashtable();
		///shift
		//control
		//alt
		//command
		return res;
	}

	//iMachinName is the name of the host reacting to the events
	//eventHeapName is the name used to create the event heap object, e.g. parker, 137.226.56.20
	public KeyRobot(String eventHeapName, String iMachineName) {
		
		try{
			mMachineName = iMachineName;
			eheap = new EventHeap(eventHeapName);
			keycodeTable = createKeycodeTable();
			metaKeycodeTable = createMetaKeycodeTable();
			keyToCodeCompletionTable = createKeyToCodeCompletionTable();
			keyDownTable = new Hashtable();
			
			robot = new Robot();

			String openSlides = "";
			Event template = new Event("KEYBOARD");
			//This is how to set a filter
			template.addField("level", Integer.class);
			template.addField("Target", String.class);
			//template.setTemplateValue("level", FieldValueTypes.VIRTUAL); //This does not work somehow, cannot filter out events that does not have this field
			template.setTemplateValue("Target", FieldValueTypes.VIRTUAL);

			Event received;
			while( running){
				received = eheap.waitForEvent(template);
				try{
					//Strange result, returns 0 although the field exisst
					Integer level;
					if (received.fieldExists("level"))
						level = (Integer)received.getPostValue("level");
					else 
						level = new Integer(0);
						
					if (level.intValue()<1) continue;
				
					String Target = (String)received.getPostValueString("Target");
					boolean matchTarget = Target.equals(mMachineName)	
							|| Target.equals("*")
							|| Target.equalsIgnoreCase("ALL");
					if (!matchTarget) continue;

					if (level.intValue()==1)
							processKeyevent(received);
					else if (level.intValue()==2)
							processKeyeventLevel2(received);
					//f1 = 122; f2=120; f3=99; f4=118; 
					//f5=96; f6=97; f7=98; f8 =100
					//f13 = 105;
					//f9=? ;f10=?  f11=? //not available, because similar to the tab key combination, those key are processed by the system rather than delegated to the Keyboard event sender
				}
				catch (EventHeapException eexp){
					eexp.printStackTrace();
				}
				catch (NullPointerException nexp){
					nexp.printStackTrace();
				}
			} // end while	
		} catch( Exception ex ){
			ex.printStackTrace();
		}
	}

	
	public static void main(String argv[]){
		if(argv.length == 2){
			KeyRobot sc = new KeyRobot(argv[0], argv[1]);
		} else {
			System.out.println("Usage: KeyRobot <Event Heap Name> or <Machine Name> not provided");
		} 
	}
	
}
