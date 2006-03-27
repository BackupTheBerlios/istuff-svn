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
	connectedToEventHeap = false;

	char domainname[1024];
	getdomainname( &domainname[0], sizeof(domainname) );
	//printf( "Domainname=%s\n", &domainname[0] );
	domainName = [NSString stringWithUTF8String:domainname];
	[domainName retain];
	NSLog(@"DomainName variable: %@", domainName); 
	
	netServices = [[NSMutableArray alloc] initWithCapacity:5];
	[netServices retain];
    netServiceBrowser = [[NSNetServiceBrowser alloc] init];
    [netServiceBrowser setDelegate:self];
    [netServiceBrowser searchForServicesOfType:@"_eheap._tcp." inDomain:nil];
	[netServiceBrowser retain];
			// DHCP is recommended! Then the EH service returns reasonable service and host names.
			// Make sure that IPv4 is used. And ipv6 is turned off
			// A NameServer must run if different OS are to be intermingled.
	hostName = [NSString stringWithString:[[NSHost currentHost] name]];
	[hostName retain];
	
	eventHeapName = [NSString stringWithString:hostName];
	[eventHeapName retain]; 

	eh2_init ("iStuffQuartzPlugin", [hostName UTF8String]);	// Names that are provided with each event posted to the heap.
	
	// Register object with Notification Center
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(manageConnection:) name:@"ReconnectAll" object:nil];

	return [super initWithIdentifier:fp8];
}
		
- (void) manageConnection:(NSNotification *) notification {
		// Only if the current patch is not connected, start the connection thread.
		if (notification != nil) {
			connectedToEventHeap = false;
			NSDictionary *dict = [notification userInfo];
			NSString *ehServerName = [NSString stringWithString:[dict valueForKey:@"newEHName"]];
			[self connectToEventHeap:ehServerName];
		}
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

	(*eh) = factory->createEventHeap ([sourceName cString],[serverName cString], port);
		//(*eh) = factory->createEventHeap ([sourceName cString],"localhost", port);
}

- (void) connectToEventHeap:(NSString *) server
{
	// if there is no parameter, connect to the first Event Heap in the list.

	//sleep(1); // Needed, otherwise reconnecting is not possible --The thread has to end first!
	NSString *currentNetServiceName;

	if  (server == nil) {
		if ([netServices count] != 0){
			NSEnumerator *enumerator = [netServices objectEnumerator];
			[self setEventHeapName: [netServices objectAtIndex:0]];
			while (currentNetServiceName = [enumerator nextObject]) {
				if ([currentNetServiceName isEqual:hostName]) [self setEventHeapName: currentNetServiceName];
			}
		}
	}	
	else { // There was a parameter and the patch should connect to that Event Heap
		[self setEventHeapName:[server copy]];
	}
	if ( ! [eventHeapName isEqualToString:@"localhost"])
	{
		NSMutableString *newName = [NSMutableString stringWithString:domainName];
		[newName insertString:@"." atIndex:0];
		[newName insertString:eventHeapName atIndex:0];
		[self createEventHeap:NULL atServer:newName atPort:4535];
	}
	else
		[self createEventHeap:NULL atServer:eventHeapName atPort:4535];
	connectedToEventHeap = true;
	standby = false;
	
	NSString *ehStatus = @"connected";
	NSDictionary *ehInfo = [NSDictionary dictionaryWithObject:ehStatus forKey:@"connectionStatus"];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"EHListChange" object:nil userInfo:ehInfo];
	[eventHeapName retain];
	//sleep(1); // Also prevents crash if proxy is still running but only the event heap crashed
	[self stopReceivingEvents]; // needed here, such that running threads are ended.
	[self startReceivingEvents];
	NSLog(@"Thread that connects to Event Heaps ended");
}

- (void) netServiceBrowser:(NSNetServiceBrowser*)aNetServiceBrowser didFindService:(NSNetService *)aNetService moreComing:(BOOL)moreComing
{
	[netServices addObject:[aNetService name]];
	NSLog(@"Posting in didfindservice: Name: %@", [aNetService name]);
	[[NSNotificationCenter defaultCenter] postNotificationName:@"EHListChange" object:nil];

	if (standby && [[aNetService name] isEqual: eventHeapName]) {
		[self connectToEventHeap:eventHeapName];
	}
	else if ((![self connected]) && !standby){
	 [self connectToEventHeap:nil];
	}
	NSLog(@"In didFindService %@ %i", [aNetService name], [[aNetService addresses] count]);

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
		[[NSNotificationCenter defaultCenter] postNotificationName: @"EHListChange" object: nil userInfo:ehInfo];
		[self stopReceivingEvents];
	}
	else {
		[[NSNotificationCenter defaultCenter] postNotificationName: @"EHListChange" object: nil userInfo:nil];
	}
		NSLog(@"In didRemoveService: %@", [aNetService name]);
    if (!moreComing) [self sendEHSListUpdate];
}

- (void)sendEHSListUpdate
{
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
	return connectedToEventHeap;
}

- (void)dealloc
{	[netServiceBrowser release];
	[netServices release];
	[hostName release];
	[eventHeapName release];
	// Now disconnect from the Event Heap
	eh2_finalize ();
	NSLog(@"All operations in dealloc were finished");
	[super dealloc];
}

- (NSMutableArray *) foundEventHeaps{
	return netServices;
}

-(void) setEventHeapName:(NSString *)newEventHeapName{
	[eventHeapName release];
	eventHeapName = [NSString stringWithString:newEventHeapName];
	[eventHeapName retain];
}

-(NSString *) ehName {
	return [NSString stringWithString:eventHeapName];
}

-(BOOL) advancedOptionsHidden
{
	return advancedOptionsHidden;
}

-(void) setAdvancedOptionsHidden:(BOOL) flag
{
	advancedOptionsHidden = flag;
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

// This method is needed for Provider patches
- (void) startReceivingEvents
{

}

- (void) stopReceivingEvents
{

}

// thread waiting for EH events, so we won't block the recognition system
// the function call (*eh)->waitForEvent is blocking !
// the thread terminates after receiving an event AND if the instance variable waitForEvent is FALSE
// thus, you will still receive an event after calling stopReceivingEvents because (*eh)->waitForEvent blocks until it receives one
- (void) waitForEvents
{
// This method has to be implemented in a subclass.
}
@end
