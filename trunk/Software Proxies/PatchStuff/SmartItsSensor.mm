//
//  SmartItsSensorPatch.mm
//  QCiStuff
//
//  Created in by René Reiners in winter 2005/2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//
// This patch waits for "Text Event" from the event heap and directs them
// to the output ports as integers with the ACII code number. As only events are processed, no input ports are needed.

#import "SmartItsSensor.h"
	
@implementation SmartItsSensor

- (id)initWithIdentifier:(id)fp8
{	
	[super initWithIdentifier:fp8];
		// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"Particle_Packet"];
	[self addTemplateEvent:templateEvent];
	return self;
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	return [super execute:fp8 time:fp12 arguments:fp20];
}

- (void) processEvent:(iStuffEvent *) event {

		// set the flag so that in the 'execute'-method the output port is set to the new value
		// after setting it, the flag is set to false again.
		// This allows posting one value per execution cycle
	
		// Read the values from the different fields of the events
		// The checks are necessary because not every field is created inside an event,
		// depending on the attached sensors.
		// This patch only posts the values if they exist.
		
		[outputSourceID setStringValue:[event stringValueForField:@"ParticleSrcId"]];
	
		if ( [event fieldExists:@"sgx"] )
			{ [outputSGX setDoubleValue: (double) [event intValueForField:@"sgx"]]; }
		if ( [event fieldExists:@"sgy"] )
			{ [outputSGY setDoubleValue:(double) [event intValueForField:@"sgy"]]; }
		if ( [event fieldExists:@"sgz"] )
			{ [outputSGZ setDoubleValue:(double) [event intValueForField:@"sgz"]]; }
		if ( [event fieldExists:@"sli"] )
			{ [outputSLI setDoubleValue:(double) [event intValueForField:@"sli"]]; }
		if ( [event fieldExists:@"ste"] )
			{ [outputSTE setDoubleValue:(double) [event intValueForField:@"ste"]]; }
		if ( [event fieldExists:@"sfc"] )
			{ [outputSFC setDoubleValue:(double) [event intValueForField:@"sfc"]]; }
		if ( [event fieldExists:@"sau"] )
			{ [outputSAU setDoubleValue:(double) [event intValueForField:@"sau"]]; }
		if ( [event fieldExists:@"ssw"] )
			{ [outputSSW setDoubleValue:(double) [event intValueForField:@"ssw"]]; }
		if ( [event fieldExists:@"svc"] )
			{ [outputSVC setDoubleValue:(double) [event intValueForField:@"svc"]]; }
}

@end


