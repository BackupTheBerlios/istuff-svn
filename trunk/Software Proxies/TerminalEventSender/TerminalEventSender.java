import iwork.eheap2.*;
import java.net.*;
import java.util.*;
import java.io.Serializable;

public class TerminalEventSender{
	private EventHeap mEventHeap;
	public String mMachineName;

	public TerminalEventSender(String[] args){
		try{
			String eventHeapName = args[0];
			String eventType = args[1];
			List fieldList = new ArrayList();
			for (int i=2;i<args.length; i++){
				fieldList.add(new FieldValuePair(args[i]) );				
			}
			send(eventHeapName, eventType, fieldList);
		}
		catch (ArrayIndexOutOfBoundsException aexp){
			printUsage();
		}
	}

	public void send(String iEventHeapName, String iEventType, List iFieldValueList){
		mEventHeap = new EventHeap(iEventHeapName);
		try{
			Event oEvent = new Event(iEventType);
			for (Iterator i=iFieldValueList.iterator(); i.hasNext();){
				FieldValuePair pair = (FieldValuePair)i.next();
				oEvent.setField(pair.mFieldName,  pair.mValue, FieldValueTypes.FORMAL);
			}
			mEventHeap.putEvent(oEvent);
		}
		catch (EventHeapException eexp){	
		}
	}

	//Integer Number > Float Number > String
	class FieldValuePair{
		String mFieldName;
		Serializable mValue;
		public FieldValuePair(String iStringToParse){
			//ffasd:asdda
			//ssasdsdf:
			//"ssdasda asdasd":
			String[] parts;
			if (iStringToParse.startsWith("\"")){
				parts = iStringToParse.split("\\\":");
			}
			else{
				parts = iStringToParse.split(":");
			}
			String iFieldName = parts[0].trim();
			if (iFieldName.startsWith("\"")){  //Strip off quotes
				iFieldName = iFieldName.substring(1,iFieldName.length()); 
			}
	
			String iValString = "";
			if (parts.length>0){
				iValString= parts[1].trim();
			}

					
			mFieldName = iFieldName;
			try{
				int intValue = Integer.parseInt(iValString.trim());
				mValue = new Integer(intValue);
			}
			catch (NumberFormatException niExp){
				try{
					float floatValue = Float.parseFloat(iValString.trim());
					mValue = new Float(floatValue);
				}
				catch (NumberFormatException nfExp){
					mValue = iValString;
				}//enf try float
			}//end try integer
		}
	}


     public static void main(String[] args)
     {
		TerminalEventSender s;
		
		if( args.length < 2 ){
			printUsage();
		}   
		else{
			s = new TerminalEventSender(args);
		}
     }


	public static void printUsage(){
		System.out.println("Usage: TerminalEventSender <event heap name> <event type> {<field name:value>}*");
		System.exit(-1);
	}


}
