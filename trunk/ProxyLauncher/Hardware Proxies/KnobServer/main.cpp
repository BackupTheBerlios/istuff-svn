#include <Carbon/Carbon.h>
#include <Quicktime/Quicktime.h>
#include <eh2.h>

eh2_EventHeapPtr eventHeapPtr;
int id;
int wheelPos;

//EY:
//later use a global variable to store the absolute wheel position
pascal OSStatus MouseHandler(EventHandlerCallRef  nextHandler, EventRef theEvent, void* userData)
{	
	OSStatus		result = eventNotHandledErr;
	
	eh2_EventPtr eventPtr;
	SInt32 wheelDelta;
	
	//kEventParamMouseWheelDelta
	//kEventParamMouseWheelAxis
	
	GetEventParameter (theEvent, kEventParamMouseWheelDelta,
					   typeSInt32, NULL, sizeof(SInt32), NULL, &wheelDelta);	
	
	//UInt16   wheelAxis;
	//GetEventParameter (theEvent, kEventParamMouseWheelAxis,
	//				   typeMouseWheelAxis, NULL, sizeof(UInt16), NULL, &wheelAxis);	
	
	wheelPos += wheelDelta;
	
	printf("rel: %d ,  abs: %d\n", wheelDelta, wheelPos);
	
	
	//Send an event
	char* typeName = "ScrollEvent";
	eventPtr = eh2_Event::cs_create(typeName);
	
	char* templateValue = "FORMAL";
	eventPtr->setPostValueInt("delta",wheelDelta);
	//eventPtr->setTemplateValueString("delta", "FORMAL");	
	eventPtr->setPostValueInt("absolute",wheelPos);
	//eventPtr->setTemplateValueString("absolute", "FORMAL");	
	eventPtr->setPostValueInt("TimeToLive",2000);	
	
	eventHeapPtr->putEvent(eventPtr);
	
	result = noErr;
	return result;
}




int main(int argc, char* argv[])
{
    IBNibRef 		nibRef;
    WindowRef 		window;
    
    OSStatus		err;
	
	eh2_EventHeapFactory* factory;

	//EY:
	char name[] = "fuller";
	if (argc>1) { //More than just the function call
		//strcpy(&name,argv[0]);
		printf("Arg num %d\n", argc);
		printf("Name without arg %s\n", name);
		printf("Want to connect to %s\n", argv[1]);
		strcpy(name,argv[1]);
	}
	
	printf("Connecting to %s\n", name);
	id = 0;
	wheelPos = 0;

    // Create a Nib reference passing the name of the nib file (without the .nib extension)
    // CreateNibReference only searches into the application bundle.
    err = CreateNibReference(CFSTR("main"), &nibRef);
    require_noerr( err, CantGetNibRef );
    
    // Once the nib reference is created, set the menu bar. "MainMenu" is the name of the menu bar
    // object. This name is set in InterfaceBuilder when the nib is created.
    //err = SetMenuBarFromNib(nibRef, CFSTR("MenuBar"));
    //require_noerr( err, CantSetMenuBar );
    // Then create a window. "MainWindow" is the name of the window object. This name is set in 
    // InterfaceBuilder when the nib is created.
    //err = CreateWindowFromNib(nibRef, CFSTR("MainWindow"), &window);
	//err = CreateCustomWindow(null, ,&window);
	//UInt32 attributes = kWindowNoShadowAttribute | kWindowNoActivatesAttribute | kWindowOpaqueForEventsAttribute ;
	//UInt32 attributes = kWindowNoShadowAttribute | kWindowNoActivatesAttribute;
	//UInt32 attributes = 0x000000;
	Rect size;
	//[NSScreen mainScreen];
	size.top = 0;
	size.left = 0;
	size.bottom = 400;
	size.right = 600;
	printf("b4 create");


	//Have to make it a window that cannot refocus
	// + has to delegates all events to underlying window
    //err = CreateNewWindow(CGShieldingWindowLevel(),attributes,&size,&window);
	//err = CreateNewWindow(kModalWindowClass,attributes,&size,&window);
	err = CreateNewWindow(kFloatingWindowClass,0,&size,&window);
	//WindowActivationScope scope = kWindowActivationScopeNone;
	//SetWindowActivationScope(&window, scope);
	//err = CreateNewWindow(kOverlayWindowClass, overlayAttributes,&window,&size,null);
	Ptr      oldState;
	BeginFullScreen(&oldState,nil,0,0,&window,0,fullScreenAllowEvents);
	
	printf("aft create");
	require_noerr( err, CantCreateWindow );
	printf("no error");
	
    // We don't need the nib reference anymore.
    DisposeNibReference(nibRef);
    
	//Change the window such that it is transparent and passing the event 
	//[window setLevel:NSNormalWindowLevel]
	//setAlphaValue:
	//
	//window->setLevel(NSScreenSaverWindowLevel);
	//SetWindowAlpha(window, 0.5);
	SetWindowAlpha(window, 0.0);
	//SendWindowGroupBehind(window, GetWindowGroupOfClass(kDocumentWindowClass));
	
    // The window was created hidden so show it.
    ShowWindow( window );

	//EY:
    EventTypeSpec    eventTypes[1];
	EventHandlerUPP  handlerUPP;
	eventTypes[0].eventClass = kEventClassMouse;
	eventTypes[0].eventKind  = kEventMouseWheelMoved;
		
	handlerUPP = NewEventHandlerUPP(MouseHandler);
	
	//printf("install event handler\n");
	InstallApplicationEventHandler (handlerUPP,
									1, eventTypes,
									NULL, NULL);
	
	//Init event heap
	eh2_init(NULL,NULL);
	factory = eh2_EventHeapFactory::cs_getInstance();
	eventHeapPtr = factory->createEventHeap(
											NULL,
											name,
											-1
											);
	
    // Call the event loop
    RunApplicationEventLoop();

	CantCreateWindow:
	CantSetMenuBar:
	CantGetNibRef:
		return err;
}

