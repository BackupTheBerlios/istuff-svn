//
//  PresentationControllerPatch.mm
//  QCiStuff
//
//  Created by Rafael Ballagas on 11/7/05.
//	Modified and refactored by RenŽ Reiners in winter 2005/2006
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "PresentationController.h"

@implementation PresentationController

- (void) executeCustomPatch {		

		// Look for a transition from FALSE to TRUE
		// only send event on the "positive edge"
		
		// This is the part where one presentation can be closed and another one is opened and started
		
			// Look for a transition from FALSE to TRUE
		// only send event on the "positive edge"
		
		/*
			if ( [inputStartPresentation1 booleanValue] == TRUE && [inputStartPresentation1 booleanValue] != lastInputStartPresentation1){
			//create a new event object
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("SlideController");
			(*eventPtr)->setPostValueString ("command", "startPresentation1");
			(*eventPtr)->setPostValueString ("URL", [[inputURL1 stringValue] UTF8String]); //From NSString to const char* conversion
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
		}
		
		if ( [inputStartPresentation2 booleanValue] == true && [inputStartPresentation2 booleanValue] != lastInputStartPresentation2){
			//create a new event object
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("SlideController");
			(*eventPtr)->setPostValueString ("command", "startPresentation2");
			(*eventPtr)->setPostValueString ("URL", [[inputURL2 stringValue] UTF8String]); //From NSString to const char* conversion
			(*eh)->putEvent (*eventPtr);			
			delete eventPtr;
		}
		*/
		
		if ((int)[inputGotoSlideNumber doubleValue] != lastInputGotoSlide) {
			iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"SlideController" eventID:[self eventID]];
			[event setTimeToLive:1000];	
			[event addNewStringField:@"command" stringValue:@"gotoSlide"];
			[event addNewIntegerField:@"slideNum" intValue: (int) [inputGotoSlideNumber doubleValue]];
			[event postEvent:eh];
		}
				
		if( [inputNextSlide booleanValue] == TRUE && [inputNextSlide booleanValue] != lastInputNextSlide){
			iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"SlideController" eventID:[self eventID]];
			[event setTimeToLive:1000];	
			[event addNewStringField:@"command" stringValue:@"next"];
			[event postEvent:eh];
		}


		if( [inputPrevSlide booleanValue] == TRUE && [inputPrevSlide booleanValue] != lastInputPrevSlide){
			iStuffEvent *event = [[iStuffEvent alloc] initWithTypeAndID:@"SlideController" eventID:[self eventID]];
			[event setTimeToLive:1000];	
			[event addNewStringField:@"command" stringValue:@"prev"];
			[event postEvent:eh];
		}
		
		lastInputNextSlide = [inputNextSlide booleanValue];
		lastInputPrevSlide = [inputPrevSlide booleanValue];
		lastInputGotoSlide = (int) [inputGotoSlideNumber doubleValue];
		//lastInputStartPresentation1 = [inputStartPresentation1 booleanValue];
		//lastInputStartPresentation2 = [inputStartPresentation2 booleanValue];
}

@end
