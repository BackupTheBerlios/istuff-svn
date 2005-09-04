// EHEventHeap.java

package ehwrapper;

import iwork.eheap2.*;

/**
 * Wrapper class for iwork.eheap2.EventHeap.
 *
 * <p> It was created to complement the convenience wrapper EHEvent.
 * <p> Like EHEvent, all method calls handle the try...catch wrapping for you.
 * <p> Note that all methods that take an event take an iwork.eheap2.Event (or
 * an ehwrapper.EHEvent, which is a subclass) but return an ehwrapper.EHEvent.
 * This is done so the EHEvent convenience methods can be used on the returned
 * events.
 */

public class EHEventHeap extends iwork.eheap2.EventHeap
{
    public EHEventHeap(String machine)
    {
        super(machine);
    }
    
    public void putEvent(Event e)
    {
        try {
            super.putEvent(e);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    public EHEvent getEHEvent(Event e)
    {
        try {
            Event result = super.getEvent(e);
            if (result == null) return null;
            else return new EHEvent(result);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    public EHEvent removeEHEvent(Event e)
    {
        try {
            Event result = super.removeEvent(e);
            if (result == null) return null;
            else return new EHEvent(result);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    public void deleteEvent(Event e)
    {
        try {
            super.deleteEvent(e);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    public EHEvent waitForEHEvent(Event e)
    {
        try {
            return new EHEvent(super.waitForEvent(e));
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    public EHEvent waitToRemoveEHEvent(Event e)
    {
        try {
            return new EHEvent(super.waitToRemoveEvent(e));
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }

    public void registerForEvent(Event e, final EHHandler handler) {
        try {
            Event[] events = new Event[1];
            events[0] = e;
            super.registerForEvents(events, new EventCallback() {
                public boolean returnEvent(Event[] retEvents) {
                    handler.handleEHEvent(new EHEvent(retEvents[0]));
                    return true;
                }
            });
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
}
