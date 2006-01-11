import iwork.eheap2.*;

class Test
{
	public static void main(String args[])
	{
		 try
		 {
		 	EventHeap eventHeap = new EventHeap("localhost");
		 	Event e = new Event("iStuffMobile");
		 	e.addField("Command",new Integer(2));
		 
		 	eventHeap.putEvent(e);
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}
	}

}