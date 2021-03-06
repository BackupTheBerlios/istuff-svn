//
//  InterfaceKitproxy.java
//  
//
//  Created by Raja Gumienny and Manfred Grosserohde on 8/23/05.
//  Copyright 2005 __Media Computing Group at RWTH Aachen University__. All rights reserved.
//

import Phidgets.*;
import java.io.*;
import java.util.*;
import iwork.eheap2.*;


// extending _IPhidgetInterfaceKitEventsAdapter allows your class to pick and choose which Phidget
// events you want to implement.  
public class InterfaceKitproxy extends _IPhidgetInterfaceKitEventsAdapter
{
	public EventHeap eheap;
	private String _proxyID;
	PhidgetInterfaceKit phid = new PhidgetInterfaceKit();
	
        
		// PhidgetInterfaceKit has new Sensor data
	public void OnSensorChange(_IPhidgetInterfaceKitEvents_OnSensorChangeEvent sens_e){
		
		try{
			// this is a generic callback to publish all data from PhidgetInterfaceKit sensors 
			System.out.println("Sensor changed: " + sens_e.get_SensorValue());
			Event e = new Event("PhidgetInterfaceKit");
			e.addField("ProxyID", _proxyID);
			
				e.addField("InputType", "SensorData");
				e.addField("Index", new Integer(sens_e.get_Index()));
			    e.addField("Min", new Integer(phid.GetSensorNormalizeMinimum(sens_e.get_Index())));
				e.addField("Max", new Integer(phid.GetSensorNormalizeMaximum(sens_e.get_Index())));
				e.addField("Value", new Integer(sens_e.get_SensorValue()));
			// set the time to life shorter --> better performance
			e.setTimeToLive(50);
			if (eheap.isConnected()) {
				eheap.putEvent(e);
			}
		} catch( Exception ex ){ ex.printStackTrace(); }
	}
				
		public void OnError(_IPhidgetInterfaceKitEvents_OnErrorEvent error_e){
	}

	public static void main(String[] args) {
		if(args.length == 1)
			new InterfaceKitproxy(args[0],"");
		else if (args.length > 1)
			new InterfaceKitproxy(args[0], args[1]);
		 else 
			System.out.println("Usage: InterfaceKitproxy <Event Heap Server Name> [ProxyID]");
	}
	
	public InterfaceKitproxy(String eventHeapServerName, String proxyID){

        eheap = new EventHeap( eventHeapServerName );
        _proxyID = proxyID;
		// By adding the EventListener, we tell the PhidgeInterfaceKit where it can throw the events
		// to.
		phid.add_IPhidgetInterfaceKitEventsListener(this);

		// We need to open the device.  
		if (phid.Open(false) == false) 
		{
			System.out.println("Could not find a PhidgetInterfaceKit");
			return;
		}
		phid.OpenRemoteIP("localhost",5001,-1,"pass");


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
