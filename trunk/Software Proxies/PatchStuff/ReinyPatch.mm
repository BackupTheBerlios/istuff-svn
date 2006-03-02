//
//  ReinyPatch.mm
//  QCiStuff
//
//  Created by Rene Reiners on 2/21/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//

#import "ReinyPatch.h"

/*
Only change the UI class if there is a new UI file attached.
Otherwise a standard class will be taken.

@interface ReinyPatch (QCInspector)
+ (Class)inspectorClassWithIdentifier:(id)fp8;
@end

@implementation ReinyPatch(QCInspector)

+ (Class)inspectorClassWithIdentifier:(id)fp8
{
NSLog(@"NOW in inspectorClassWithIdentifier FP8 is: %@", fp8);
	
	return [PresentationUI class];
}

@end
*/

@implementation ReinyPatch

- (id)initWithIdentifier:(id)fp8
{
	return [super initWithIdentifier:fp8];
}




@end
