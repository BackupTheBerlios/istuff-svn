//
//  CustomTableView.h
//  QCiStuff
//
//  Created by Rene Reiners on 4/5/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface CustomTableView : NSTableView {

	BOOL allowEditing;
}

- (void)textDidEndEditing:(NSNotification *)aNotification;


@end
