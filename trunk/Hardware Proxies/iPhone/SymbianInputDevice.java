/**
 * $Id: SymbianInputDevice.java,v 1.3 2004/06/30 12:47:55 rohs Exp $
 *
 *  Name     : SymbianInputDevice
 *  Part of  : VisualCodesDemo
 *  Created  : 29.06.2004 by Michael Rohs
 *  Copyright: (c) 2004 ETH Zurich
 **/

import javax.vecmath.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Arrays;
import javax.media.j3d.*;

import javax.comm.*;

interface SymbianInputListener {
    void translationCallback(int dX, int dY);
	void rotationCallback(int angle);
	void clickCallback();
	void codeCallback(String code, int targetX, int targetY);
};

public class SymbianInputDevice{
	private final static boolean DEBUG = false;

	private final static int OPCODE_DISCONNECT = 1;
	private final static int OPCODE_MOTION_ACTIVE = 2;
	private final static int OPCODE_MOTION_STOP = 3;
	private final static int OPCODE_SEND_CODES = 4;

	private String comPort;
	private int currentMenuId = 0;
	private SymbianInputListener listener;

	public SymbianInputDevice(String comPort, SymbianInputListener listener) {
		this.comPort = comPort;
		this.listener = listener;
		try {
			initSerial();
		} catch (Exception ex) {
			System.out.println("RFCOMM error: " + ex.toString());
			System.exit(1);
		}
	}

    private SerialPort serPort = null;
	private InputStream in = null;
	private OutputStream out = null;
	private byte[] buffer = new byte[1024];
	private boolean showFrame = false;

    protected void initSerial() throws Exception {
        CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(comPort);
		if (portId == null) {
			throw new NullPointerException("no com port identifier");
		}
        serPort = (SerialPort)portId.open("iPhone", 5000);
        out = serPort.getOutputStream();
        in = serPort.getInputStream();
    }

	public static int INCOMING_CODE_NUM_BYTES = 11;
	public class IncomingCode {
		public String code = "0x";
		public int targetX;
		public int targetY;
		public int tlX, tlY, trX, trY, blX, blY, brX, brY;
	}

	public void pollAndProcessInput() {

		int x = 0, y = 0, angle = 0, minDiff = 0, minDiffRotation = 0;

		try {

			// read opcode
			read(in, buffer, 0, 1);

			switch (buffer[0]) {
				case OPCODE_DISCONNECT:
					if(DEBUG)
						System.out.println("OPCODE_DISCONNECT");
					break;

				case OPCODE_MOTION_ACTIVE:
					if(DEBUG)
						System.out.println("OPCODE_MOTION_ACTIVE");
					read(in, buffer, 0, 11);
					x = buffer[0];
					y = buffer[1];
					minDiff = buffer[2] & 0xff;
					minDiff = (minDiff << 8) | (buffer[3] & 0xff);
					minDiff = (minDiff << 8) | (buffer[4] & 0xff);
					minDiff = (minDiff << 8) | (buffer[5] & 0xff);
					angle = buffer[6];
					minDiffRotation = buffer[7] & 0xff;
					minDiffRotation = (minDiffRotation << 8) | (buffer[8] & 0xff);
					minDiffRotation = (minDiffRotation << 8) | (buffer[9] & 0xff);
					minDiffRotation = (minDiffRotation << 8) | (buffer[10] & 0xff);

					if(DEBUG)
						System.out.println("(x,y) = (" + x + "," + y + "), a = " +
						angle + ", dt = " + minDiff + ", dr = " + minDiffRotation);

					double rotX = 0.5 * y * Math.PI / 180;
					double rotY = 0.5 * x * Math.PI / 180;
					double rotZ = -0.4 * angle * Math.PI / 180;

					if (minDiffRotation < minDiff) {
						/* send rotation */
						listener.rotationCallback(angle);
					} else {
						/* send translation*/
						listener.translationCallback(x, y);
					}
					break;

				case OPCODE_MOTION_STOP:
					if(DEBUG)
						System.out.println("OPCODE_MOTION_STOP");
					break;

				case OPCODE_SEND_CODES:
					if(DEBUG)
						System.out.println("OPCODE_SEND_CODES");
					read(in, buffer, 0, 1);
					int n = buffer[0];
					if (n <= 0 || n > 10) {
						currentMenuId = 0;
						Arrays.fill(buffer, (byte)0);
						/* no codes in picture, just send a click */
						listener.clickCallback();
						break;
					}
					read(in, buffer, 0, n*(31) + 1);
					int j = 0;
					int currentMenuIdIndex = -1;
					IncomingCode[] mc = new IncomingCode[n];
					for (int i = 0; i < n; i++) {
						mc[i] = new IncomingCode();
						for(int k = 0; k < INCOMING_CODE_NUM_BYTES; k++){
							mc[i].code += valueOf(buffer[j+INCOMING_CODE_NUM_BYTES-1-k], true);
						}
						j += INCOMING_CODE_NUM_BYTES;
						mc[i].targetX = (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].targetY = (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].tlX= (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].tlY= (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].trX= (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].trY= (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].blX= (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].blY= (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].brX= (buffer[j++] << 8) | (buffer[j++] & 0xff);
						mc[i].brY= (buffer[j++] << 8) | (buffer[j++] & 0xff);

						if(DEBUG)
							System.out.println("code = " + mc[i].code +
								", target = (" + mc[i].targetX + "," + mc[i].targetY + ")");
					}

					int closestCodeIndex = buffer[j++] & 0xff;
					listener.codeCallback(mc[closestCodeIndex].code, 
										  mc[closestCodeIndex].targetX, mc[closestCodeIndex].targetY);
					break;

				default:
					throw new IOException("unknown opcode");
			}

		} catch (IOException ex) {
			System.out.println(ex.getMessage());
			try { Thread.sleep(1000); } catch (InterruptedException ex2) {}
		}
	}

	public void read(InputStream in, byte[] buffer, int off, int len) throws IOException {
		int i;
		while (len > 0 && (i = in.read(buffer, off, len)) != -1) {
			off += i;
			len -= i;
		}
		if (len > 0) throw new IOException("read error");
	}
	
	public static String valueOf(byte num, boolean padding) {
		String hex = Integer.toHexString((int)num);

		if (padding) {
			hex = "00" + hex;
			int len = hex.length();

			hex = hex.substring(len - 2, len);
		} 
		return hex;
	}
}
