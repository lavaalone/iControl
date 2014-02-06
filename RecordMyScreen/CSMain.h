//
//  CSMain.h
//  iControl
//
//  Created by Thinh Nguyen on 12/7/13.
//  Copyright (c) 2013 CoolStar Organization. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Define_TypeAndMacro.h"


@interface CSMain : NSObject//<NSStreamDelegate>
{
    // class variables here
}

// public methods here
- (void)Start;
- (void)Stop;
- (void)Update;
- (int)GetCurrentStep;
- (void)HandleReceivedMessage:(BYTE*)data length:(int)length;
- (void)NotifyAppExit;

@end


