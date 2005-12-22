import java.io.*;
import javax.comm.*;
import iwork.eheap2.*;

public class MPProxy
{
		private final static int OPCODE_DISCONNECT		= 1;
		private final static int OPCODE_BACKLIGHT_ON	=	2;
		private final static int OPCODE_BACKLIGHT_OFF	=	3;
		private final static int OPCODE_KEYPRESS = 4;
		private final static int OPCODE_PLAYSOUND = 5;
		private final static int OPCODE_STOPSOUND = 6;
		private final static int OPCODE_LAUNCHAPP = 7;
		private final static int OPCODE_CLOSEAPP = 8;
		
		private EventHeap eventHeap;
		private Event template;
		
		private String comPort;
		private SerialPort serPort = null;
		private OutputStream out = null;
    
		
		public MPProxy(String cmprt)
		{
			try 
			{
				eventHeap = new EventHeap("localhost");
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
		
		private void initSerial()throws Exception
		{
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(comPort);
			if (portId == null) 
			{
				throw new NullPointerException("no com port identifier");
			}
      serPort = (SerialPort)portId.open("MPToolkit", 5000);
      out = serPort.getOutputStream();
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
							 
							 case OPCODE_PLAYSOUND:
							 case OPCODE_LAUNCHAPP:
							 case OPCODE_CLOSEAPP:
							 	getPathAndRedirect(recEvent);
							 
							 case OPCODE_KEYPRESS:
							 	sendKey(recEvent);
						}
						
						Thread.sleep(100);
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
				out.write(buffer);
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
					out.write(buffer);
					out.write((byte)buffer1.length);
					out.write(buffer1);
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
					System.out.println("About to send over bluetooth");
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
					
					out.write(buffer);
					out.write(buffer1);
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
			
			if(argv.length == 1)
			{
				mobileProxy = new MPProxy(argv[0]);
				mobileProxy.run();
			}
			else
			{
			System.out.println("Usage: java MPProxy <Comm Port>\n" +
								"\t<Comm Port> = the serial port address for the phone examples: /dev/tty.Nokia6600, COM3\n");
			}
		}
}