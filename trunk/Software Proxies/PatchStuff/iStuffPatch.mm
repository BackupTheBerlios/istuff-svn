//
//  iStuffPatch.mm
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 Media Computing Group RWTH Aachen. All rights reserved.
//
// This is an abstract class for the development of iStuff patches.
// Concrete patches must also supply a UI class.

#import "iStuffPatch.h"
	
@interface iStuffPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation iStuffPatch(QCInspector)

+ (Class)inspectorClassWithIdentifier:(id)fp8
{	
	return [iStuffPatchUI class];
}
@end


@implementation iStuffPatch

+ (int)executionMode
{
        //  1 - Consumer Patch (Renderer, Environment) - pink title bar
        //  2 - Provider Patch (Source, Tool, Controller) - blue title bar
        //  3 - Processor Patch (Numeric, Modifier, Generator) - green title bar
        return nil; // Standard is 2 - nil should point out that this class is an abstraction which does not provide all the functionality
}
	
+ (BOOL)allowsSubpatches
{
        // If your patch is a parent patch, like 3D Transformation,
        // you will allow subpatches, otherwise FALSE.
	return FALSE;
}
	
- (id)initWithIdentifier:(id)fp8
{
	advancedOptionsHidden = true;
	standby = false;
	tryToConnect = true;
	connectToEventHeaps = true;
	netServices = [[NSMutableArray alloc] initWithCapacity:5];
	[netServices retain];
    netServiceBrowser = [[NSNetServiceBrowser alloc] init];
    [netServiceBrowser setDelegate:self];
    [netServiceBrowser searchForServicesOfType:@"_eheap._tcp." inDomain:nil];
	[netServiceBrowser retain];
			// DHCP is recommended! Then the EH service returns reasonable service and host names.
	hostName = [NSString stringWithString:[[NSHost currentHost] name]];
	[hostName retain]; 
	NSLog(@"Hostname %@", hostName);

	NSArray *ipaddresses = [[NSHost currentHost] addresses];
	if([ipaddresses count] == 0)
	NSLog (@"Your machine network settings are not properly configured. Please enable DHCP");
	
	NSLog(@"THE number of addreses: %i", [ipaddresses count]);
	// Normally, the current IP address ist stored in the first element of the NSArray returned by the  addresses method.
	NSLog(@"THE ADDRESS IS: %@", [ipaddresses objectAtIndex:0]);
	
	[hostName retain]; 
	// default connection
	eventHeapName = [NSString stringWithString:hostName];
	[eventHeapName retain];
	eh2_init ("iStuffQuartzPlugin", [hostName UTF8String]);	// Names that are provided with each event posted to the heap.
	NSLog(@"Hostname %@", eventHeapName);
	connectedToEventHeap = false;
	[connectedToEventHeap retain];
	
	// Register object with Notification Center
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(establishEHConnection:) name:@"ConnectToEH" object:nil];
	[self establishEHConnection:nil];
	// create the thread that connects to the Event Heap
	[NSThread detachNewThreadSelector:@selector(connectToEventHeap) toTarget:self withObject:nil];

	return [super initWithIdentifier:fp8];
}
		
- (id)setup:(id)fp8
{
  // fp8 is the QCOpenGLContext
	// setup vars here
        return fp8;
}

// create the Event Heap instance for the client
- (void) createEventHeap:(NSString *)sourceName atServer:(NSString *) serverName atPort:(int)port
{
	// first, get the Event Heap factory
	// you are not responsible of releasing the reference to it
	eh2_EventHeapFactory *factory = eh2_EventHeapFactory::cs_getInstance ();

	// then, ask the factory for creating the Event Heap client instance
	// you have the ownership of the returned object, so you have to keep it in a smart pointer
	// specify source name, event heap host (e.g., "localhost"), and default port
	// allocate memory for Event Heap client
	eh = new (eh2_EventHeapPtr);

	//(*eh) = factory->createEventHeap (NULL, "localhost", 4535);
	//make a copy of the serverName. Otherwise eventHeapName will be destroyed.
	(*eh) = factory->createEventHeap ([sourceName cString],[serverName cString], port);
}

- (void) establishEHConnection:(NSNotification *) notification
{	
	if (notification != nil) {
	NSDictionary *tempDic = [notification userInfo];
	[self setEventHeapName:[tempDic valueForKey:@"newEHName"]];
	NSLog(@"Dictionary value: %@", [tempDic valueForKey:@"newEHName"]);
	// set the flags to activate the thread
	}
	delete eh;
	connectToEventHeaps = true;
	tryToConnect = true;
}

- (void) disconnectFromEH
{
	tryToConnect = false;
	connectToEventHeaps = false;
	connectedToEventHeap = false;
}

- (void) connectToEventHeap
{
	// This thread should only be ended when the patch is deleted or QC is quit
	// All active services are discovered (I think). It does not seem to be a problem.
	// The flag connectToEventHeaps is set until a patch is deleted
	
	// create an autorelease pool for the thread
	NSAutoreleasePool *localPool;
	localPool = [[NSAutoreleasePool alloc] init];	
	
	NSString *serverName;
	NSString *currentNetServiceName;
	
	// Standard connection: localhost
	// tryToConnect has to be set inside other methods. Then
	// the inner loop that searches for a matching Event Heap is run again
  sleep(1); // Need time to discover every service
  NSLog(@"Searching for Event Heaps...");
  while (connectToEventHeaps){
   // NSLog(@"ConnectToEventHeaps is true...");

	while (tryToConnect) {
	 // NSLog(@"In try to connect loop...");

	if ([netServices count] != 0){
		NSEnumerator *enumerator = [netServices objectEnumerator];
		serverName = [netServices objectAtIndex:0];
		NSLog(@"%i Services were found. Trying to connect", [netServices count]);
		while (currentNetServiceName = [enumerator nextObject]) {
			NSLog (@"In inner loop %@", eventHeapName);
			if ([currentNetServiceName isEqual:eventHeapName]) {
			serverName = currentNetServiceName;
			NSLog (@"ServerName is %@", eventHeapName);
			}
		}
		[eventHeapName release];  // a different Event Heap.
		eventHeapName = [NSString stringWithString:serverName];
		[eventHeapName retain];
		if ([eventHeapName isEqual:hostName]){
			[self createEventHeap:NULL atServer:@"localhost" atPort:4535];
				NSLog(@"CREATED EH WITH constant");
		}
		else {
			[self createEventHeap:NULL atServer:eventHeapName atPort:4535];
			NSLog(@"CREATED EH WITH eventHeapName parameter");
		}	
		connectedToEventHeap = true;
		NSLog(@"connectedFlag is true");
		standby = false;
		// post a notification that signifies that the view has to be uodated
		NSString *ehStatus = @"connected";
		NSDictionary *ehInfo = [NSDictionary dictionaryWithObject:ehStatus forKey:@"connectionStatus"];
		[[NSNotificationCenter defaultCenter] postNotificationName: @"EHStatusChanged" object: nil userInfo:ehInfo];
		NSLog(@"Notifcation CONNECTED posted");
		//[ehInfo release];
		//[ehStatus release];
		
        tryToConnect = false; // Now the loop is skipped until another method turns the flag to true again in order to connect to 
		NSLog (@"LOCAL HOST RUNNING - created EH %@", eventHeapName);
		}
	} // otherwise the outerloop does not finish
	
	sleep(2);

  } // Here the loop ends if connectToEventHeaps is false --> the patch is removed or QC quit.	
	NSLog(@"Thread that connects to Event Heaps ended");
	//[eventHeapName retain];
	[localPool release]; // exit the thread.

}

- (void) netServiceBrowser:(NSNetServiceBrowser*)aNetServiceBrowser didFindService:(NSNetService *)aNetService moreComing:(BOOL)moreComing
{
	[netServices addObject:[aNetService name]];
    [aNetService setDelegate:self];
    [aNetService resolveWithTimeout:10];
	[[NSNotificationCenter defaultCenter] postNotificationName: @"EHStatusChanged" object: nil userInfo:nil];
	NSLog(@"In didFindService %@ %i", [aNetService name], [[aNetService addresses] count]);
	if (standby && [[aNetService name] isEqual: eventHeapName]) {
		[self establishEHConnection:nil];
	}
    if (!moreComing) [self sendEHSListUpdate];
}

- (void) netServiceBrowser:(NSNetServiceBrowser *)aNetServiceBrowser didRemoveService:(NSNetService *)aNetService moreComing:(BOOL)moreComing
{
    NSEnumerator *enumerator = [netServices objectEnumerator];
	NSString *currentNetServiceName;

	while (currentNetServiceName = [enumerator nextObject]) {
        if ([currentNetServiceName isEqual:[aNetService name]]) {
            [netServices removeObject:currentNetServiceName];
            break;
        }
    }
	
	if ([[aNetService name] isEqual:eventHeapName]){
		connectedToEventHeap = false;
		standby = true;
		// post a notification that signifies that the view has to be uodated
		NSString *ehStatus = @"standby";
		NSDictionary *ehInfo = [NSDictionary dictionaryWithObject:ehStatus forKey:@"connectionStatus"];
		[[NSNotificationCenter defaultCenter] postNotificationName: @"EHStatusChanged" object: nil userInfo:ehInfo];
		NSLog(@"Notifcation disconnected and standby posted");
		NSLog(@"The connection to the Event Heao %@ was interrupted", currentNetServiceName);
	}
	else {
		[[NSNotificationCenter defaultCenter] postNotificationName: @"EHStatusChanged" object: nil userInfo:nil];
		NSLog(@"Reload data notification posted");
	}
		NSLog(@"In didRemoveService: %@", [aNetService name]);
    if (!moreComing) [self sendEHSListUpdate];
}

- (void)sendEHSListUpdate
{
    NSLog(@"EHSListUpdate");
    NSDictionary *message = [NSDictionary dictionaryWithObject:netServices
                                                       forKey:@"EventHeapServiceList"];
    [[NSDistributedNotificationCenter defaultCenter] postNotificationName:@"ESEventHeapServiceListUpdate" object:nil userInfo:message];
}


- (BOOL)execute:(id)fp8 time:(double)fp12 arguments:(id)fp20
{
	// This is where the execution of your patch happens.
        // Everything in this method gets executed once
        // per 'clock cycle', which is available in fp12 (time).
	
        // fp8 is the QCOpenGLContext*.  Don't forget to set
        // it before you start drawing.  
	
        // Read/Write any ports in here too.
		
        return TRUE;
}

- (BOOL) connected
{
	if (connectedToEventHeap)
	NSLog(@"CONNECTED!!");
	else
	NSLog (@"NOT CONNECTED");
	return connectedToEventHeap;
}

- (void)dealloc
{
	[netServiceBrowser release];
	[netServices release];
	[hostName release];
	[eventHeapName release];
	
	// stop thread that receives EH events
//	[self disconnectFromEH:eventHeapName];
//	[self stopReceivingEvents];
	// Now disconnect from the Event Heap
	eh2_finalize ();
	[super dealloc];
	NSLog(@"All operations in dealloc were finished");
}

- (NSMutableArray *) foundEventHeaps{
	return netServices;
}

- (void)nodeWillRemoveFromGraph{
	[self disconnectFromEH];
	NSLog(@"node removed - call dealloc manually or check wether it is called");
	sleep(2); // Needed such that the connection management thread is quit first.
			  // Otherwise, dealloc won't be called.

	[super nodeWillRemoveFromGraph];
}

-(void) setEventHeapName:(NSString *)newEventHeapName{
	[eventHeapName release];
	eventHeapName = [NSString stringWithString:newEventHeapName];
	[eventHeapName retain];
}

-(NSString *) eventHeapName {
	return [[eventHeapName copy] autorelease];
}

-(BOOL) advancedOptionsHidden
{
	return advancedOptionsHidden;
}

-(void) setAdvancedOptionsHidden:(BOOL) flag
{
	advancedOptionsHidden = flag;
	NSLog(@"STATUS of hidden: %b", advancedOptionsHidden);
}
-(BOOL) suspended {
	return standby;
}

- (void) setRadioButtonIndex:(int)index{
	radioButtonIndex = index;
}

-(int) radioButtonIndex {
	return radioButtonIndex;
}


@end
