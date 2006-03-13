import java.awt.Robot;
import java.awt.event.*;
import iwork.eheap2.*;
import java.util.*;

public class KeyRobot{

	private Robot robot = null;
	private boolean running = true;
	private Hashtable keyDownTable;
	
	private Hashtable keycodeTable;
	private Hashtable metaKeycodeTable;
	private EventHeap eheap;
	private String mMachineName;
	
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
		if (iEvent.fieldExists("code") && iEvent.fieldExists("key")){
		
		}
	}
	
	public void processKeyevent(Event iEvent){
		if (iEvent.fieldExists("code") && iEvent.fieldExists("key")){
			try{
				boolean currentIsDown  = (((Integer)iEvent.getPostValue("isDown")).equals(new Integer(1)));
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
					System.out.println("Copy");
					robot.keyPress(java.awt.event.KeyEvent.VK_COPY);
					robot.keyRelease(java.awt.event.KeyEvent.VK_COPY);
				}
				else if (code.intValue()==97){ //F6
					System.out.println("Paste");
					robot.keyPress(java.awt.event.KeyEvent.VK_PASTE);
					robot.keyRelease(java.awt.event.KeyEvent.VK_PASTE);
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
				else if (code.intValue()==10 && !currentIsDown){ //¤, there is no virtual key that can be mapped to it!
						robot.keyPress(java.awt.event.KeyEvent.VK_F9);
						robot.keyRelease(java.awt.event.KeyEvent.VK_F9);
				}
			
			
				//check in code table, use keybot to input, this must be faster than using applescript
				if (keycodeTable.containsKey(code)){
					int vkey= ((Integer)keycodeTable.get(code)).intValue();
					boolean pastIsDown = false;
					//no entry  &  current down    => keyPress + Eintrag
					//no entry  &  ~ current down = release => do nothing; kann nicht sein
					//has entrty & current down		=> key repeat
					//has entrty & ~ current down	=> keyRelease
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
			
		}//end if
	}
	
	
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
	
	
	
	public Hashtable createMetaKeycodeTable(){
		Hashtable res = new Hashtable();
		///shift
		//control
		//alt
		//command
		return res;
	}

	public KeyRobot(String eventHeapName, String iMachineName) {
		
		try{
			mMachineName = iMachineName;
			eheap = new EventHeap(eventHeapName);
			keycodeTable = createKeycodeTable();
			metaKeycodeTable = createMetaKeycodeTable();
			keyDownTable = new Hashtable();
			
			robot = new Robot();

			String openSlides = "";
			Event template = new Event("KEYBOARD");
			template.addField("code", Integer.class);
			template.addField("level", Integer.class);
			template.addField("Target", String.class);
			Event received;
			while( running){
				received = eheap.waitForEvent(template);
				try{
					Integer level = (Integer)received.getPostValue("level");
					if (level.intValue()<1) continue;
				
					String Target = (String)received.getPostValueString("Target");
					if (!Target.equals(mMachineName)) continue;
		
					processKeyevent(received);
					//f1 = 122; f2=120; f3=99; f4=118; 
					//f5=96; f6=97; f7=98; f8 =100
					//f13 = 105;
					//f9=? ;f10=?  f11=? //not available
					//Arrow keys
					
					//char charCode =
					//	int KeyCode = ;
					//int State = 
				}
				catch (EventHeapException eexp){
					eexp.printStackTrace();
				}
			} // end while	
		} catch( Exception ex ){
			ex.printStackTrace();
		}
	}

	public void gotoSlide(int num){
		try{
			if(num <= 0) {num = 1;}
				String numString = Integer.toString(num);
				char[] digits = numString.toCharArray();
				for(int i=0; i < digits.length; i++){
					int keyCode = KeyEvent.VK_0 + Integer.parseInt(digits[i]+"");
					robot.keyPress(keyCode);
					robot.keyRelease(keyCode);			
				
				// sleep required for Keynote to respond correctly
				//Thread.sleep(3000);
				robot.keyPress(KeyEvent.VK_ENTER);
				robot.keyRelease(KeyEvent.VK_ENTER);
			}
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
