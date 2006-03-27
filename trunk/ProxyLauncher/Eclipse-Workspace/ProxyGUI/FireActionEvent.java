import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.event.EventListenerList;
 
public class FireActionEvent {
    		
	public static void fireEvent(ActionEvent evt, EventListenerList listenerList) {
    			Object[] listeners = listenerList.getListenerList();
    			// Each listener occupies two elements - the first is the listener class
    			// and the second is the listener instance
    			for (int i=0; i<listeners.length; i+=2) {
    				if (listeners[i]==ActionListener.class) {
    					((ActionListener)listeners[i+1]).actionPerformed (evt);
    				}
    			}
    		}
    }