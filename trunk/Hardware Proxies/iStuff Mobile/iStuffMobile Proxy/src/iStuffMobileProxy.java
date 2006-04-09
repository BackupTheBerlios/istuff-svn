/*
 * Copyright (c) 2006
 * Media informatics Department
 * RWTH Aachen Germany
 * http://media.informatik.rwth-aachen.de
 *
 * Redistribution and use of the source code and binary, with or without
 * modification, are permitted under OPI Artistic License 
 * (http://www.opensource.org/licenses/artistic-license.php) provided that 
 * the source code retains the above copyright notice and the following 
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors:	  Faraz Ahmed Memon
 *			  Tico Ballagas
 *
 * Version:	  1.0
 */
 
import java.io.*;
import javax.comm.*;
import iwork.eheap2.*;


public class iStuffMobileProxy implements EventCallback
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
		private final int OPCODE_START_KEYCAPTURE = 10;
		private final int OPCODE_STOP_KEYCAPTURE = 11;
		private final int OPCODE_CHANGEPROFILE = 12;

		private final boolean DEBUG = true;
		private EventHeap eventHeap;
		private Event[] template;
		private String  proxyID;

		private String comPort;
		private SerialPort serPort = null;
		private OutputStream outStream = null;
		private InputStream inStream = null;

		private byte[] buffer = new byte[512];


		public iStuffMobileProxy(String ip, String proxyID, String cmprt)
		{
			try
			{
				eventHeap = new EventHeap(ip);
				template = new Event[1];
				template[0] = new Event("iStuffMobile");
				template[0].addField("Command", Integer.class, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);
				this.proxyID = proxyID;
				this.comPort = cmprt;
				initSerial();
				eventHeap.registerForEvents(template,this);
			}
			catch (Exception ex)
			{
				ex.printStackTrace();
				System.exit(-1);
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
					inStream.close();
					serPort.close();
					System.exit(0);
			}
			catch(Exception ex)
			{
					System.exit(-1);
			}
		}

		// Callback from register for events
		public boolean returnEvent(Event[] retEvents)
		{
			try
			{
				
				String currentProxyId = null;
				int command = ((Integer)retEvents[0].getPostValue("Command")).intValue();
				
				if(retEvents[0].fieldExists("ProxyID"))
					currentProxyId = retEvents[0].getPostValueString("ProxyID");
					
				if ((currentProxyId == null && proxyID.equals("")) || (proxyID.equals(currentProxyId)))
				{
						System.out.println("Received command = " + command);

						switch (command)
						{
							case OPCODE_DISCONNECT:
							case OPCODE_BACKLIGHT_ON:
							case OPCODE_BACKLIGHT_OFF:
							case OPCODE_STOPSOUND:
							case OPCODE_START_KEYCAPTURE:
							case OPCODE_STOP_KEYCAPTURE:
								redirectEvent(command);
								break;

							case OPCODE_PLAYSOUND:
							case OPCODE_LAUNCHAPP:
							case OPCODE_CLOSEAPP:
								getPathAndRedirect(retEvents[0]);
								break;

							case OPCODE_KEY_RECEIVED:
								sendKey(retEvents[0]);
								break;

							case OPCODE_CHANGEPROFILE:
								sendChangeProfile(retEvents[0]);
								break;
						}
				}
			}
			catch(Exception ex)
			{
					ex.printStackTrace();
			}

			System.out.println("Waiting for event");
			return true;
		}

		private void initSerial()throws Exception
		{
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(comPort);
			if (portId == null)
			{
				throw new NullPointerException("no com port identifier");
			}
		  serPort = (SerialPort)portId.open("iStuffMobile", 5000);
		  outStream = serPort.getOutputStream();
		  inStream = serPort.getInputStream();
		}

		public void read(InputStream in, byte[] buffer, int off, int len) throws IOException {
			int i;
			while (len > 0 && (i = in.read(buffer, off, len)) != -1) {
				off += i;
				len -= i;
			}
			if (len > 0) throw new IOException("read error");
		}

		public void run()
		{
				while(true)
				{
					try{
						read(inStream, buffer, 0, 1);

						switch (buffer[0]) {
							case OPCODE_KEY_PRESSED:
								if (DEBUG) System.out.println("OPCODE_KEY_RECIEVED");
								read(inStream, buffer, 0, 4);
								Event keyEvent = new Event("iStuffMobile");
								keyEvent.addField("ProxyID",proxyID);

								char keyCode = 0;
								keyCode |= buffer[0];
								keyCode <<= 8;
								keyCode |= buffer[1];

								char type = 0;
								type |= buffer[2];
								type <<= 8;
								type |= buffer[3];

								switch(type)
								{
									case 1:
										keyEvent.setPostValue("Activity", "KeyPress");
										keyEvent.setPostValue("KeyCode", new Integer(keyCode));
									break;
									case 2:
										keyEvent.setPostValue("Activity", "KeyUp");
									break;
									case 3:
										keyEvent.setPostValue("Activity", "KeyDown");
									break;

									default:
										System.out.println("Unrecognized Key Type");
								}
								if (eventHeap.isConnected()) 
									eventHeap.putEvent(keyEvent);
								break;
							default:
								System.out.println("unrecognized opcode " + new Integer(buffer[0]));
						}
					} catch( Exception ex ){
						ex.printStackTrace();
					}
				}
		}

		public void redirectEvent(int command)
		{
			try
			{
				byte buffer[] = new byte[1];
				buffer[0] = new Integer(command).byteValue();
				outStream.write(buffer);
			}
			catch(Exception ex)
			{
				ex.printStackTrace();
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
				ex.printStackTrace();
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
				ex.printStackTrace();
			}
		}

		public void sendChangeProfile(Event recEvent)
		{
			try
			{
				byte buffer[] = new byte[2];
				buffer[0] = ((Integer)recEvent.getPostValue("Command")).byteValue();
				
				if(recEvent.fieldExists("ProfileNo"))
				{
					buffer[1] = ((Integer)recEvent.getPostValue("ProfileNo")).byteValue();
					
					outStream.write(buffer);
				}
				else
					return;
			}
			catch(Exception ex)
			{
				ex.printStackTrace();
			}
		}
		
		public static void main(String argv[])
		{
			iStuffMobileProxy mobileProxy = null;
			Shutdown killer;
			
			if (argv.length >=2) { // At least two arguments are needed in order to start the proxy
				if(argv.length == 2)  // Only the neccessary parameters EventHeapName and COMPort were supplied. 
					mobileProxy = new iStuffMobileProxy(argv[0],"",argv[1]);
				else if (argv.length >= 3) // All parameters were supplied
					mobileProxy = new iStuffMobileProxy(argv[0], argv[1], argv[2]);
			
				killer = new Shutdown(mobileProxy);
				Runtime.getRuntime().addShutdownHook(killer);

				mobileProxy.run();
			}
			else
			{
				System.out.println("\nUsage: java MPProxy <Event Heap IP> <Comm Port> [ProxyID] \n" +
				"<Comm Port> = the serial port address for the phone e.g. /dev/tty.Nokia6600, COM3\n" +
				"[ProxyID] = an optional parameter to be checked in the events received and sent in events generated e.g. proxy1\n");
			}
		}
}

class Shutdown extends Thread {

		private iStuffMobileProxy mobileProxy;

		public Shutdown(iStuffMobileProxy mobile)
		{
			mobileProxy = mobile;
		}
		
		public void run() {
        System.out.println("Shutdown hook called");
        mobileProxy.Destroy();
    }
}


//for testing purpose

/*class Stdio extends Thread 
{

	private iStuffMobileProxy mobileProxy;

	public Stdio(iStuffMobileProxy mobile)
	{
		mobileProxy = mobile;
	}

	public void run()
	{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		while (true) 
		{
			try 
			{
				String command = in.readLine();
				if(command == null)
				{
						break;
				}
				else
				{
					mobileProxy.redirectEvent((new Integer(command)).intValue());
					System.out.println("sending event " + command);
				}
			}
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}
	}
}*/