//
//  Threshold.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//
#import "Filter.h"

@implementation Filter

+ (int) executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
		return 3;
}

- (id)initWithIdentifier:(id)fp8
{
	lastInputVal = 0;	
	return [super initWithIdentifier:fp8];
}
	
- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
		// Remember the last input value to compare with the new one
		double currentInput = [inputInputValue doubleValue];
		double thresholdValue = [inputThreshold doubleValue];
		double changeByValue = [inputChangeBy doubleValue];
		
		if (( currentInput >= thresholdValue) &&
			(abs ((int)(currentInput - lastInputVal)) >= changeByValue) ||
			(currentInput == 0))
			{
				[outputPassthrough setDoubleValue:currentInput];
				NSLog(@"New output set");
				lastInputVal = currentInput;
			}
	
		return [super execute:fp8 time:fp12 arguments:fp20];
}

@end
