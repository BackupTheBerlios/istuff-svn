import java.awt.Robot;
import java.awt.event.*;
import iwork.eheap2.*;

public class SlideController{

	private Robot robot = null;

	public SlideController(String eventHeapName) {
		try{
			EventHeap eheap = new EventHeap(eventHeapName);
			robot = new Robot();
			String openSlides = "";
			
			Event template = new Event("SlideController");
			Event received;
			while( true ){
				received = eheap.waitForEvent(template);
				String command = received.getPostValueString("command");
				if( command.equals("next") ){
					nextSlide();
				} else if( command.equals("prev") ){
					prevSlide();
				} else if( command.equals("open") ){
					String url = received.getPostValueString("url");
					// opening the same slides twice can be problematic
					// make sure this is not a repeat
					if(!openSlides.equals(url)){
						Runtime rt = Runtime.getRuntime();
						if( System.getProperty("os.name").equals("Mac OS X") )
						{
							rt.exec("open " + url);
						} 
						else if (System.getProperty("os.name").equals("Windows XP"))
						{
							rt.exec("explorer " + url);
						}
						/*synchronized(this)
						{
							// provide time for the presentation to launch up
							wait(4000);
						}*/
						openSlides = url;
					}
				}
			}
		} catch( Exception ex ){
			ex.printStackTrace();
		}
	}

	
	public void nextSlide(){
		robot.keyPress(KeyEvent.VK_N);
		robot.keyRelease(KeyEvent.VK_N);
		//robot.mousePress(InputEvent.BUTTON1_MASK);
		//robot.mouseRelease(InputEvent.BUTTON1_MASK);
	}

	public void prevSlide(){
		robot.keyPress(KeyEvent.VK_P);
		robot.keyRelease(KeyEvent.VK_P);
	}
	
	public static void main(String argv[]){
		if(argv.length == 1){
			SlideController sc = new SlideController(argv[0]);
		} else {
			System.out.println("Usage: SlideController <Event Heap Name>");
		}
	}

}
