//
//  CSMain.m
//  iControl
//
//  Created by Thinh Nguyen on 12/7/13.
//  Copyright (c) 2013 CoolStar Organization. All rights reserved.
//

#import "CSMain.h"

@interface CSMain()

// private methods here
-(void)HandleSomething;

@end

@implementation CSMain

-(void)Update
{
    NSLog(@"Update with current step = %d", _currentStep);
}

-(void)HandleSomething
{
    NSLog(@"Handle some things here");
}

@end
