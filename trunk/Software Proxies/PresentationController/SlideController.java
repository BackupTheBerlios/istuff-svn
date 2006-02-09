import java.awt.Robot;
import java.awt.event.*;
import iwork.eheap2.*;

public class SlideController{

	private Robot robot = null;

	public SlideController(String eventHeapName, String machineName) {
	
		try{
			EventHeap eheap = new EventHeap(eventHeapName);
			robot = new Robot();
			String openSlides = "";
			System.out.println("MACHINE NAME IS: " + machineName);
			Event template = new Event("SlideController");
			Event received;
			while( true ){
				received = eheap.waitForEvent(template);
				//System.out.println("Value of MachineName is: " + received.getPostValueString("MachineName"));
				if (received.getPostValueString("MachineName").equals(machineName))
				{
				String command = received.getPostValueString("command");
				System.out.println("An Event for this machine was received: " + command);
				if( command.equals("next") ){
					nextSlide();
				} else if( command.equals("prev") ){
					prevSlide();
				} else if( command.equals("fullScreen") ){
					fullScreen();
				} else if( command.equals("gotoSlide") ){
					Integer slideNum = (Integer)received.getPostValue("slideNum");
					gotoSlide(slideNum.intValue());
				} else if( command.equals("open") ){
					String url = received.getPostValueString("url");
					// opening the same slides twice can be problematic
					// make sure this is not a repeat
					if(!openSlides.equals(url)){
						Runtime rt = Runtime.getRuntime();
						if( System.getProperty("os.name").equals("Mac OS X") )
						{
							// if http, first wget
							// then file is local
							rt.exec("open " + url);
						} 
						else if (System.getProperty("os.name").equals("Windows XP"))
						{
							// if http, print an error message that says wget must be installed, see readme
							// try wget
							rt.exec("explorer " + url);
						}

						// Provide time for the presentation to start up
						Thread.sleep(10000);
					
						openSlides = url;
					}
				} else if (command.equals("startPresentation1")) {
					String presentationURL = received.getPostValueString("URL");
					Runtime rt = Runtime.getRuntime();
					//closeCurrentPresentation();
					//Thread.sleep(2000);
					rt.exec ("open " + presentationURL);
					Thread.sleep(10000);
				}
			} // end if
		} // end while	
		} catch( Exception ex ){
			ex.printStackTrace();
		}
	}


	public void closeCurrentPresentation(){
		//Keynote COMMAND+W
		robot.keyPress(KeyEvent.VK_META);
		robot.keyPress(KeyEvent.VK_W);
		robot.keyRelease(KeyEvent.VK_W);
		robot.keyRelease(KeyEvent.VK_META);
	}
	
	public void fullScreen(){
		// Keynote ALT+COMMAND+P
		robot.keyPress(KeyEvent.VK_ALT);
		robot.keyPress(KeyEvent.VK_META);
		robot.keyPress(KeyEvent.VK_P);
		robot.keyRelease(KeyEvent.VK_P);
		robot.keyRelease(KeyEvent.VK_META);
		robot.keyRelease(KeyEvent.VK_ALT);
		
		
		// PowerPoint CTRL+SHIFT+S
		robot.keyPress(KeyEvent.VK_SHIFT);
		robot.keyPress(KeyEvent.VK_CONTROL);
		robot.keyPress(KeyEvent.VK_S);
		robot.keyRelease(KeyEvent.VK_S);
		robot.keyRelease(KeyEvent.VK_CONTROL);
		robot.keyRelease(KeyEvent.VK_SHIFT);
	}
	
	public void nextSlide(){
		robot.keyPress(KeyEvent.VK_N);
		robot.keyRelease(KeyEvent.VK_N);
	}

	public void prevSlide(){
		robot.keyPress(KeyEvent.VK_P);
		robot.keyRelease(KeyEvent.VK_P);
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
			SlideController sc = new SlideController(argv[0], argv[1]);
		} else {
			System.out.println("Usage: SlideController <Event Heap Name> or <Machine Name> not provided");
		} 
	}
		

}
