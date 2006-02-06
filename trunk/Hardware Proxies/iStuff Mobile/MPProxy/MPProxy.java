import java.io.*;
import javax.comm.*;
import iwork.eheap2.*;


public class MPProxy
{
		private final int OPCODE_DISCONNECT		= 1;
		private final int OPCODE_BACKLIGHT_ON	=	2;
		private final int OPCODE_BACKLIGHT_OFF	=	3;
		private final int OPCODE_KEY_RECEIVED = 4;
		private final int OPCODE_PLAYSOUND = 5;
		private final int OPCODE_STOPSOUND = 6;
		private final int OPCODE_LAUNCHAPP = 7;
		private final int OPCODE_CLOSEAPP = 8;
		private final int OPCODE_KEY_PRESSED = 9;
		
		private EventHeap eventHeap;
		private Event template;
		
		private String comPort;
		private SerialPort serPort = null;
		private OutputStream outStream = null;
    
		
		public MPProxy(String cmprt, String ip)
		{
			try 
			{
				eventHeap = new EventHeap(ip);
				template = new Event("iStuffMobile");
				template.addField("Command", Integer.class, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
				this.comPort = cmprt;
				initSerial();
			} 
			catch (Exception ex) 
			{
				System.out.println(ex.toString());
				System.exit(1);
			}
		}
		
		public void Destroy()
		{
    	try
    	{
      	System.out.println("Cleaning up");
      	byte buffer[] = new byte[1];
				buffer[0] = new Integer(OPCODE_DISCONNECT).byteValue();
				outStream.write(buffer);
				outStream.close();
				serPort.close();
    	} 
    	catch(Exception ex)
    	{
        System.out.println(ex.toString());
    	}
		}
		
		private void initSerial()throws Exception
		{
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(comPort);
			if (portId == null) 
			{
				throw new NullPointerException("no com port identifier");
			}
      serPort = (SerialPort)portId.open("MPToolkit", 5000);
      outStream = serPort.getOutputStream();
		}
		
		public void run()
		{
				while(true)
				{
					try
					{
						System.out.println("Waiting for event");
						Event recEvent = eventHeap.waitForEvent(template);
						int command = ((Integer)recEvent.getPostValue("Command")).intValue();
						System.out.println("Received command = " + command);
						
						switch (command)
						{
							 case OPCODE_DISCONNECT:
							 case OPCODE_BACKLIGHT_ON:
							 case OPCODE_BACKLIGHT_OFF:
							 case OPCODE_STOPSOUND:
							 	redirectEvent(command);
							 	break;
							 
							 case OPCODE_PLAYSOUND:
							 case OPCODE_LAUNCHAPP:
							 case OPCODE_CLOSEAPP:
							 	getPathAndRedirect(recEvent);
							 	break;
							 
							 case OPCODE_KEY_RECEIVED:
							 	sendKey(recEvent);
							 	break;
						}
					}
					catch(Exception ex)
					{
							System.out.println(ex.toString());
					}
				}
		}
		
		private void redirectEvent(int command)
		{
			try
			{
				byte buffer[] = new byte[1];
				buffer[0] = new Integer(command).byteValue();
				outStream.write(buffer);
			}
			catch(Exception ex)
			{
				System.out.println("RFCOM : "+ ex.toString());
			}
		}
		
		private void getPathAndRedirect(Event recEvent)
		{
			try
			{
				Integer command = (Integer)recEvent.getPostValue("Command");
				byte buffer[] = new byte[1];
				buffer[0] = command.byteValue();
				
				if(recEvent.fieldExists("Path"))
				{
					String path = (String)recEvent.getPostValue("Path");
					path += "\0";
					
					byte buffer1[] = path.getBytes();
					outStream.write(buffer);
					outStream.write((byte)buffer1.length);
					outStream.write(buffer1);
				}
				else
					return;
			}
			catch(Exception ex)
			{
				System.out.println(ex.toString());
			}
		}
		
		private void sendKey(Event recEvent)
		{
			try
			{
				Integer command = (Integer)recEvent.getPostValue("Command");
				byte buffer[] = new byte[1];
				buffer[0] = command.byteValue();
				
				if(recEvent.fieldExists("Code") && recEvent.fieldExists("Repeat") && recEvent.fieldExists("ScanCode"))
				{
					int code = ((Integer)recEvent.getPostValue("Code")).intValue();
					int repeat = ((Integer)recEvent.getPostValue("Repeat")).intValue();
					int scancode = ((Integer)recEvent.getPostValue("ScanCode")).intValue();
					
					byte buffer1[] = new byte[6];
					
					buffer1[0] = 0;
					buffer1[0] |= (0xFF00 & repeat) >> 8;
					buffer1[1] = 0;
					buffer1[1] |= (0x00FF & repeat);
					
					buffer1[2] = 0;
					buffer1[2] |= (0xFF00 & scancode) >> 8;
					buffer1[3] = 0;
					buffer1[4] |= (0x00FF & scancode);
										
					buffer1[4] = 0;
					buffer1[4] |= (0xFF00 & code) >> 8;
					buffer1[5] = 0;
					buffer1[5] |= (0x00FF & code);
					
					outStream.write(buffer);
					outStream.write(buffer1);
				}
				else
					return;
			}
			catch(Exception ex)
			{
				System.out.println(ex.toString());
			}
		}
		
		public static void main(String argv[])
		{
			MPProxy mobileProxy;
			Shutdown killer;
			
			if(argv.length == 2)
			{
				mobileProxy = new MPProxy(argv[0],argv[1]);
				
				killer = new Shutdown(mobileProxy);
				Runtime.getRuntime().addShutdownHook(killer);
				
				mobileProxy.run();
			}
			else
			{
			System.out.println("Usage: java MPProxy <Comm Port> <Event Heap IP>\n" +
								"\t<Comm Port> = the serial port address for the phone examples: /dev/tty.Nokia6600, COM3\n");
			}
		}
}

class Shutdown extends Thread {
	
		private MPProxy mobileProxy;
		
		public Shutdown(MPProxy mobile)
		{
			mobileProxy = mobile;
		}
    public void run() {
        System.out.println("Shutdown hook called");
        mobileProxy.Destroy();
    }
}