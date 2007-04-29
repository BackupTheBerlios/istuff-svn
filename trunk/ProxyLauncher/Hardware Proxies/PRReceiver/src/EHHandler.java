// EHHandler.java

package ehwrapper;

import iwork.eheap2.*;

/**
 * Implement this interface to handle EventHeap events caught by an EHListener
 * Note that the event receieved in the callback is an EHEvent, so its convenience
 * methods can be used.
 */

public interface EHHandler
{
    public void handleEHEvent(EHEvent e);
}
