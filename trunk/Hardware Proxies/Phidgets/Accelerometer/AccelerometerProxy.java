
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
	 
		// PhidgetAccelerometer has new data
        public void OnAccelerationChange(_IPhidgetAccelerometerEvents_OnAccelerationChangeEvent ke) {
		try { System.out.println("Acceleration changed: " + Double.toString(ke.get_Acceleration()));
		Event e = new Event("PhidgetAccelerometer");
		e.addField("Acceleration", Double.toString(ke.get_Acceleration()));
		eheap.putEvent(e);
		} catch( Exception ex ){ ex.printStackTrace(); }
	
        }
		

	public static void main(String[] args) {
		new AccelerometerProxy();
	}
	public AccelerometerProxy(){

        eheap = new EventHeap( "localhost" );
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
