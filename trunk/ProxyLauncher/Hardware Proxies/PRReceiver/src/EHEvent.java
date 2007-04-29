// EHEvent.java

package ehwrapper;

import iwork.eheap2.*;
import java.io.Serializable;

/**
 * Wrapper class for iwork.eheap2.Event.
 * 
 * <p> It was created for several reasons:
 * 
 * <p> a) Because nearly every method in Event throws an exception, it can be a pain to use.
 * Most of the exceptions are thrown only in the case of a fatal error, so in typical use
 * the method calls are wrapped in a try...catch block that simply prints out the details
 * of the exception.  To alleviate the pain of having to do this every time a method is
 * called, this wrapper does this step for you.
 * <br> (The one side affect is that, since the constructor throws an exception, and it cannot
 * be wrapped in a try...catch block since super() must be the first call, EHEvents should
 * be created using the static 'create' methods, which are able to do the necessary wrapping)
 * 
 * <p> b) When adding fields to an Event, non-string values must be encapsulated in Serializable objects.
 * (e.g. a value of type 'int' must be put in a object of type 'Integer')  The addField methods of
 * EHEvent are overridden to do this for you - give them a int, float, etc., and they'll wrap them
 * in an object of the necessary type.
 * 
 * <p> c) Similarly, when retrieving field values, the returned Serializable object must be cast to the
 * appropriate type before their value can be seen.  EHEvent contains several convenience methods
 * that do this casting for you for the most commonly used types (int, float, etc.)  Note that no
 * error checking is done - attempts to cast objects incorrectly will probably cause a fatal error.
 * 
 * <p> Note that EHEvent is a *subclass* of Event, so any of the methods not explictily overridden are
 * still available, albeit in their less convenient forms.
 */
public class EHEvent extends iwork.eheap2.Event
{
    public static EHEvent create(String eventType)
    {
        try {
            return new EHEvent(eventType);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    public static EHEvent create(String eventType, long timeToLive)
    {
        try {
            return new EHEvent(eventType, timeToLive);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    
    
    public EHEvent(String eventType) throws EventHeapException
    {
        super(eventType);
    }
    
    public EHEvent(String eventType, long timeToLive) throws EventHeapException
    {
        super(eventType);
        setTimeToLive(timeToLive);
    }
    
    public EHEvent(Tuple tuple)
    {
        super(tuple);
    }
    
    
    
    public void addField(String name, java.io.Serializable value)
    {
        try {
            super.addField(name, value);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    public void addField(String name, int value)
    {
        try {
            super.addField(name, new Integer(value));
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    public void addField(String name, long value)
    {
        try {
            super.addField(name, new Long(value));
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    public void addField(String name, float value)
    {
        try {
            super.addField(name, new Float(value));
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    public void addField(String name, double value)
    {
        try {
            super.addField(name, new Double(value));
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    public void addField(String name, boolean value)
    {
        try {
            super.addField(name, new Boolean(value));
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    
    
    public void addTemplateField(String name, String type)
    {
        try {
            super.addField(name, type, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
    }
    
    
    
    public String eventType()
    {
        try {
            return super.getEventType();
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    public Serializable value(String name)
    {
        try {
            return getPostValue(name);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    public String stringValue(String name)
    {
        try {
            return getPostValueString(name);
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return null;
    }
    
    public int intValue(String name)
    {
        try {
            return ((Integer)getPostValue(name)).intValue();
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return 0;
    }
    
    public long longValue(String name)
    {
        try {
            return ((Long)getPostValue(name)).longValue();
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return 0;
    }
    
    public float floatValue(String name)
    {
        try {
            return ((Float)getPostValue(name)).floatValue();
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return 0.0f;
    }
    
    public double doubleValue(String name)
    {
        try {
            return ((Double)getPostValue(name)).doubleValue();
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return 0.0;
    }
    
    public boolean booleanValue(String name)
    {
        try {
            return ((Boolean)getPostValue(name)).booleanValue();
        } catch (EventHeapException ehe) { System.out.println(ehe.getDetail().toString()); }
        return false;
    }
}
