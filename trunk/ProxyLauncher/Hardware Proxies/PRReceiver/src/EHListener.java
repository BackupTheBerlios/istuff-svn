// EHListener.java

package ehwrapper;

import iwork.eheap2.*;

/**
 * A listening thread to catch EventHeap events.
 *
 * <p> Creating an EHListener spawns a new thread that blocks waiting for events that
 * match the given template event.  It does not remove event from the EventHeap (it uses
 * 'waitForEvent').  When an event is received, it calls the callback method of the
 * specified EHHandler (handleEHEvent).  Note that handleEHEvent executes in the listening
 * thread, so any operations in this callback need to be thread safe, and the EHListener
 * is not listening while the callback is executing (it should therefore execute quickly).
 *
 * <p> To use an EHListener, you need three things:
 * <br> - an EHEventHeap (easily created with the name of the EventHeap server),
 * <br> - a template Event (may be either an Event or an EHEvent), and
 * <br> - a class that implements the EHHandler interface (which consists of one callback method).
 *
 * <p> Because the EHListener rarely needs to be reference after it is created,
 * the static 'create' method can be used (as a convenience).
 */

public class EHListener extends Thread
{
    public static void create(EHEventHeap eheap, Event template, EHHandler handler)
    {
        new EHListener(eheap, template, handler);
    }


    EHEventHeap eheap;
    Event template;
    EHHandler handler;
    
    public EHListener(EHEventHeap eheap, Event template, EHHandler handler)
    {
        super();
        this.eheap = eheap;
        this.template = template;
        this.handler = handler;
        setDaemon(true);
        start();
    }
    
    public void run()
    {
        while (true) {
            EHEvent e = eheap.waitForEHEvent(template);
            handler.handleEHEvent(e);
        }
    }
}
