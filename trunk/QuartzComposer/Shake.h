//
//  Shake.h
//  QCiStuff
//
//  Created by Rafael Ballagas 2008/04/28.
//  Copyright 2008, Nokia Research Center Palo Alto, USA. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iStuffProviderPatch.h"

@interface Shake : iStuffProviderPatch {

	QCStringPort *outputSourceID;
	QCNumberPort *outputAccX;
	QCNumberPort *outputAccY;
	QCNumberPort *outputAccZ;
	QCNumberPort *outputGyroPitch;	
	QCNumberPort *outputGyroRoll;
	QCNumberPort *outputGyroYaw;
	QCNumberPort *outputMagX;
	QCNumberPort *outputMagY;
	QCNumberPort *outputMagZ;
	QCNumberPort *outputCompass;
	QCNumberPort *outputCap0;
	QCNumberPort *outputCap1;
	QCNumberPort *outputAnalogIn0;
	QCNumberPort *outputAnalogIn1;
	QCNumberPort *outputJogDial;
	QCBooleanPort *outputSelect;
	QCNumberPort *outputTemp;
	QCNumberPort *outputBattery;
}

- (id) initWithIdentifier:(id)fp8;
- (BOOL) execute:(id)fp8 time:(double)fp12 arguments:(id)fp20;

@end
