//
//  iPongEvents.java
//  GameController
//
//  Created by Andy Szybalski on Mon Feb 24 2003.
//
//  This simple class was written for the purpose of debugging GameController.
//  It has a bunch of static methods that return iPongEvents ready to send to an EventHeap.

package iwork.gamecontroller;
import iwork.eheap2.*;


public class iPongEvents {

    public static final String[] IPONG_SIDES = {"Left", "Right"};

    // methods sendMovePaddleRelativeEvent() and sendSetPaddleVelocityEvent()
    // have public access to allow calling by GameController debug buttons
    // where side == "Left" or "Right"

    public static Event movePaddleRelative(String side, int delta) {
        Event ev = getBasicPongEvent(side);
        try {
            ev.addField("iPongEventType", "MovePaddleRelative");
            ev.addField("Delta", new Integer(delta));
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
        
        return ev;
    }

    public static Event setPaddleVelocity(String side, double velocity) {
        Event ev = getBasicPongEvent(side);
        try {
            ev.addField("iPongEventType", "SetPaddleVelocity");
            ev.addField("Velocity", new Double(velocity));
        } catch (EventHeapException ex) {
            ex.printStackTrace();
        }
        
        return ev;
    }
    

    // getBasicPongEvent()
    // -------------------
    
    private static Event getBasicPongEvent(String side) {
        try {
            Event e = new Event("iPongEvent");
            e.addField("Side", side);
            return e;
        } catch (EventHeapException ex) {
            ex.printStackTrace();
            return null;
        }
    }
}
