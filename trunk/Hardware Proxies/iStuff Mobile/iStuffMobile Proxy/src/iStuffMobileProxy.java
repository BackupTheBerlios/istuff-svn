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

//!  "iStuffMobile" proxy program to communicate with the "Event Heap".
/*!  The "iStuff Mobile" proxy Class which communicates with the "Event Heap".
  	 The two main functionalities of this class are:
  		-# Receive events of type iStuffMobile from the "Event Heap" and send
  	   	   appropriate commands to the "iStuff Mobile" mobile phone application.
  		-# Receive Key Press events from the "iStuff Mobile" mobile phone application
  		   and post corresponding key events on the "Event Heap".
*/

public class iStuffMobileProxy implements EventCallback
{

		/** @name Opcodes
		 *  High-level opcodes that could be sent (or received) to (or from)
    		"iStuff Mobile" mobile phone application.
 		*/

		//@{

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

		//@}


		private final boolean DEBUG = true;
		private EventHeap eventHeap;
		private Event[] template;
		private String  proxyID;

		private String comPort;
		private SerialPort serPort = null;
		private OutputStream outStream = null;
		private InputStream inStream = null;

		private byte[] buffer = new byte[512];

		//! iStuffMobile class constructor
    	/*! The constructor take "Event Heap" IP address, the current
      		proxy Id and a COM port name as an inputs.

      		\param ip as a String. Specifies the IP address of the "Event Heap".
      		\param proxyID as a String. Specifies the proxy ID to be used while
      			   posting Events and to be checked while receiving events.
      		\param cmprt as a String. Specifies the COM Port name.
    	*/

		public iStuffMobileProxy(String ip, String proxyID, String cmprt)
		{
			try
			{
				eventHeap = new EventHeap(ip);
				template = new Event[1];
				template[0] = new Event("iStuffMobile");		//the Events to be fetched should be of type iStuffMobile
				template[0].addField("Command", Integer.class, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);	//the events to be fetched should have a field Command of an Integer value type
				this.proxyID = proxyID;
				this.comPort = cmprt;
				initSerial();
				eventHeap.registerForEvents(template,this);	//register to receive events of type template
			}
			catch (Exception ex)
			{
				ex.printStackTrace();
				System.exit(-1);
			}
		}

		//! Disconnects the proxy
    	/*! This method is called when Ctrl + C is hit on the keyboard.
        	It sends a Disconnect command to the "iStuff Mobile"
      		mobile phone application, closes I/O streams and exits the
      		Proxy.
    	*/

		public void Destroy()
		{
			try
			{
					System.out.println("Cleaning up");

					byte buffer[] = new byte[1];
					buffer[0] = new Integer(OPCODE_DISCONNECT).byteValue();
					outStream.write(buffer);	//send disconnect command to "iStuff Mobile" mobile phone application
					outStream.close();
					inStream.close();
					serPort.close();
					System.exit(0);	//exit normally
			}
			catch(Exception ex)
			{
					System.exit(-1); //abmornal termination in case of an exception
			}
		}

		//! Callback Method from the "Event Heap"
		/*! This method is called whenever an event matching the template
			is found on the event heap. This function decodes the events
			of type "iStuffMobile" and issues corresponding high-level
			commands to the "iStuff Mobile" mobile phone application.

			\param retEvents as an Event array. The first element of the
				   array is the matching event. Subsequent events in
				   the array are the template events used for the match.

			\return The function should return true if it wants to
					continue recieving callbacks, and false if it is
					done and doesn't want to recieve any more callbacks.
		*/

		public boolean returnEvent(Event[] retEvents)
		{
			try
			{

				String currentProxyId = null;
				int command = ((Integer)retEvents[0].getPostValue("Command")).intValue();	// get the value of Command field from the Event

				if(retEvents[0].fieldExists("ProxyID"))
					currentProxyId = retEvents[0].getPostValueString("ProxyID");	//extract the ProxyID field value if it exists in the received event

				if (proxyID.equals("") || proxyID.equals(currentProxyId))
				{

					/*send high-level commands to the mobile phone if:
					  1. no proxyID field was found in the received event and no proxyID was passed as command line argument

					  OR

					  2.the proxyID field found in the current event is equal to the proxyID passed as command line argument
					  to this program */

						System.out.println("Received command = " + command);

						switch (command)
						{
							case OPCODE_DISCONNECT:
							case OPCODE_BACKLIGHT_ON:
							case OPCODE_BACKLIGHT_OFF:
							case OPCODE_STOPSOUND:
							case OPCODE_START_KEYCAPTURE:
							case OPCODE_STOP_KEYCAPTURE:	//same method call for all these cases because these opcodes can be directly
								redirectEvent(command);		//relayed to the "iStuff Mobile" mobile phone application without any extra
								break;						//parameters

							case OPCODE_PLAYSOUND:
							case OPCODE_LAUNCHAPP:
							case OPCODE_CLOSEAPP:
								getPathAndRedirect(retEvents[0]); //all these opcodes require a PATH to be sent following the opcode
								break;

							case OPCODE_KEY_RECEIVED:		//invoked when a Key Event is received from the "Event Heap"
								sendKey(retEvents[0]);
								break;

							case OPCODE_CHANGEPROFILE:		//invoked when an event with Profile Change opcode is received
								sendChangeProfile(retEvents[0]);
								break;
						}
				} else{
					System.out.println("Received command but ProxyID: " + currentProxyId + " did not match ProxyID: " + proxyID);
				}
			}
			catch(Exception ex)
			{
					ex.printStackTrace();
			}

			System.out.println("Waiting for event");
			return true;
		}

		//! Initializes the serial ports
    	/*! This method initializes the input and output stream member
    		variables. It throws an exception if the COM port identifier
    		is not found.
    	*/

		private void initSerial()throws Exception
		{
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(comPort);		//get the port ID for the port name received through command line
			if (portId == null)
			{
				throw new NullPointerException("no com port identifier");
			}
		  serPort = (SerialPort)portId.open("iStuffMobile", 5000);	//open the serial Port
		  outStream = serPort.getOutputStream();					//get output stream to the serial port
		  inStream = serPort.getInputStream();						//get input stram to the serial port
		}

		//! Reads data from input stream
    	/*! This method reads data from the given input stream(in) into
    		the provided buffer(buffer) starting from an offset index(off). Number of
    		bytes to be read are specified by length(len).

      		\param[in]  in as an InputStream object. Data is read from this input stream.
      		\param[out] buffer as a Byte array. The read data is copied to this buffer as
      					bytes.
      		\param[in]  off as an Integer. Specifies the offset index from which writing
      					into the buffer should start.
      		\param[in]  len as an Integer. Specifies the number of bytes to be read from
      					the given input stream.
    	*/

		public void read(InputStream in, byte[] buffer, int off, int len) throws IOException {
			int i;
			while (len > 0 && (i = in.read(buffer, off, len)) != -1) {
				off += i;
				len -= i;
			}
			if (len > 0) throw new IOException("read error");
		}

		//! Receives key codes from the "iStuff Mobile" mobile phone application
		/*! This method runs all the time and listens to key codes from the
			"iStuff Mobile" mobile phone application and posts corresponding key
			events onto the "Event Heap".
		*/

		public void run()
		{
				while(true)
				{
					try{
						read(inStream, buffer, 0, 1);			//read the opcode received by the "iStuff Mobile" mobile phone application

						switch (buffer[0]) {
							case OPCODE_KEY_PRESSED:
								if (DEBUG) System.out.println("OPCODE_KEY_RECIEVED");
								read(inStream, buffer, 0, 4);	//if the opcode is OPCODE_KEY_PRESSED, 4 bytes will follow.
																//2 bytes denoting the keycode and 2 bytes denoting the keytype

								Event keyEvent = new Event("iStuffMobile");
								keyEvent.addField("ProxyID",proxyID);		//create a new event

								char keyCode = 0;
								keyCode |= buffer[0];		//fill the keycode from two bytes into a char
								keyCode <<= 8;
								keyCode |= buffer[1];

								char type = 0;
								type |= buffer[2];			//fill the keytype from two bytes into a char
								type <<= 8;
								type |= buffer[3];

								switch(type)
								{
									case 1:					// type 1 denotes key was pressed
										keyEvent.setPostValue("Activity", "KeyPress");
										keyEvent.setPostValue("KeyCode", new Integer(keyCode));
									break;
									case 2:					// type 2 denotes key was released
										keyEvent.setPostValue("Activity", "KeyUp");
									break;
									case 3:					// type 3 denoted key was hit
										keyEvent.setPostValue("Activity", "KeyDown");
									break;

									default:
										System.out.println("Unrecognized Key Type");
								}
								if (eventHeap.isConnected())
									eventHeap.putEvent(keyEvent);		//post the received key press from the "iStuff Mobile" mobile
								break;									//phone application to the "Event Heap"
							default:
								System.out.println("unrecognized opcode " + new Integer(buffer[0]));
						}
					} catch( Exception ex ){
						ex.printStackTrace();
					}
				}
		}


		//! Sends high-level commands to the "iStuff Mobile" mobile phone application
		/*! This method sends an int command to the "iStuff Mobile" mobile phone
			application. This method is called from \e public <b>boolean returnEvent(Event[]
			retEvents)</b> inside this class.

			\param command as an Ingeter. Specifies the opcode to be sent to the
				   mobile phone application.
		*/

		private void redirectEvent(int command)
		{
			try
			{
				byte buffer[] = new byte[1];
				buffer[0] = new Integer(command).byteValue();
				outStream.write(buffer);	//send the command received to the "iStuff Mobile" mobile phone application
			}
			catch(Exception ex)
			{
				ex.printStackTrace();
			}
		}

		//! Sends high-level commands to the "iStuff Mobile" mobile phone application
		/*! This method extracts the "Command" and "Path" fields from the Event passed
			as parameter and issue a corresponding high-level command to the "iStuff
			Mobile" mobile phone application along with the path. This method is called
			from <b>public boolean returnEvent(Event[] retEvents)</b> inside this class
			for	high-level commands that require a path field.

			\param recEvent as an Event Object. Specifies an Event containing "Command"
				   and "Path" fields.
		*/

		private void getPathAndRedirect(Event recEvent)
		{
			try
			{
				Integer command = (Integer)recEvent.getPostValue("Command");	//extract the Command field from the received Event
				byte buffer[] = new byte[1];
				buffer[0] = command.byteValue();	//convert the command to byte

				if(recEvent.fieldExists("Path"))	//check if Path field exists in the event because it is required to follow
													//the command when sending opcodes to the "iStuff Mobile" mobile phone application
				{
					String path = (String)recEvent.getPostValue("Path"); //extract the Path field from the event
					path += "\0";	//a \0 is added expilicitly because the getBytes() method of String doesnot return 0
									//as a last byte which denotes the end of string

					byte buffer1[] = path.getBytes();
					outStream.write(buffer);		//send the opcode to the "iStuff Mobile" mobile phone application
					outStream.write((byte)buffer1.length);	//send the length of the path
					outStream.write(buffer1);		//sned the path itself
				}
				else
					return;
			}
			catch(Exception ex)
			{
				ex.printStackTrace();
			}
		}

		//! Sends a key press simulation command to the "iStuff Mobile" mobile phone application
		/*! This method extracts the "Command", "Code", "ScanCode", and "Repead" fields
			from the Event passed as parameter and issue a Key Press simulation command
			to the "iStuff Mobile" mobile phone application. This method is called
			from <b>public boolean returnEvent(Event[] retEvents)</b> inside this class for
			opcode OPCODE_KEY_RECEIVED.

			\param recEvent as an Event Object. Specifies an Event containing "Command"
				   "Code", "ScanCode" and "Repeat" fields.
		*/

		private void sendKey(Event recEvent)
		{
			try
			{
				Integer command = (Integer)recEvent.getPostValue("Command");
				byte buffer[] = new byte[1];
				buffer[0] = command.byteValue();

				if(recEvent.fieldExists("Code") && recEvent.fieldExists("Repeat") && recEvent.fieldExists("ScanCode"))
				{	//check if the received event contains Code, Repeat and ScanCode fields because they are required
					//to send a key press high-level command to the "iStuff Mobile" mobile phone application

					int code = ((Integer)recEvent.getPostValue("Code")).intValue();			//extract Code, Repeat and ScanCode fields
					int repeat = ((Integer)recEvent.getPostValue("Repeat")).intValue();
					int scancode = ((Integer)recEvent.getPostValue("ScanCode")).intValue();

					byte buffer1[] = new byte[6];

					//coversion of Code, Repeat and ScanCode fields from integer to 2 bytes

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

					outStream.write(buffer);  //send the OPCODE_KEY_RECEIVED to the "iStuff Mobile" mobile phone application
					outStream.write(buffer1); //send the Code, Repeat and ScanCode fields
											  //Note: These 3 fields are required to simulate a Key Press on the foreground
											  //application in the mobile phone
				}
				else
					return;
			}
			catch(Exception ex)
			{
				ex.printStackTrace();
			}
		}

		//! Sends a profile change command to the "iStuff Mobile" mobile phone application
		/*! This method extracts the "Command" and "ProfileNo" fields from the Event
			passed as parameter and issue a profile change command to the "iStuff
			Mobile" mobile phone application along with the profile number. This method
			is called from <b>public boolean returnEvent(Event[] retEvents)</b> inside this
			class for opcode OPCODE_CHANGEPROFILE.

			\param recEvent as an Event Object. Specifies an Event containing "Command"
				   and "ProfileNo" fields.
		*/

		private void sendChangeProfile(Event recEvent)
		{
			try
			{
				byte buffer[] = new byte[2];
				buffer[0] = ((Integer)recEvent.getPostValue("Command")).byteValue();

				if(recEvent.fieldExists("ProfileNo"))			//check if the ProfileNo field exists in the received event
																//bacause it is required to follow the OPCODE_CHANGEPROFILE
				{
					buffer[1] = ((Integer)recEvent.getPostValue("ProfileNo")).byteValue();
					outStream.write(buffer); //send the opcode followed by the ProfileNo to change a profile on the mobile phone
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

//!  A shutdown hook for "iStuff Mobile" proxy program.
/*!  The Shutdown class is a shutdown hook for "iStuff Mobile" proxy
	 program.
*/


class Shutdown extends Thread {

		private iStuffMobileProxy mobileProxy;

		//!  Shutdown class constructor.
		/*!  The Shutdown class constructor takes iStuffMobileProxy reference
			 and saves the reference to a local member variable.

			 \param mobile as an iStuffMobile object.
		*/

		public Shutdown(iStuffMobileProxy mobile)
		{
			mobileProxy = mobile;
		}

		//!  The overriden run method of the Thread class
		/*!  This method simply calls the Destroy method of the iStuffMobileProxy
			 class.
		*/

		public void run() {
        System.out.println("Shutdown hook called");
        mobileProxy.Destroy();
		System.exit(0);
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