//
//  SmartItsSensorPatch.mm
//  QCiStuff
//
//  Created in by RenŽ Reiners in winter 2005/2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//
// This patch waits for "Text Event" from the event heap and directs them
// to the output ports as integers with the ACII code number. As only events are processed, no input ports are needed.

#import "SmartItsSensorPatch.h"
	
@implementation SmartItsSensorPatch

- (id)initWithIdentifier:(id)fp8
{	
	proxyName = [NSMutableString stringWithString:@"Particle_Packet"];
	return [super initWithIdentifier:fp8];
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}
/*
- (void) waitForEvents
{
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];

	// define the type of events you want to receive
	const char* eventType = "Particle_Packet";
	eh2_EventPtr templatePtr = eh2_Event::cs_create (eventType);
	eh2_EventPtr dummyPtr = eh2_Event::cs_create("DUMMY");

	eh2_EventCollectionPtr eventsToWaitFor = eh2_EventCollection::cs_create();

	eventsToWaitFor->add(templatePtr);
	eventsToWaitFor->add(dummyPtr);

	while (waitForEvents) {
		eh2_EventPtr resultEventPtr;
		resultEventPtr = (*eh)->waitForEvent (eventsToWaitFor, NULL);

		if ([[NSString stringWithUTF8String:resultEventPtr->getEventType()] isEqual:[NSString stringWithUTF8String:eventType]])
		{		
			// set the flag so that in the 'execute'-method the output port is set to the new value
			// after setting it, the flag is set to false again.
			// This allows posting one value per execution cycle
			
			// Read the values from the different fields of the events
			// The checks are necessary because not every field is created inside an event,
			// depending on the attached sensors.
			// This patch only posts the values if they exist.
			
			[outputSourceID setStringValue:[NSString stringWithCString:resultEventPtr->getPostValueString("ParticleSrcId")]];
		
			if ( resultEventPtr->fieldExists("sgx") )
			{ [outputSGX setDoubleValue:(double) resultEventPtr->getPostValueInt("sgx")]; }
			if ( resultEventPtr->fieldExists("sgy") )
			{ [outputSGY setDoubleValue:(double) resultEventPtr->getPostValueInt("sgy")]; }
			if ( resultEventPtr->fieldExists("sgz") )
			{ [outputSGZ setDoubleValue:(double) resultEventPtr->getPostValueInt("sgz")]; }
			if ( resultEventPtr->fieldExists("sli") )
			{ [outputSLI setDoubleValue:(double) resultEventPtr->getPostValueInt("sli")]; }
			if ( resultEventPtr->fieldExists("ste") )
			{ [outputSTE setDoubleValue:(double) resultEventPtr->getPostValueInt("ste")]; }
			if ( resultEventPtr->fieldExists("sfc") )
			{ [outputSFC setDoubleValue:(double) resultEventPtr->getPostValueInt("sfc")]; }
			if ( resultEventPtr->fieldExists("sau") )
			{ [outputSAU setDoubleValue:(double) resultEventPtr->getPostValueInt("sau")]; }
			if ( resultEventPtr->fieldExists("ssw") )
			{ [outputSSW setDoubleValue:(double) resultEventPtr->getPostValueInt("ssw")]; }
			if ( resultEventPtr->fieldExists("svc") )
			{ [outputSVC setDoubleValue:(double) resultEventPtr->getPostValueInt("svc")]; }
		}
	}
	
	NSLog (@"thread waitForEvents deactivated");

	[localPool release];
}
*/

- (void) processEvent:(eh2_EventPtr) eventPtr {
		// set the flag so that in the 'execute'-method the output port is set to the new value
		// after setting it, the flag is set to false again.
		// This allows posting one value per execution cycle
	
		// Read the values from the different fields of the events
		// The checks are necessary because not every field is created inside an event,
		// depending on the attached sensors.
		// This patch only posts the values if they exist.
		
		[outputSourceID setStringValue:[NSString stringWithCString:eventPtr->getPostValueString("ParticleSrcId")]];
	
		if ( eventPtr->fieldExists("sgx") )
			{ [outputSGX setDoubleValue:(double) eventPtr->getPostValueInt("sgx")]; }
		if ( eventPtr->fieldExists("sgy") )
			{ [outputSGY setDoubleValue:(double) eventPtr->getPostValueInt("sgy")]; }
		if ( eventPtr->fieldExists("sgz") )
			{ [outputSGZ setDoubleValue:(double) eventPtr->getPostValueInt("sgz")]; }
		if ( eventPtr->fieldExists("sli") )
			{ [outputSLI setDoubleValue:(double) eventPtr->getPostValueInt("sli")]; }
		if ( eventPtr->fieldExists("ste") )
			{ [outputSTE setDoubleValue:(double) eventPtr->getPostValueInt("ste")]; }
		if ( eventPtr->fieldExists("sfc") )
			{ [outputSFC setDoubleValue:(double) eventPtr->getPostValueInt("sfc")]; }
		if ( eventPtr->fieldExists("sau") )
			{ [outputSAU setDoubleValue:(double) eventPtr->getPostValueInt("sau")]; }
		if ( eventPtr->fieldExists("ssw") )
			{ [outputSSW setDoubleValue:(double) eventPtr->getPostValueInt("ssw")]; }
		if ( eventPtr->fieldExists("svc") )
			{ [outputSVC setDoubleValue:(double) eventPtr->getPostValueInt("svc")]; }
}

@end


