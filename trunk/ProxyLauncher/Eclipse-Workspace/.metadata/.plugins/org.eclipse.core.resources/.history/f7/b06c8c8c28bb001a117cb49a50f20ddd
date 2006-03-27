
import java.io.*;
import java.util.*;
import javax.comm.*;
import java.nio.*;


interface RFIDListener {
    void callback(String rfid);
};

public class RFID implements Runnable, SerialPortEventListener, CommPortOwnershipListener {
    static CommPortIdentifier portId;
    static Enumeration portList;

    // debug flag
    boolean DEBUG = false;

    private final int RFID_TAG_SIZE = 36;
    private final int MAX_CHANNELS = 8;
    private final int RECONNECT_TIMEOUT = 5000;
	private final int MAGIC_COOKIE = 0x7e;
	
    InputStream inputStream;
    OutputStream outputStream;
    SerialPort serialPort;
    Thread readThread;
    String portName;
    private Vector clients = new Vector();
	BufferedReader in;
	private int bufSize;
	byte [] idBuf;
	int bufOffset = 0;
	char [] cbuf;
	boolean foundMagicCookie = false;
	
	public static void main(String[] args) {
        RFID bs;

        if( args.length > 0 )
            bs = new RFID(args[0]);
        else
            bs = new RFID();

        // activate the print statements
        bs.DEBUG = true;
		
     
        // route keyboard input to the RFID
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        while( true ){
            try{
                bs.getOutputStream().write( in.readLine().getBytes() );
            } catch (Exception e) { e.printStackTrace(); }
        }
    }

    public RFID() {
        //this( "COM3" );
        this("/dev/tty.usbserial0");
    }
	
    public RFID( String portName ){
			idBuf = new byte[RFID_TAG_SIZE];
			cbuf = new char[RFID_TAG_SIZE];
			this.portName = portName;
            openPort( portName );
    }

    public void openPort( String portName ){
		//while( connected == false ){
			portList = CommPortIdentifier.getPortIdentifiers();
    
			System.out.println("RFID: Establishing Connection to RFID");

			while (portList.hasMoreElements()) {
				portId = (CommPortIdentifier) portList.nextElement();
				if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
					System.out.println( portId.getName() );
					if(portId.getName().equals(portName)){
						System.out.println("RFID: Found serial port");
						portId.addPortOwnershipListener( this );
						connect();
						break;
					}
				}
			}
		//}
    }

   

    public void connect(){
		try {
			serialPort = (SerialPort) portId.open("RFID", RECONNECT_TIMEOUT);
	
			try {
				inputStream = serialPort.getInputStream();
				outputStream = serialPort.getOutputStream();
				in = new BufferedReader( new InputStreamReader(inputStream) );

				try {
					serialPort.addEventListener(this);
				} catch (TooManyListenersException e) { e.printStackTrace(); }

			} catch (IOException e) { e.printStackTrace(); }

			System.out.println("RFID: Registered for SerialEvents");
			serialPort.notifyOnDataAvailable(true);
			System.out.println("RFID: Waiting on SerialEvent");

			try {
				serialPort.setSerialPortParams(19200, SerialPort.DATABITS_8, 
											   SerialPort.STOPBITS_1, 
											   SerialPort.PARITY_NONE);
			} catch (UnsupportedCommOperationException e) {
				e.printStackTrace();
			}

			readThread = new Thread(this);

			readThread.start();
								
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("RFID: Could not establish connection to RFID");
			serialPort = null;
			System.exit(-1);
		}

	}


	public void ownershipChange( int type ){
		switch( type ){
		case PORT_OWNED:
			System.out.println("RFID: PORT_OWNED");
			break;
		case PORT_OWNERSHIP_REQUESTED:
			System.out.println("RFID: PORT_OWNERSHIP_REQUESTED");
			break;
		case PORT_UNOWNED:
			System.out.println("RFID: PORT_UNOWNED");
			break;
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
            System.out.println("RFID: Break interrupt");
            break;
        case SerialPortEvent.OE:
            System.out.println("RFID: Overrun error");
            break;
        case SerialPortEvent.FE:
            System.out.println("RFID: Framing error");
            break;
        case SerialPortEvent.PE:
            System.out.println("RFID: Parity error");
            break;
        case SerialPortEvent.CD:
            System.out.println("RFID: Carrier detect");
            break;
        case SerialPortEvent.CTS:
            System.out.println("RFID: Clear to send");
            break;
        case SerialPortEvent.DSR:
            System.out.println("RFID: Data set ready");
            break;
        case SerialPortEvent.RI:
            System.out.println("RFID: Ring indicator");
            break;
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
            System.out.println("RFID: Output Buffer Empty");
            break;
        case SerialPortEvent.DATA_AVAILABLE:
            try {			              
				while(in.ready()){
					int charsRead = in.read(cbuf, 0, RFID_TAG_SIZE);
					extractID(cbuf, charsRead);
				}
            } catch (IOException e) {}	
            break;
        }
    }
	
    public OutputStream getOutputStream(){
        return outputStream;
    }
	
	private void extractID(char cbuf[], int len){
		if(!foundMagicCookie){
			if(cbuf[0] == MAGIC_COOKIE){
				foundMagicCookie = true;
			} else {
				return;
			}
		}
		
		int numChars = RFID_TAG_SIZE - bufOffset;
		if( numChars > len ){
			numChars = len;
		}
		
		for(int i = 0; i < numChars ; i++){
			idBuf[bufOffset] = (byte)cbuf[i];
			bufOffset++;
		}
		
		if(bufOffset == RFID_TAG_SIZE){
			String hexID = byteArrayToHexString(idBuf);
			bufOffset = 0;
			if(DEBUG)
				System.out.println("RFID: " + hexID.trim());
			// the reader id is in the first 10 bytes (20 hex characters)
			notifyClients(hexID.trim().substring(20));
			// look for magic cookie again
			if( cbuf[numChars] == MAGIC_COOKIE){
				for(int i = 0; i < len - numChars; i++){
					idBuf[i] = (byte)cbuf[numChars + i];
					bufOffset++;
				}
			} else{
				foundMagicCookie = false;
			}	
		}
	}

	/**
	* Convert a byte[] array to readable string format. This makes the "hex" readable!
	* @return result String buffer in String format 
	* @param in byte[] buffer to convert to string format
	*/

	static String byteArrayToHexString(byte in[]) {
		byte ch = 0x00;
		int i = 0; 
		if (in == null || in.length <= 0)
			return null;
			
		String pseudo[] = {"0", "1", "2",
	"3", "4", "5", "6", "7", "8",
	"9", "A", "B", "C", "D", "E",
	"F"};
	
		StringBuffer out = new StringBuffer(in.length * 2);

		while (i < in.length) {
			ch = (byte) (in[i] & 0xF0); // Strip off high nibble
			ch = (byte) (ch >>> 4); // shift the bits down
			ch = (byte) (ch & 0x0F);    // must do this is high order bit is on!
			out.append(pseudo[ (int) ch]); // convert the nibble to a String Character
			ch = (byte) (in[i] & 0x0F); // Strip off low nibble 
			out.append(pseudo[ (int) ch]); // convert the nibble to a String Character
			i++;
		}
		String rslt = new String(out);
		return rslt;
	}    
	
	public void register(RFIDListener lt) {
        clients.add(lt);
    }
	
    public void notifyClients(String rfid) {
        Iterator it = clients.iterator();
        while (it.hasNext()) {
            RFIDListener lt = (RFIDListener) it.next();
            lt.callback(rfid);
        }
    }
}

