//
//  SimpleEventHandler.java
//  SimpleEventHandler version 0.2
//
//  Created by Andy Szybalski on Sat Feb 01 2003.
//  Modified to limit sending to 1 event per 50 ms (ver 0.2)
//

package iwork.gamecontroller;

import java.util.*; // for Timer and TimerTask
import iwork.eheap2.*;
import iwork.eheap2.EventRegistration;
import iwork.eheap2.EventCallback;

public class SimpleEventHandler {
    public static final int SERVER_TIMEOUT = 10000; // 4 sec timeout
    public static final int SEND_INTERVAL = 50; // milliseconds
	
    private EventHeap theEventHeap;
    private EventRegistration theRegistration;
    private String appName;
    private boolean validEventHeap;
	
	//private boolean eventUpdated = false;
	//private Event eventToSend = null;

    private String heapMachine;
    private int heapPort;
	private Timer timer = new Timer();
	private int numEventsSent = 0;
	private long latencySum = 0;
	private int numEventsProcessed = 0;
	//private boolean noNewEvents = true;

    public SimpleEventHandler(String appName, String heapMachine, int heapPort) {
        this.appName = appName;
        this.heapMachine = heapMachine;
        this.heapPort = heapPort;
        this.validEventHeap = false;
        this.theEventHeap = null;

        EventHeapInitializer initializer = new EventHeapInitializer(heapMachine, heapPort);
        Thread initThread = new Thread(initializer);
        initThread.start();
        try {
            initThread.join(SERVER_TIMEOUT);
        } catch (InterruptedException ex) {
            //this shouldn't ever happen
            ex.printStackTrace();
        }

        if (initThread.isAlive()) {
            initThread.interrupt();
            System.out.println("No valid server found. Server initialization interrupted.");
            validEventHeap = false;
        } else {
            validEventHeap = initializer.validEventHeap();
            if (validEventHeap) {
                this.theEventHeap = initializer.theEventHeap;
                System.out.println("Connection established.");
				//mer.schedule(new EventSender(), 0, SEND_INTERVAL);
				//Thread senderThread = new Thread(new EventSender());
				//senderThread.start();
            }
        }
    }
	
	//public synchronized boolean eventUpdated() {
	//	return eventUpdated;
	//}
	
	//public synchronized void setEventUpdated(boolean updated) {
	//	this.eventUpdated = updated;	
	//

    public boolean validEventHeap() {
        return validEventHeap;
    }

    // registerForAll():
    // -----------------
    // Returns true if successful, false if unsuccessful

    public boolean registerForAll(EventCallback callback) {
        if (!validEventHeap) return false;
        try {
            theRegistration= theEventHeap.registerForAll(callback);
        } catch (EventHeapException ex) {
            ex.printStackTrace();
            return false;
        }
        // System.out.println("Registered for events.");
        return true;
    }

    private class EventHeapInitializer implements Runnable {
        public EventHeap theEventHeap;
        public String heapMachine;
        public int heapPort;

        public EventHeapInitializer(String heapMachine, int heapPort) {
            theEventHeap = null;
            this.heapMachine = heapMachine;
            this.heapPort = heapPort;
        }

        public void run() {
            // debug code:
            System.out.println("Attempting to connect to Event Heap:\n" +
                               "\tEHeap Host Machine:\t" + heapMachine + "\n" +
                               "\tEHeap Port:\t\t" + heapPort + "\n" +
                               "\tOur Application Name:\t\t'"+appName+"'");
            //////

            theEventHeap=new EventHeap(appName, heapMachine, heapPort,
                                       null, null, appName);
            if (theEventHeap == null)
                System.out.println("Error: EventHeap object could not be created.");
            System.out.println("\tMy source name:\t\t" +
                               theEventHeap.getSourceName());
        }

        public boolean validEventHeap() {
            return (theEventHeap != null);
        }
    }

    public void sendEventNow(Event e) {
        try {			
            if (theEventHeap != null) {
                theEventHeap.putEvent(e);
                numEventsSent++;
                if (GameController.BENCHMARK) {
                    double latency = GameController.hiResTimer.endTiming(GameController.triggerTime);
                    latencySum += latency;
                    System.out.print("\r" + numEventsSent + " events sent (" + latency + " ms).");
                    if (numEventsSent % 10 == 0) {
                            System.out.println(" \tAverage latency: " + latencySum/numEventsSent + " ms");
                    }
                }
            }
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
    }

    public static final int TIMEOUT = 5000;
    
    public void sendEventAndWait(Event e) {
        try {
            if (theEventHeap != null) {
                Event[] templateEvents = { e };
                sendEventNow(e);
                //theEventHeap.waitForEvent(e);
                theEventHeap.registerForEvents(templateEvents, new EventWaitCallback(Thread.currentThread()));
                boolean eventReceived = false;
                try {
                    Thread.sleep(TIMEOUT);
                } catch (InterruptedException ex) {
                    eventReceived = true;
                }
                if (!eventReceived) {
                    System.out.println("Error: event dropped.");
                } else {
                    System.out.println("Event sent successfully.");
                }
            }
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
    }
    
    public class EventWaitCallback implements EventCallback {
        Thread t;
        public EventWaitCallback (Thread t) {
            this.t = t;
        }
        public boolean returnEvent(Event[] retEvents) {
            t.interrupt();
            return true; // continue receiving callbacks.
        }
    }

    public void deregister() {
        if (theRegistration != null) theRegistration.deregister();
        //System.out.println("Deregistered for events.");
    }

    public String getMyName() {
        return appName;
    }

    public int getServerVersion() {
        if (theEventHeap != null) return theEventHeap.getVersion();
        else return 0;
    }

    public String getMachine() {
        if (theEventHeap != null) return theEventHeap.getMachine();
        else return "N/A";
    }

    public String getHeapMachine() {
        return heapMachine;
    }

    public int getHeapPort() {
        return heapPort;
    }
}
