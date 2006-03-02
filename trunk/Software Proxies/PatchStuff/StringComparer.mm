//
//  StringComparer.mm
//  QCiStuff
//
//  Created by René Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "StringComparer.h"

@implementation StringComparer

+ (int) executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
		return 3;
}

- (id)initWithIdentifier:(id)fp8
{		
	return [super initWithIdentifier:fp8];
}

- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
		if ([[inputCompareThisString stringValue] compare:[inputWithString stringValue]] == NSOrderedSame){//	NSComparisonResult NSOrderedSame){
			[outputResult setBooleanValue:true];
		}
		else {
			[outputResult setBooleanValue:false];
		}

		return [super execute:fp8 time:fp12 arguments:fp20];
}

@end
