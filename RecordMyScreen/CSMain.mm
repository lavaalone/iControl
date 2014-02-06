//
//  CSMain.m
//  iControl
//
//  Created by Thinh Nguyen on 12/7/13.
//  Copyright (c) 2013 CoolStar Organization. All rights reserved.
//

#import "CSMain.h"

#import "Defines.h"
#import "FBEncode.h"
#import "FBDecode.h"
#import "Misc/CommandID.h"
#import "Misc/DatabaseID.h"
#import "Misc/KeyID.h"
#import "Misc/ReturnCode.h"
#include <unistd.h>


#import <dlfcn.h>
#import "GSEvent.h"

#import "CSRecordViewController.h"
#import "CSScreenRecorder.h"
#import "SocketConnection.h"
#import <AVFoundation/AVFoundation.h>

#define SBSERVPATH  "/System/Library/PrivateFrameworks/SpringBoardServices.framework/SpringBoardServices"

#define REPORT_CURRENT_STEP 89
#define PERFORM_TOUCH_SCREEN 90
#define GO_HOME_SCREEN 91
#define TAKE_SCREEN_SHOT 92
#define REPORT_FRONTMOST_APP 93
#define EXIT 94
#define NOTIFY_APP_EXIT 95
#define DOUBLE_HOME_TOUCH 96

@interface CSMain()
{
    bool _touchdown;
    int _currentStep;
    
    int _command_id;
    int _request_id;
    int _response_status;
    
    CSRecordViewController *_recordVC;
    CSScreenRecorder *_screenRecorder;
}
@property (nonatomic, strong) AVQueuePlayer *player;
@property (nonatomic, strong) NSInputStream *inputStream;
@property (nonatomic, strong) NSOutputStream *outputStream;


@end

@implementation CSMain

- (id)init
{
    self = [super init];
    if (self)
    {
        _touchdown = true;
        _recordVC = [[CSRecordViewController alloc] init];
        _screenRecorder = [[CSScreenRecorder alloc] init];
        
        _request_id = 0;
        _currentStep = 0;
        
    }
    
    NSLog(@"###CSMain.. init complete with current step %d", _currentStep);
    
    // Play audio
    // Set AVAudioSession
    NSError *sessionError = nil;
    [[AVAudioSession sharedInstance] setDelegate:self];
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:&sessionError];
    
    // Change the default output audio route
    UInt32 doChangeDefaultRoute = 1;
    AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryDefaultToSpeaker, sizeof(doChangeDefaultRoute), &doChangeDefaultRoute);
    
    UInt32 allowMixing = true;
    AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryMixWithOthers, sizeof(allowMixing), &allowMixing);
    
    NSArray *queue = @[[AVPlayerItem playerItemWithURL:[[NSBundle mainBundle] URLForResource:@"button-3" withExtension:@"mp3"]]];
    
    self.player = [[AVQueuePlayer alloc] initWithItems:queue];
    self.player.actionAtItemEnd = AVPlayerActionAtItemEndNone;
    
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector ( playerItemDidReachEnd: ) name: AVPlayerItemDidPlayToEndTimeNotification object: [queue lastObject] ];

    [self.player play];
    [self ShowNotification];
    [self Start];
    
//    // Set up VoIP services
//    CFReadStreamRef readStream;
//    CFWriteStreamRef writeStream;
//    CFStreamCreatePairWithSocketToHost(NULL, ( CFStringRef)(@"192.168.2.111"), [@"444" intValue], &readStream, &writeStream);
//    self.inputStream = (NSInputStream *)readStream;
//    self.outputStream = (NSOutputStream *)writeStream;
//    [self.inputStream setProperty:NSStreamNetworkServiceTypeVoIP forKey:NSStreamNetworkServiceType];
////    [self.inputStream setDelegate:self];
////    [self.outputStream setDelegate:self];
//    [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
//    [self.outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
//    [self.inputStream open];
//    [self.outputStream open];
//    
//    [[UIApplication sharedApplication] setKeepAliveTimeout:600 handler:^{
//        NSLog(@"###KeepAliveTimeOut");
//    }];
    
    return self;
}

- (void)addEvent:(NSString *)event
{
    if (UIApplication.sharedApplication.applicationState == UIApplicationStateActive)
    {
        NSLog(@"###App is forgrounded. New event: %@", event);
    }
    else
    {
        NSLog(@"###App is backgrounded. New event: %@", event);
        NSLog(@"Sending self-touch event");
        CGPoint point = CGPointMake(110,130);
        [self handleMouseEventAtPoint:point];
    }
}


- (void) playerItemDidReachEnd: (NSNotification *)notification
{
    [self.player seekToTime: kCMTimeZero];
    self.player.actionAtItemEnd = AVPlayerActionAtItemEndNone;
    [self.player play];
}

- (void)Start
{
    NSLog(@"###Start..");
    
    // establish connection
    if (OS_IsConnected())
    {
        OS_CloseConnection();
    }
    
//    sleep(1);

    if (OS_OpenConnection(IP_CONNECTION, IP_PORT) == 1)
    {
        NSLog(@"###Connection established.");
        
        // send login request
        FBEncode* encode = new FBEncode();
        encode->AddInt16(KEY_USER_COMMAND_ID, CMD_LOGIN);
        encode->AddStringANSI(KEY_DEVICE_ID, "ipod_test");
        encode->AddInt32(KEY_USER_REQUEST_ID, _request_id);
        
        if (OS_IsConnected())
        {
            [self SendDataToServer:encode];
            
            NSLog(@"###Sent request login");
        }
    }
}

-(void)ShowNotification
{
    if (UIApplication.sharedApplication.applicationState == UIApplicationStateActive)
    {
        NSLog(@"###DEBUG: App in on foreground");
    }
    else
    {
        NSLog(@"###DEBUG: App in background, send notification");
        UILocalNotification *notification = [[UILocalNotification alloc] init];
        notification.alertBody = @"iControl is restarting";
        notification.alertAction = @"Support now";
        [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
    }
}

- (void)SendDataToServer:(FBEncode*)encode
{
    int len = encode->GetBufferLength();
    BYTE* data = new BYTE[len];
    encode->GetBuffer(data);
    
//    OS_SendDataToServer(data, len, COMPRESS_BEFORE_SEND);
        OS_SendDataToServer(data, len, 0);
    
//    delete[] data;
}

- (void)Stop
{
    NSLog(@"Stop.");
//    [self.player pause];
    
    // close connection
    if (OS_IsConnected())
    {
        OS_CloseConnection();
    }
}

- (void)Update
{
    NSLog(@"Update with current step = %d", _currentStep);
}

- (int)GetCurrentStep
{
    return _currentStep;
}

- (void)HandleReceivedMessage:(BYTE*)data length:(int)length
{
//    NSLog(@"Hanlde received message");
    FBDecode* fb_decoder = new FBDecode();
    if (fb_decoder->Decode(data, length))
    {
        NSLog(@"HandleReceivedMessage: Decode Successfully");
    }
    else
    {
        NSLog(@"HandleReceivedMessage: Decode fail");
        SAFE_DEL(fb_decoder);
        return;
    }
    
    if (fb_decoder->HasKey(KEY_REQUEST_STATUS))
    {
//        NSLog(@"###hereee 1");
        int length;
        BYTE* value = fb_decoder->GetBinary(KEY_REQUEST_STATUS, length);
        FBDecode content_decode;
        bool result_t = content_decode.Decode(value, length);
        
        if (result_t)
        {
            // get request status and command id from server
            if (content_decode.HasKey(KEY_USER_COMMAND_ID))
            {
                _command_id = content_decode.GetInt32(KEY_USER_COMMAND_ID);
//                NSLog(@"### key 1");
            }
            if (content_decode.HasKey(KEY_USER_REQUEST_STATUS))
            {
                _response_status = content_decode.GetInt32(KEY_USER_REQUEST_STATUS);
//                NSLog(@"### key 2");
            }
            
            if (content_decode.HasKey(KEY_USER_REQUEST_ID))
            {
                _request_id = content_decode.GetInt32(KEY_USER_REQUEST_ID);
//                NSLog(@"### key 3");
            }
            NSLog(@"Received request id: %d", _request_id);
            NSLog(@"Received command id: %d", _command_id);
            
            //if (_command_id == 1)
                //_command_id = REPORT_CURRENT_STEP;
            
            // handle command request from server
            switch (_command_id)
            {
                case REPORT_CURRENT_STEP:
                    [self ReportCurrentStep];
                    break;
                case PERFORM_TOUCH_SCREEN:
                    [self PerformTouchScreen:fb_decoder];
                    break;
                case GO_HOME_SCREEN:
                    [self GoHomeScreen];
                    break;
                case TAKE_SCREEN_SHOT:
                    [self TakeScreenShot];
                    break;
                case REPORT_FRONTMOST_APP:
                    [self ReportFrontMostApp];
                    break;
                case EXIT:
                    [self Exit];
                    break;
                case DOUBLE_HOME_TOUCH:
                    [self simulatePressHomeEventx2];
                    break;
                default:
                    break;
            }
        }
//        NSLog(@"###hereeeee 2");
    }
    else
    {
        NSLog(@"###err! package does not contain key request status");
    }
    
    SAFE_DEL(fb_decoder);
}

- (void)ReportCurrentStep
{
    FBEncode* encode = new FBEncode();
    encode->AddInt16(KEY_USER_COMMAND_ID, CMD_LOGIN);
    encode->AddStringANSI(KEY_DEVICE_ID, "ipod_test");
    encode->AddInt32(KEY_USER_REQUEST_ID, _request_id);
    encode->AddInt64("current_step", _currentStep);
    
    [self SendDataToServer:encode];
}

- (void)PerformTouchScreen:(FBDecode*)fb_decode
{
    int x = fb_decode->GetInt32("position_x");
    int y = fb_decode->GetInt32("position_y");
    
    CGPoint point = CGPointMake(x,y);
    [self handleMouseEventAtPoint:point];
    
    double delayInSeconds = 0.6;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){ 
        [self handleMouseEventAtPoint:point];
    });

    
    FBEncode* encode = new FBEncode();
    encode->AddInt16(KEY_USER_COMMAND_ID, PERFORM_TOUCH_SCREEN);
    encode->AddStringANSI(KEY_DEVICE_ID, "ipod_test");
    encode->AddInt32(KEY_USER_REQUEST_ID, _request_id);
    
    [self SendDataToServer:encode];
}

- (void)GoHomeScreen
{
    // go to homescreen
    [self simulatePressHomeEvent];
    
    FBEncode* encode = new FBEncode();
    encode->AddInt16(KEY_USER_COMMAND_ID, GO_HOME_SCREEN);
    encode->AddStringANSI(KEY_DEVICE_ID, "ipod_test");
    encode->AddInt32(KEY_USER_REQUEST_ID, _request_id);
    
    [self SendDataToServer:encode];
}

- (void)TakeScreenShot
{
    // take screenshot
    UIImage* img = [_screenRecorder takeScreenShotAsUIImage];
    
    // convert image to byte array
    NSData *data = UIImagePNGRepresentation(img);
    NSUInteger len = [data length];
    BYTE* byteData = (BYTE*)malloc(len);
    memcpy(byteData, [data bytes], len);
    NSLog(@"Data length in int: %d", (int)len);
    
    FBEncode* encode = new FBEncode();
    encode->AddInt16(KEY_USER_COMMAND_ID, TAKE_SCREEN_SHOT);
    encode->AddStringANSI(KEY_DEVICE_ID, "ipod_test");
    encode->AddInt32(KEY_USER_REQUEST_ID, _request_id);
    
    if (len <= 1000000)
        encode->AddLongBinary("screen_shot", byteData, (int)len);
    
    [self SendDataToServer:encode];
}

- (void)ReportFrontMostApp
{
    NSString* app_name = [_recordVC GetFrontMostAppName];
    NSLog(@"Frontmost app name: %@", app_name);
    
    FBEncode* encode = new FBEncode();
    encode->AddInt16(KEY_USER_COMMAND_ID, REPORT_FRONTMOST_APP);
    encode->AddStringANSI(KEY_DEVICE_ID, "ipod_test");
    encode->AddInt32(KEY_USER_REQUEST_ID, _request_id);
    encode->AddStringANSI("app_name", [app_name UTF8String]);
    
    [self SendDataToServer:encode];
}

- (void)simulatePressHomeEvent
{
    NSLog(@"Simulate press home event");
    GSEventType type = _touchdown ? kGSEventMenuButtonDown : kGSEventMenuButtonUp;
    GSSendSimpleEvent(type, [_recordVC GetHomePort]);
    NSLog(@"Sent home event, touch_down = %d", _touchdown);
    
    _touchdown = !_touchdown;
    
    double delayInSeconds = 0.25;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        GSEventType type = _touchdown ? kGSEventMenuButtonDown : kGSEventMenuButtonUp;
        GSSendSimpleEvent(type, [_recordVC GetHomePort]);
        NSLog(@"Sent home event, touch_down = %d", _touchdown);
        _touchdown = !_touchdown;
    });
}

- (void)simulatePressHomeEventx2
{
    [self simulatePressHomeEvent];
    
    double delayInSeconds = 0.5;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self simulatePressHomeEvent];
    });
}

- (void)Exit
{
    exit(0);
}

- (void)handleMouseEventAtPoint:(CGPoint) point
{
    uint8_t gsTouchEvent[sizeof(GSEventRecord) + sizeof(GSHandInfo) + sizeof(GSPathInfo)];
    
    // structure of touch GSEvent
    struct GSTouchEvent
    {
        GSEventRecord record;
        GSHandInfo    handInfo;
    };
    
    struct GSTouchEvent *touchEvent = (struct GSTouchEvent *) &gsTouchEvent;
    
    bzero(touchEvent, sizeof(touchEvent));
    
    // set up GSEvent
    touchEvent->record.type = kGSEventHand;
    touchEvent->record.windowLocation = point;
    touchEvent->record.timestamp = GSCurrentEventTimestamp();
    touchEvent->record.infoSize = sizeof(GSHandInfo) + sizeof(GSPathInfo);
    
    touchEvent->handInfo.type = GetHandInfoType(_touchdown);
    touchEvent->handInfo.pathInfosCount = 1;
    
    bzero(&touchEvent->handInfo.pathInfos[0], sizeof(GSPathInfo));
    touchEvent->handInfo.pathInfos[0].pathIndex     = 1;
    touchEvent->handInfo.pathInfos[0].pathIdentity  = 2;
    touchEvent->handInfo.pathInfos[0].pathProximity = 1 ? 0x03 : 0x00;
    touchEvent->handInfo.pathInfos[0].pathLocation  = point;
    
    GSSendEvent((GSEventRecord*)touchEvent, [_recordVC GetFrontMostAppPort]);
    NSLog(@"Sent touch event, x = %f, y = %f, touch_down = %d", point.x, point.y, _touchdown);
    
    _touchdown = !_touchdown;
}

- (void)NotifyAppExit
{
//    NSLog(@"NotifyAppExit 1");
//    FBEncode* encode = new FBEncode();
//        NSLog(@"NotifyAppExit 2");
//    encode->AddInt16(KEY_USER_COMMAND_ID, NOTIFY_APP_EXIT);
//        NSLog(@"NotifyAppExit 3");
//    encode->AddStringANSI(KEY_DEVICE_ID, "ipod_test");
//        NSLog(@"NotifyAppExit 4");
//    encode->AddInt32(KEY_USER_REQUEST_ID, _request_id);
//        NSLog(@"NotifyAppExit 5");
//    
//    [self SendDataToServer:encode];
//        NSLog(@"NotifyAppExit 6");
}

static GSHandInfoType GetHandInfoType(bool touch_down)
{
    if (touch_down)
    {
        return (GSHandInfoType) kGSHandInfoTypeTouchDown;
    }
    else
    {
        return (GSHandInfoType) kGSHandInfoTypeTouchUp;
    }
}

@end
