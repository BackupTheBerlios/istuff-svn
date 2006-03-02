//
//  iStuffPatchUI.h
//  QCiStuff
//
//  Created by René Reiners on 02/03/2006.
//  Copyright 2006 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "QCInspector.h"
#import "CustomPatch.h"

@interface CustomPatchUI : QCInspector
{
// ***********Specify IB Outlets and member variables ***************

}

// ********* QCInspector standard methods that are extended *********
+ (id)viewNibName;
- (id)init;
- (void)setupViewForPatch:(id)fp8; // load data from the model (QCPatch)
- (void) resetView; // store data in the model (QCPatch)


// ********* Interface Builder Actions **************

@end
