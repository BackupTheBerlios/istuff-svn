
//
//  RFIDproxy.java
//  
//
//  Created by Raja Gumienny and Manfred Grosserohde on 09/07/05.
//  Copyright 2005 __Media Computing Group at RWTH Aachen University__. All rights reserved.
//

import Phidgets.*;
import java.io.*;
import java.util.*;
import iwork.eheap2.*;


// extending _IPhidgetAccelerometerEventsAdapter allows your class to pick and choose which Phidget
// events you want to implement. 
public class AccelerometerProxy extends _IPhidgetAccelerometerEventsAdapter
{
	public EventHeap eheap;
	private String _proxyID;
	private double X = 0;
	private double Y = 0;
	 
		// PhidgetAccelerometer has new data
        public void OnAccelerationChange(_IPhidgetAccelerometerEvents_OnAccelerationChangeEvent ke) {
		try { System.out.println("Acceleration changed: " + Double.toString(ke.get_Acceleration()));
		if(ke.get_Index() == 1){
			Y = ke.get_Acceleration();
		}
		else if(ke.get_Index() == 0){
			X = ke.get_Acceleration();
		}
		
		Event e = new Event("PhidgetAccelerometer");
		e.addField("X", Double.toString(X));
		e.addField("Y", Double.toString(Y));
		e.addField("ProxyID", _proxyID);
	// change by R. Reiners
	// the Event Heap should not be flooded with events --> short time to live
		e.setTimeToLive(50);
		if (eheap.isConnected()) {
			eheap.putEvent(e);
		}
		} catch( Exception ex ){ ex.printStackTrace(); }
	
        }
		

	public static void main(String[] args) {
		if(args.length == 1)
			new AccelerometerProxy(args[0],"");
		else if (args.length >= 2)
			new AccelerometerProxy(args[0], args[1]);
		 else 
			System.out.println("usage:  AccelerometerProxy <Event Heap Name> [ProxyID]");
	}
	
	public AccelerometerProxy(String eventHeapName, String proxyID){

        eheap = new EventHeap( eventHeapName);
        _proxyID = proxyID;
		PhidgetAccelerometer phid = new PhidgetAccelerometer();
		// By adding the EventListener, we tell the PhidgetAccelerometer where it can throw the events
		// to.
		phid.add_IPhidgetAccelerometerEventsListener(this);
		

		// We need to open the device.  
		if (phid.Open(false) == false) 
		{
			System.out.println("Could not find a PhidgetAccelerometer");
			return;
		}
		System.out.println(phid.GetDeviceType());
		System.out.println("Serial Number " + phid.GetSerialNumber());
		System.out.println("Device Version " + phid.GetDeviceVersion());
		System.out.println("Attached " + phid.GetIsAttached());

		// the .run method starts an infinite loop, polling the device for data.
		// If you call .start instead - phid.start() - the infinite loop will
		// run in a separate thread, allowing your program to proceed.
		// In this example, if we called .start, the program immediately finishes.
		phid.run();
	}
}
