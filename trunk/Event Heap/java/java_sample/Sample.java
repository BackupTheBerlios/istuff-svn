import iwork.eheap2.*;

class Sample implements EventCallback{
	public Sample(){
		try{
			EventHeap eh = new EventHeap("localhost");
			Event e = new Event("MyEventType");
			e.addField("AGE", new Integer(27));
			e.addField("NAME", "Tico Ballagas");
			Event templates[] = new Event[1];
			templates[0] = e;
			
			// register for a specific event template
			// this will only be matched when EventType = MyEventType and Age = 27 and Name = Tico Ballagas
			eh.registerForEvents(templates, this);
			
			// send an event - commented out for template demonstration
			// uncomment to see both templates match
			//eh.putEvent(e);
						
			Event template = new Event("MyEventType");
			template.addField("AGE", Integer.class, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
			template.addField("NAME", String.class, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
			
			// register for a generic event template
			// this template will be matched for any event that has EventType = MyEventType  
			// and contains the Age and Name fields with correct type
			// the values of Age and Name can be any value
			// (run the c tutorial app as a test, waitForEvent should print and registerForEvents should not)
			Event received = eh.waitForEvent(template);
			System.out.println("waitForEvent: " + received.getEventType());
			
			
		}catch(Exception e){
			e.printStackTrace();
		}
	
	}

	public boolean returnEvent(Event[] retEvents){
		try{
			System.out.println("registerForEvents: " + retEvents[0].getEventType());
		}catch(Exception e){
			e.printStackTrace();
		}
		return true;
	}

    public static void main( String argv[]){
		Sample s = new Sample();
    }
}
