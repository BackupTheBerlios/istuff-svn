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
 *			  		Tico Ballagas
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
		private Event template;

		private String comPort;
		private SerialPort serPort = null;
		private OutputStream outStream = null;
		private InputStream inStream = null;

		private byte[] buffer = new byte[512];


		public iStuffMobileProxy(String cmprt, String ip)
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
				ex.printStackTrace();
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
					inStream.close();
					serPort.close();
			}
			catch(Exception ex)
			{
					System.exit(1);
			}
		}

		// Callback from register for events
		public boolean returnEvent(Event[] retEvents){
			try
			{
				for(int i=0; i<retEvents.length; i++){
					System.out.println("Waiting for event");
					int command = ((Integer)retEvents[i].getPostValue("Command")).intValue();
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
							getPathAndRedirect(retEvents[i]);
							break;

						 case OPCODE_KEY_RECEIVED:
							sendKey(retEvents[i]);
							break;

						 case OPCODE_CHANGEPROFILE:
							sendChangeProfile(retEvents[i]);
							break;
					}
				}
			}
			catch(Exception ex)
			{
					System.out.println(ex.toString());
			}

			return true;
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

		public void sendChangeProfile(Event recEvent)
		{
			try
			{
				byte buffer[] = new byte[2];
				buffer[0] = ((Integer)recEvent.getPostValue("Command")).byteValue();
				buffer[1] = ((Integer)recEvent.getPostValue("ProfileNo")).byteValue();
				
				outStream.write(buffer);
			}
			catch(Exception ex)
			{
				System.out.println("RFCOM : "+ ex.toString());
			}
		}
		
		public static void main(String argv[])
		{
			iStuffMobileProxy mobileProxy;
			Shutdown killer;
			Stdio std;

			if(argv.length == 2)
			{
				mobileProxy = new iStuffMobileProxy(argv[0],argv[1]);

				killer = new Shutdown(mobileProxy);
				Runtime.getRuntime().addShutdownHook(killer);

				std = new Stdio(mobileProxy);
				std.start();

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

class Stdio extends Thread 
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
				mobileProxy.redirectEvent((new Integer(command)).intValue());
				System.out.println("sending event " + command);
			}
			catch (Exception e) 
			{
				e.printStackTrace();
			}
		}
	}
}