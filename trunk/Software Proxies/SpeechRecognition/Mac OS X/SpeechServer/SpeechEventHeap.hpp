/*
 *  SpeechEventHeap.h
 *  CarbonSpeechTest
 *
 *  Created by Daniel Spelmezan on Thu Jun 03 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */

#include <Carbon/Carbon.h>

#include <eh2.h>
#include <idk_io.h>


// by inheriting eh2_Consts, you can omit prefix eh2_Consts:: when you use constant values
class SpeechEventHeap : protected eh2_Consts {

public:

	SpeechEventHeap ();
	~SpeechEventHeap ();
	
	eh2_EventHeapPtr createEventHeap ();
	void putEvent (eh2_EventHeap* eh);
	void printEvent (const eh2_Event* event);
	void waitForEvent (eh2_EventHeap* eh);
	void getAll (eh2_EventHeap* eh);
	//void getEvent2 (eh2)EventHeap* eh);
};
