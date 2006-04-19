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

- (id)initWithIdentifier:(id)fp8
{
	proxyName = [NSMutableString stringWithString:@"PresentationController_"];
	return [super initWithIdentifier:fp8];
}
	
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
		//iStuffPatch *currentPatch = [self patch];
		const char* name = [eventID cString];
		
		if ((int)[inputGotoSlideNumber doubleValue] != lastInputGotoSlide) {
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("SlideController");
			(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
			(*eventPtr)->setPostValueString ("command", "gotoSlide");
			(*eventPtr)->setPostValueInt("slideNum", (int) [inputGotoSlideNumber doubleValue]);
			(*eventPtr)->setPostValueString ("ProxyID", name);
		    (*eventPtr)->setPostValueInt("TimeToLive", 1000);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;

		}
				
		if( [inputNextSlide booleanValue] == TRUE && [inputNextSlide booleanValue] != lastInputNextSlide){
			//create a new event object
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("SlideController");
			(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
			(*eventPtr)->setPostValueString ("command", "next");
			(*eventPtr)->setPostValueString ("ProxyID", name);
			(*eventPtr)->setPostValueInt("TimeToLive", 1000);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
		}


		if( [inputPrevSlide booleanValue] == TRUE && [inputPrevSlide booleanValue] != lastInputPrevSlide){
			//create a new event object
			eh2_EventPtr *eventPtr = new eh2_EventPtr;
			(*eventPtr) = eh2_Event::cs_create ("SlideController");
			(*eventPtr)->setPostValueString("ProxyID", [eventID cString]);	
			(*eventPtr)->setPostValueString ("command", "prev");
			(*eventPtr)->setPostValueString ("ProxyID", name);
			(*eventPtr)->setPostValueInt("TimeToLive", 1000);
			(*eh)->putEvent (*eventPtr);
			delete eventPtr;
		}
		
		lastInputNextSlide = [inputNextSlide booleanValue];
		lastInputPrevSlide = [inputPrevSlide booleanValue];
		lastInputGotoSlide = (int) [inputGotoSlideNumber doubleValue];
		//lastInputStartPresentation1 = [inputStartPresentation1 booleanValue];
		//lastInputStartPresentation2 = [inputStartPresentation2 booleanValue];
}

@end
