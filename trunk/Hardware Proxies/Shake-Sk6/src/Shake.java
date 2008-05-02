//
//  Shake.java
//  
//
//  Created by Tico Ballagas on 4/24/08.
//


import java.io.*;
import javax.comm.*;
import iwork.eheap2.*;

public class Shake implements EventCallback, Runnable
{

		/** @name Opcodes
		 *  High-level opcodes that could be sent (or received) to (or from)
    		"iStuff Mobile" mobile phone application.
 		*/

		//@{

		public final String REG_POWER_CONTROL = "0000";
		public final int PCC_CAPACITIVE_SENSING		= 0x01;
		public final int PCC_ACCELEROMETER			= 0x02;
		public final int PCC_ANGULAR_RATE_SENSOR	= 0x04;
		public final int PCC_VIBE					= 0x08;
		public final int PCC_MAGNETOMETER			= 0x10;
		public final int PCC_TEMPERATURE			= 0x20;
		public final int PCC_ANALOG_IN				= 0x40;
		public final int PCC_NAVIGATION_SWITCH		= 0x80;	
		
		public final String REG_POWER_CONTROL_2 = "0001";
		public final int CS0_INC_TRIG_VIBE			= 0x01;
		public final int CS0_DEC_TRIG_VIBE			= 0x02;
		public final int CS1_INC_TRIG_VIBE			= 0x04;
		public final int CS1_DEC_TRIG_VIBE			= 0x08;
		public final int DATA_OUT_PACK_EN			= 0x10;

		public final String REG_DATA_OUTPUT_FORMAT = "0002";
		public final int DATA_CHECKSUM			= 0x01;
		public final int DATA_FORMAT_ASCII		= 0x00;
		public final int DATA_FORMAT_RAW			= 0x02;
		
		public final String REG_ACC_CONF = "0004";
		public final int ACCEL_MEASUREMENT_RANGE_2G = 0x00;
		public final int ACCEL_MEASUREMENT_RANGE_6G = 0x01;
		public final int HIGH_PASS_FILTER			= 0x02;
		
		// ODR = output data rate
		public final String REG_ACCELOROMETER_ODR = "0008";
		public final String REG_ANGULAR_RATE_SENSOR_ODR = "0009";
		public final String REG_MAGNETOMETER_ODR = "000A";
		public final String REG_COMPASS_HEADING_ODR = "000B";
		public final String REG_CAPACITIVE_SENSOR_CH0_ODR = "000C";
		public final String REG_CAPACITIVE_SENSOR_CH1_ODR = "000D";
		public final String REG_ANALOG_IN_CH0 = "000E";
		public final String REG_ANALOG_IN_CH1 = "000F";
		
		public final String REG_DATA_REQUEST = "0100";
		public final int ACCELEROMETER				= 0x01;
		public final int ANGULAR_RATE				= 0x02;
		public final int MAGNETOMETER				= 0x04;
		public final int COMPASS_HEADING			= 0x08;
		public final int CAPACITIVE_SENSOR_CH0		= 0x10;
		public final int CAPACITIVE_SENSOR_CH1		= 0x20;
		public final int ANALOG_IN_CH0				= 0x40;
		public final int ANALOG_IN_CH1				= 0x80;
						
		private final boolean DEBUG = true;
		private EventHeap eventHeap;
		private Event[] template;
		private String  proxyID;
		private boolean running = true;

		private String comPort;
		private SerialPort serPort = null;
		private OutputStream outStream = null;
		private InputStream inStream = null;
		private BufferedReader inBufReader = null;

		public Shake(String ip, String proxyID, String cmprt)
		{
			try
			{
				eventHeap = new EventHeap(ip);
				template = new Event[1];
				template[0] = new Event("Shake");		//the Events to be fetched should be of type Shake
				template[0].addField("Command", String.class, FieldValueTypes.FORMAL, FieldValueTypes.FORMAL);	//the events to be fetched should have a field Command of an Integer value type
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
		  serPort = (SerialPort)portId.open("Shake", 5000);	//open the serial Port
		  outStream = serPort.getOutputStream();					//get output stream to the serial port
		  inStream = serPort.getInputStream();						//get input stram to the serial port
		  inBufReader = new BufferedReader(new InputStreamReader(inStream));		  
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
				String command = retEvents[0].getPostValueString("Command");	// get the value of Command field from the Event
				System.out.println("Received " + command);
			}
			catch(Exception ex)
			{
					ex.printStackTrace();
			}

			System.out.println("Waiting for event");
			return true;
		}

		//! Receives key codes from the Shake SK6 Sensor module
		/*! This method runs all the time and listens to data from the SK6 and posts the data through 
			events to the event heap
		*/
		public void run()
		{
				String data;
				String[] tokens;
				Integer value;
				Event e;
				
				System.out.println("Bluetooth thread, waiting for data");
				while(running == true)
				{
					try{
						if(inBufReader.ready()){
							data = inBufReader.readLine();
							tokens = data.split(",");
							e = new Event("Shake");
							e.addField("ProxyID", proxyID);
							e.setPostValue("TimeToLive", new Integer(50)); // set time to live to 50 msec
							e.setPostValue("Sensor",tokens[0]);
							for(int i = 1; i < tokens.length; i++){
								if(tokens[i].startsWith("+")){ // eliminate Number format exception
									value = new Integer(tokens[i].substring(1));
								}else{
									value = new Integer(tokens[i]);
								}
								e.setPostValue("Data"+i,value);
							}
							eventHeap.putEvent(e);
						}
					} catch(Exception ex){
						ex.printStackTrace();
					}
				}
				System.out.println("out of run");
		}
		
		public static void main(String[] argv){
			Shake myShake = null;

			if (argv.length >=2) { // At least two arguments are needed in order to start the proxy
				if(argv.length == 2)  // Only the neccessary parameters EventHeapName and COMPort were supplied.
					myShake = new Shake(argv[0],"",argv[1]);
				else if (argv.length >= 3) // All parameters were supplied
					myShake = new Shake(argv[0], argv[2], argv[1]);

				myShake.run();
			}
			else
			{
				System.out.println("\nUsage: java Shake <Event Heap IP> <Comm Port> [ProxyID] \n" +
				"<Comm Port> = the serial port address for the phone e.g. /dev/tty.Nokia6600, COM3\n" +
				"[ProxyID] = an optional parameter to be checked in the events received and sent in events generated e.g. proxy1\n");
			}
		
		}
}
