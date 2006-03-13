#import "PRController.h"

#import "PRWindow.h"

#include <string>

@implementation PRController

- (void)awakeFromNib
{
    NSString *layoutFile;
    prefKey = CFSTR("iwork.EventSharing");

    //NSLog([NSString stringWithFormat:@"PointRight Sender started, pid = %d", [[NSProcessInfo processInfo] processIdentifier]]);

    //layoutFile = [self getStringPref:@"PRSenderLayoutFile"];
	layoutFile = @"default.jph";
	
    if (![[NSFileManager defaultManager] fileExistsAtPath:layoutFile]) {
        NSLog([NSString stringWithFormat:@"Couldn't find layout file: %@, Exiting", layoutFile]);
        [self setBooleanPref:@"PRSenderShouldRun" to:NO];
        [[NSDistributedNotificationCenter defaultCenter] postNotificationName:@"ESPrefsChanged" object:nil];
        [[NSDistributedNotificationCenter defaultCenter] postNotificationName:@"ESHelperUpdate" object:nil];
        [[NSApplication sharedApplication] terminate:self];
        return;
    }
    PropertyHash &settings = PRWorld::ReadSettings([layoutFile cString]);
    //settings["eheap"] = [[self getStringPref:@"EventHeapServerName"] cString];
	settings["eheap"] = "127.0.0.1";
	settings["srcMachineName"] = "unset";
	if ([[[NSProcessInfo processInfo] arguments] count] > 2){
		settings["eheap"] = [[[[NSProcessInfo processInfo] arguments] objectAtIndex:1] cString];
		settings["srcMachineName"] = [[[[NSProcessInfo processInfo] arguments] objectAtIndex:2] cString];
	}
    world = new PRWorld(settings);

    screenFrame = [[NSScreen mainScreen] frame];
	//topFrame = NSMakeRect(0,0,100,100);
	topFrame = NSMakeRect(screenFrame.origin.x, screenFrame.size.height-1, screenFrame.size.width, 1);
	//topFrame = NSMakeRect(screenFrame.origin.x, screenFrame.size.height-1, 100, 100);

    [[NSApplication sharedApplication] setDelegate:[NSApplication sharedApplication]];

    window = [[PRWindow alloc] initWithFrame:topFrame withController:self];
    [window makeKeyAndOrderFront:self];
    [window makeFirstResponder:window];
    [window startTracking];
	
	NSRect aFrame = NSMakeRect(screenFrame.size.width/2-200,screenFrame.size.height/2-100,400,200); 
	NSTextView *text = [[NSTextView alloc] initWithFrame: aFrame];
	[text setFont: [NSFont systemFontOfSize: 30.0]]; 
	[[window contentView] addSubview: text];
	[text setString:@"Press ctrl-cmd-q to retrieve cursor."];

}

- (NSString*)getStringPref:(NSString*)key
{
    NSString* str = @"";

    CFPropertyListRef value = CFPreferencesCopyAppValue( (CFStringRef)key, prefKey );
    if ( value && (CFGetTypeID(value) == CFStringGetTypeID()) ) {
        str = [NSString stringWithString:(NSString*)value];
    }
    if (value) CFRelease(value);

    return str;
}

- (void)setBooleanPref:(NSString*)key to:(BOOL)value
{
    CFPreferencesSetAppValue( (CFStringRef)key, (value?kCFBooleanTrue:kCFBooleanFalse), prefKey );
    CFPreferencesAppSynchronize( prefKey );
}

- (NSWindow*)window
{
    return window;
}

- (bool)isSending
{
    return world->isSending();
}

- (void)attemptStart:(NSPoint)mouseLocation
{
    if (world->isSending()) return;
    world->updateMousePosition((int)mouseLocation.x, (int)(screenFrame.size.height - mouseLocation.y));
    if (world->isSending()) [self startCapture];
}

- (void)startCapture
{
    //cout << "start capture" << endl;
    
    [[NSApplication sharedApplication] activateIgnoringOtherApps:YES];
    [NSCursor hide];    

    CGAssociateMouseAndMouseCursorPosition(false);
    CGPoint p = { screenFrame.size.width/2, screenFrame.size.height/2 };
    CGWarpMouseCursorPosition(p);
    
    [window setFrame:screenFrame display:NO];
    [window setAcceptsMouseMovedEvents:YES];
}

- (void)stopCapture
{
    //cout << "stop capture" << endl;

    if (world->isSending()) world->stopSending();
    
    [window setAcceptsMouseMovedEvents:NO];
    [window setFrame:topFrame display:NO];

    CGPoint p = { world->getMouseLocation().x, 2 };
    CGWarpMouseCursorPosition(p);
    CGAssociateMouseAndMouseCursorPosition(true);
    
    [NSCursor unhide];
    //[[NSApplication sharedApplication] hide:self]; //with this commented out I still can post key event to the program
    [[NSApplication sharedApplication] unhideWithoutActivation];

    [window startTracking];
}

- (void)mouseMoved
{
    if (world->isSending())
    {
        CGMouseDelta x,y;
        CGGetLastMouseDelta(&x,&y);
        world->updateMousePosition(x,y,PR_RELATIVE);
        if (!world->isSending()) [self stopCapture];
    }
}

- (void)mouseButton:(int)button isDown:(bool)isDown
{
    //cout << "buttonNumber: " << button << endl;
    if (world->isSending()) world->updateMouseButton(button, isDown);
}


- (void)scrollWheel:(int)value
{
    if (world->isSending()) world->updateScrollWheel(value);
}

- (void)charCode:(int)charCode keyCode:(int)keyCode isDown:(bool)isDown
{
    if (world->isSending()) world->updateKeyState(charCode, keyCode, isDown);
}

@end
