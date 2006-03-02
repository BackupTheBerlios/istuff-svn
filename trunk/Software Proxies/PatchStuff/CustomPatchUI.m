//
//  CustomPatchUI.m
//  QCiStuff
//
//  Created by René Reiners on 02/03/2006.
//  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
//

#import "CustomPatchUI.h"

@implementation CustomPatchUI
// this method is called when a patch is inserted and 
// the inspector is  shown for the first time
+ (id)viewNibName
{
	return @"CustomPatchUI.nib";
}
/*


 This method is always called  when the patch is selected
 fp8 is the currently active patch
 The patch passed as parameter provides the model.
 There is one instance of a view that always has to be updated with the current data from the patch.
 In setupViewForPatch the data from the model has to be read and the view has to be updated.
 
 In ResetView the currently displayed data in the view must be stored inside the current model.
 The method is called automatically when another patch or nothing is selected.
*/

- (void)setupViewForPatch:(id)fp8
{
	[super setupViewForPatch:fp8];

}


- (id)init{

	return [super init];
}


// The resetView method is called when the current patch is deselected
- (void)resetView{
 // Here the currently specified data in the view has to be stored inside the model if that did not already happen inside IBActions.
 // --> Saving of what is not saved yet.

  [super resetView];

}

@end
