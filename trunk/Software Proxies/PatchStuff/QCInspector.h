/*
 *  QCInspector.h
 *  QCiStuff
 *
 *  Created by Rafael Ballagas on 11/20/05.
 *  Copyright 2005 Media Computing Group, RWTH Aachen University, Germany. All rights reserved.
 *
 */
#include "QCPatch.h"

@interface QCInspector : NSObject
{
    NSView *view;
    QCPatch *_patch;
    void *_unused2[4];
}

+ (id)viewNibName;
+ (id)viewTitle;
- (id)init;
- (void)didLoadNib;
- (id)patch;
- (void)setupViewForPatch:(id)fp8;
- (void)resetView;
- (id)view;

@end

