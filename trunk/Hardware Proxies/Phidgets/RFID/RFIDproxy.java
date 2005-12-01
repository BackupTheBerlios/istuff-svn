//
//  RFIDproxy.java
//  
//
//  Created by Raja Gumienny and Manfred Grosserohde on 8/15/05.
//  Copyright 2005 __Media Computing Group at RWTH Aachen University__. All rights reserved.
//

import Phidgets.*;
import java.io.*;
import java.util.*;
import iwork.eheap2.*;


// extending _IPhidgetRFIDEventsAdapter allows your class to pick and choose which Phidget
// events you want to implement.
public class RFIDproxy extends _IPhidgetRFIDEventsAdapter
{
	public EventHeap eheap;
	    
		// PhidgetInterfaceKit has new data
        public void OnTag(_IPhidgetRFIDEvents_OnTagEvent ke) {
		try {
		// this is a generic callback to publish all data from the RFID sensor
		System.out.println("Tag Found: " + ke.get_TagNumber());
		Event e = new Event("PhidgetRFID");
		e.addField("TagNumber", ke.get_TagNumber());
		eheap.putEvent(e);
		} catch( Exception ex ){ ex.printStackTrace(); }
	
        }
		
		public void OnDetach(_IPhidgetRFIDEvents_OnDetachEvent ke) {
		System.out.println("FINISHED!");
        }

	public static void main(String[] args) {
		if (args.length == 1) {
			new RFIDproxy(args[0]);
		}
		else{
			System.out.println("usage: RFIDproxy <Event Heap Server Name>");
		}
	}
	public RFIDproxy(String eventHeapServerName){

        eheap = new EventHeap( eventHeapServerName );
		PhidgetRFID phid = new PhidgetRFID();
		// By adding the EventListener, we tell the PhidgetRFID where it can throw the events
		// to.
		phid.add_IPhidgetRFIDEventsListener(this);
		

		// We need to open the device.  
		if (phid.Open(false) == false) 
		{
			System.out.println("Could not find a PhidgetRFID");
			return;
		}
		System.out.println(phid.GetDeviceType());
		System.out.println("Serial Number " + phid.GetSerialNumber());
		System.out.println("Device Version " + phid.GetDeviceVersion());
		System.out.println("Attached " + phid.GetIsAttached());
		phid.SetOutputState(3, true);

		// the .run method starts an infinite loop, polling the device for data.
		// If you call .start instead - phid.start() - the infinite loop will
		// run in a separate thread, allowing your program to proceed.
		// In this example, if we called .start, the program immediately finishes.
		phid.run();
	}
}
