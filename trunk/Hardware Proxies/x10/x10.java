/*
 * @(#)SimpleRead.java	1.12 98/06/25 SMI
 *
 * Copyright (c) 1998 Sun Microsystems, Inc. All Rights Reserved.
 *
 * Sun grants you ("Licensee") a non-exclusive, royalty free, license 
 * to use, modify and redistribute this software in source and binary
 * code form, provided that i) this copyright notice and license appear
 * on all copies of the software; and ii) Licensee does not utilize the
 * software in a manner which is disparaging to Sun.
 *
 * This software is provided "AS IS," without a warranty of any kind.
 * ALL EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES,
 * INCLUDING ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN AND
 * ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THE
 * SOFTWARE OR ITS DERIVATIVES. IN NO EVENT WILL SUN OR ITS LICENSORS
 * BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR FOR DIRECT,
 * INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE DAMAGES,
 * HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, ARISING
 * OUT OF THE USE OF OR INABILITY TO USE SOFTWARE, EVEN IF SUN HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * This software is not designed or intended for use in on-line control
 * of aircraft, air traffic, aircraft navigation or aircraft
 * communications; or in the design, construction, operation or
 * maintenance of any nuclear facility. Licensee represents and
 * warrants that it will not use or redistribute the Software for such
 * purposes.
 */

import java.io.*;
import java.util.*;
import javax.comm.*;
import iwork.eheap2.*;

public class x10 implements Runnable, SerialPortEventListener {
    static CommPortIdentifier portId;
    static Enumeration portList;

    final static byte POWERFAIL_POLL=(byte)165;
    final static byte TIMER_DOWNLOAD_HDR=(byte)155;
    final static byte POLL=(byte)90;
    final static byte PC_READY=(byte)195;

    InputStream inputStream;
    OutputStream outputStream;
    SerialPort serialPort;
    Thread readThread;
    EventHeap eHeap;

	int housecode = -1, 
		address = -1, 
		function;

    public static void main(String[] args) {
        System.out.print("Entering SimpleRead\n");
        portList = CommPortIdentifier.getPortIdentifiers();
	if( portList == null || portList.hasMoreElements()==false){
		System.out.println("No comm ports found!");
		System.out.println("Ensure javax.comm is installed properly");
		System.exit(-1);
	}

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();    
		System.out.println(portId.getName()+"\n");
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
		boolean portExist;
		if( args.length > 0 )
                	portExist = portId.getName().equals(args[0]);
		else
			portExist = portId.getName().equals("COM2");
	                //portId.getName().equals("/dev/term/a");
		
		if(portExist){
                    x10 reader = new x10(args);
                    System.out.print("Found serial port\n");
                }
		else
		    System.out.println("Could not find serial port");
            }
        }
        System.out.print("Exiting SimpleRead, helper thread should be waiting on serial input\n");
    }

    public x10() {        
        try {
            serialPort = (SerialPort) portId.open("SimpleReadApp", 2000);
        } catch (PortInUseException e) {}
        try {
            inputStream = serialPort.getInputStream();
        } catch (IOException e) {}
        try {
            outputStream = serialPort.getOutputStream();
        } catch (IOException e) {}
	try {
            serialPort.addEventListener(this);
	} catch (TooManyListenersException e) {}
        serialPort.notifyOnDataAvailable(true);
        try {
            serialPort.setSerialPortParams(4800,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);
        } catch (UnsupportedCommOperationException e) {}
        System.out.print("Succesfully opened serial port at 4800bps\n");

        readThread = new Thread(this);
        readThread.start();
    }

    public x10( String[] args ){
	this();
	// if no event heap is specified on command line, default to the iRoom event heap
        if( args.length <= 1 )
		eHeap = new EventHeap( "iw-room2" );
	else 
		eHeap = new EventHeap( args[1] );    
    }

    public void Decode(byte[] readBuffer, int numBytes) {
        for( int i=0; i < numBytes; i++ ){
            switch( readBuffer[i] ){
            case POWERFAIL_POLL:
            {
                byte[] bufMsg = new byte[8];
                bufMsg[0] = TIMER_DOWNLOAD_HDR; // Timer download header
                /* for now leave time info set to 0 */
                try {
                    outputStream.write(bufMsg);
                } catch (IOException e) {}
                System.out.print("powerfail poll received, reseting time\n");
                break;
            }
            case POLL:
            {
                System.out.print("received poll\n");
                byte[] bufMsg = new byte[1];
                bufMsg[0] = PC_READY; 
                try {
                     outputStream.write(bufMsg);
                } catch (IOException e) {}
                break;
            }
        }
        }        
    }

    public void PostEvent(int buttonNum) {
    	try {
    		EventHeap eh = new EventHeap("iw-room2");
    		iwork.eheap2.Event testEvent = new iwork.eheap2.Event("ButtonEvent");
    		iwork.eheap2.Event mbEvent = new iwork.eheap2.Event("1345");  // deprecated: multibrowse events have type "1345"

    		testEvent.addField("ButtonID", Integer.toString(buttonNum));
		mbEvent.addField("RunMode", "SHOW_MAXIMIZED");
		mbEvent.addField("Target", "3"); // post event to the control panel
		mbEvent.addField("CommandToExecute", "http://www.google.com");    	

    		testEvent.setTimeToLive(20000);
		mbEvent.setTimeToLive(5000);

		eh.putEvent(testEvent);
		eh.putEvent(mbEvent);
   		System.out.println("Placed event.");
      } catch (Exception e) {
		e.printStackTrace();
	}
    }

    public void run() {
        try {
            Thread.sleep(20000);
        } catch (InterruptedException e) {}
    }

    public void serialEvent(SerialPortEvent event) {
        switch(event.getEventType()) {
        case SerialPortEvent.BI:
        case SerialPortEvent.OE:
        case SerialPortEvent.FE:
        case SerialPortEvent.PE:
        case SerialPortEvent.CD:
        case SerialPortEvent.CTS:
        case SerialPortEvent.DSR:
        case SerialPortEvent.RI:
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
            break;
        case SerialPortEvent.DATA_AVAILABLE:
            byte[] readBuffer = new byte[20];
            String bufString = new String(";");
            int numBytes = 0;
		int functionMask, reportedBytes;
            
            try {
                while (inputStream.available() > 0) {
                    numBytes = inputStream.read(readBuffer);
                    for( int i = 0; i < numBytes; i++ ){
                        Byte readByte = new Byte(readBuffer[i]);
                        bufString = bufString.concat(Byte.toString(readBuffer[i]));
                        bufString = bufString.concat(";");
                    }
                    bufString = bufString.concat("\n");
                    Decode(readBuffer, numBytes);
                }
		    System.out.print("received data " + Integer.toString(numBytes) + " " + bufString);                		    
		    
		    // first byte indicates how long the buffer is
		    // the second byte tells number of address bytes vs. function bytes
		    // we can uniquely define each button by combining the function and address bytes
                reportedBytes = readBuffer[0];
		    if( reportedBytes != numBytes-1 )
                    Decode(readBuffer, numBytes);
		    else{		    
			    // functions are indicated with a high bit, addresses are indicated with low
			    functionMask = readBuffer[1];

			    iwork.eheap2.Event newEvent;

		
			    for( int i = 2; i<=reportedBytes; i++)
			    {
					if((functionMask & 0x01) != 0){
						// this is a function
						// the lower nibble is the function
						function = readBuffer[i] & 0x0F;
						// the upper nibble is a housecode, verify that it matches address' housecode
						if( housecode == (readBuffer[i] >> 4)){
							newEvent = new iwork.eheap2.Event("iStuffInputEvent");
							newEvent.addField("Device", "Button");
							newEvent.addField("ID", housecode + "-" + address + "-" + function + "-x10" );
							newEvent.addField("Housecode", new Integer(housecode) );;
							newEvent.addField("Address", new Integer(address));
							newEvent.addField("Function", new Integer(function));
							eHeap.putEvent(newEvent);
							System.out.println( "Posted new iStuffInputEvent, ID=" + newEvent.getPostValueString("ID") );
							//System.out.println( newEvent.toString() );
						}
						else {
							System.out.println("Function = " + function);
							System.out.println("Housecode = " + housecode);
							System.out.println("Housecode = " + (readBuffer[i]>> 4));
							System.out.println("ERROR: x10 function and address do not match");
						}
					}
					else {
						// this is an address
						// the lower nibble is the address
						address = readBuffer[i] & 0x0F;
						// the upper nibble is the housecode
						housecode = readBuffer[i] >> 4;
						System.out.println("Address = " + address);
						System.out.println("Housecode = " + housecode);
					}
				
					// Shift down the function mask for the next byte
					functionMask = functionMask >> 1;
			    }
			}
            } catch (Exception e) { e.printStackTrace();}
            break;
        }
    }   
    
   
}
