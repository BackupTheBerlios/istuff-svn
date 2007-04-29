
import java.io.*;
import java.util.*;
import javax.comm.*;
import java.nio.*;


public class fakeRFID {
	
	private Vector clients = new Vector();
	private TimerThread tt;
	
	
	public fakeRFID( String portName ){
		tt = new TimerThread();
	}

	
	public void register(RFIDListener lt) {
        clients.add(lt);
		tt.run();
    }
	
    public void notifyClients(String rfid) {
        Iterator it = clients.iterator();
        while (it.hasNext()) {
            RFIDListener lt = (RFIDListener) it.next();
            lt.callback(rfid);
        }
    }
	
	public class TimerThread implements Runnable{
		public void run(){
			try{
				synchronized(this){
					this.wait(1000);
				}
				notifyClients(RFIDproxy.START_TAG);
				for(int i = 0; i < 10; i++){
					synchronized(this){
						this.wait(3000);
					}
					notifyClients(RFIDproxy.NEXT_TAG);
				}
				synchronized(this){
					this.wait(1000);
				}
				notifyClients(RFIDproxy.PREV_TAG);
			}catch(Exception ex){
				ex.printStackTrace();
			}
		}
	}
}


