//
//  Shake.mm
//  QCiStuff
//
//  Created by Rafael Ballagas 2008/04/28.
//  Copyright 2008, Nokia Research Center Palo Alto, USA. All rights reserved.
//

#import "Shake.h"
	
@implementation Shake

- (id)initWithIdentifier:(id)fp8
{	
	[super initWithIdentifier:fp8];
		// define the templates that the patch should register for. 
	iStuffEvent *templateEvent = [[iStuffEvent alloc] initWithType:@"Shake"];
	[templateEvent addNewStringTemplateField:@"Sensor"];
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
		
		// Not yet implemented a source id for the shake.  Perhaps it should be the Serial Number (from the discovery)
		//[outputSourceID setStringValue:[event stringValueForField:@"ParticleSrcId"]];
		NSLog(@"in Shake processEvent");
		NSString *sensorType = [[NSString alloc] initWithString:[event stringValueForField:@"Sensor"]];
			
		if( [sensorType isEqualToString:@"$ACC"] ) // Accelerometer
		{
			[outputAccX setDoubleValue: (double) [event intValueForField:@"Data1"]]; 
			[outputAccY setDoubleValue: (double) [event intValueForField:@"Data2"]]; 
			[outputAccZ setDoubleValue: (double) [event intValueForField:@"Data3"]]; 			
		}
		else if( [sensorType isEqualToString:@"$HED"] ) // Compass
		{
			[outputCompass setDoubleValue:(double) [event intValueForField:@"Data1"]]; 
		}
		else if( [sensorType isEqualToString:@"$ARS"] ) // Angular Rate Sensor
		{ 
			[outputGyroPitch setDoubleValue: (double) [event intValueForField:@"Data1"]]; 
			[outputGyroRoll setDoubleValue: (double) [event intValueForField:@"Data2"]]; 
			[outputGyroYaw setDoubleValue: (double) [event intValueForField:@"Data3"]]; 
		}			
		else if( [sensorType isEqualToString:@"$NVU"] ) // Navigation Switch (JogDial) up
		{
			[outputJogDial setDoubleValue:1];
		}
		else if( [sensorType isEqualToString:@"$NVD"] ) // Navigation Switch (JogDial) down
		{
			[outputJogDial setDoubleValue:-1];
		}
		else if( [sensorType isEqualToString:@"$NVN"] ) // Navigation Switch (JogDial) neutral
		{
			[outputJogDial setDoubleValue:0];
			[outputSelect setBooleanValue:NO];
		}
		else if( [sensorType isEqualToString:@"$NVC"] ) // Navigation Switch (JogDial) click
		{
			[outputSelect setBooleanValue:YES];
		}
		else if( [sensorType isEqualToString:@"$CS0"] )
		{
			[outputCap0 setDoubleValue:[event intValueForField:@"Data1"]];
		}
		else if( [sensorType isEqualToString:@"$CS1"] )
		{
			[outputCap1 setDoubleValue:[event intValueForField:@"Data1"]];
		}
		else if( [sensorType isEqualToString:@"$AI0"] )
		{
			[outputAnalogIn0 setDoubleValue:[event intValueForField:@"Data1"]];
		}
		else if( [sensorType isEqualToString:@"$AI1"] )
		{
			[outputAnalogIn1 setDoubleValue:[event intValueForField:@"Data1"]];
		}		
		else if( [sensorType isEqualToString:@"$MAG"] )
		{
			[outputMagX setDoubleValue: (double) [event intValueForField:@"Data1"]]; 
			[outputMagY setDoubleValue: (double) [event intValueForField:@"Data2"]]; 
			[outputMagZ setDoubleValue: (double) [event intValueForField:@"Data3"]]; 
		}
		else if( [sensorType isEqualToString:@"$ACK"] )
		{
			int ackNum = [event intValueForField:@"Data1"];
			if( ackNum == 107 )
			{
					double temp = [event intValueForField:@"Data2"] * 0.25; // degrees C
					[outputTemp setDoubleValue:temp];
			}
			else if( ackNum == 105 )
			{
					double battery = [event intValueForField:@"Data2"] / 255 * 100; // in percent
					[outputBattery setDoubleValue:battery];
			}
		}		
}

@end


