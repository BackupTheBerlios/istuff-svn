import java.io.File;
import java.io.IOException;

public class EventHeapThread extends Thread{

	  public void run()
	  {
		  File env = new File("/Users/rene/DiplomaThesis/Programming/trunk/Event\\ Heap");
		  System.out.println("Env Path: " + env);
		  try {
			   Process _ehProcess = Runtime.getRuntime().exec(
					  "java -cp ../Lib/iROS.jar:../Lib/jmdns.jar iwork.eheap2.server.EventHeapServer",null,env);
		  }
		  catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	  }

}
