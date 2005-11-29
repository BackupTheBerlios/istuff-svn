//
//  RFIDproxy.java
//  
//
//  Created by Raja Gumienny and Manfred Grosserohde on 8/15/05.
//  Copyright 2005 __Media Computing Group at RWTH Aachen University__. All rights reserved.
//

import iwork.eheap2.Event;
import iwork.eheap2.EventHeap;

import java.util.Timer;
import java.util.TimerTask;

import Phidgets.PhidgetRFID;
import Phidgets._IPhidgetRFIDEventsAdapter;
import Phidgets._IPhidgetRFIDEvents_OnDetachEvent;
import Phidgets._IPhidgetRFIDEvents_OnTagEvent;


// extending _IPhidgetRFIDEventsAdapter allows your class to pick and choose which Phidget
// events you want to implement.
public class RFIDproxyMod extends _IPhidgetRFIDEventsAdapter
{
	 EventHeap eheap;
	 boolean freshTag;
	public Timer timer;
		// PhidgetInterfaceKit has new data
        public void OnTag(_IPhidgetRFIDEvents_OnTagEvent ke) {
        	try {
		// this is a generic callback to publish all data from the RFID sensor
		System.out.println("Tag Found: " + ke.get_TagNumber());
		Event e = new Event("PhidgetRFID");
		e.setTimeToLive(50);
		e.addField("TagNumber", ke.get_TagNumber());
		eheap.putEvent(e);
		freshTag = true;		
		} catch( Exception ex ){ ex.printStackTrace(); }
	        }
		
		public void OnDetach(_IPhidgetRFIDEvents_OnDetachEvent ke) {
		System.out.println("FINISHED!");
        }

		public static void main(String[] args) {
		new RFIDproxyMod();
	}
		
	public RFIDproxyMod(){
        eheap = new EventHeap( "localhost" );
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
		freshTag = true;
		timer = new Timer();
		timer.schedule(new Checker(),0,180);

		// the .run method starts an infinite loop, polling the device for data.
		// If you call .start instead - phid.start() - the infinite loop will
		// run in a separate thread, allowing your program to proceed.
		// In this example, if we called .start, the program immediately finishes.
		phid.run();
	}
	class Checker extends TimerTask{

		public void run() {
			if (freshTag == false) {
			try {			
				Event e = new Event("PhidgetRFID");
				e.setTimeToLive(50);
				e.addField("TagNumber", "");
				eheap.putEvent(e);
				System.out.println("posted empty string");
				}		
			catch( Exception ex ){ ex.printStackTrace(); }
			}
			freshTag = false;
	}
	}
	
}
