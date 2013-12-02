//
//  CSRecordViewController.m
//  RecordMyScreen
//
//  Created by @coolstarorg on 12/29/12.
//  Copyright (c) 2012 CoolStar Organization. All rights reserved.
//

#import "CSRecordViewController.h"
#import <IOMobileFrameBuffer.h>
#include <sys/time.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <dlfcn.h>

#import "GSEvent.h"

#define SBSERVPATH  "/System/Library/PrivateFrameworks/SpringBoardServices.framework/SpringBoardServices"

@interface CSRecordViewController ()
{
    CSScreenRecorder *_screenRecorder;
    bool touch_down;
}

@property (nonatomic, strong) NSTimer *updateTimer;
@property (nonatomic) UIBackgroundTaskIdentifier backgroundTask;

@end

@implementation CSRecordViewController
- (id)init
{
    self = [super init];
    if (self) {
        _screenRecorder = [[CSScreenRecorder alloc] init];
        _screenRecorder.delegate = self;
        
        touch_down = true;
        
        self.tabBarItem = [[[UITabBarItem alloc] initWithTitle:NSLocalizedString(@"iControl", @"") image:[UIImage imageNamed:@"video"] tag:0] autorelease];
    }
    return self;
}

- (void)dealloc
{
    [_screenRecorder release];
    _screenRecorder = nil;
    
    [super dealloc];
}

- (void)loadView
{
    self.view = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height)] autorelease];
    UINavigationBar *navigationBar = [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 43)];
    navigationBar.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    [navigationBar pushNavigationItem:[[[UINavigationItem alloc] initWithTitle:NSLocalizedString(@"iControl", @"")] autorelease] animated:NO];
    [navigationBar setBarStyle:UIBarStyleBlack];
    [self.view addSubview:[navigationBar autorelease]];
    
    _recordbar = [[UIImageView alloc] initWithFrame:CGRectMake(0, 43, self.view.frame.size.width, isiPad?158:124)];
    [_recordbar setImage:[UIImage imageNamed:@"side_top"]];
    _recordbar.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleBottomMargin;
    [self.view addSubview:[_recordbar autorelease]];
    
    _statusLabel = [[UILabel alloc] initWithFrame:CGRectMake(85, 52, 150, 39)];
    [_statusLabel setText:NSLocalizedString(@"Ready", @"")];
    _statusLabel.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
    [_statusLabel setBackgroundColor:[UIColor clearColor]];
    [_statusLabel setTextColor:[UIColor whiteColor]];
    [_statusLabel setTextAlignment:UITextAlignmentCenter];
    [self.view addSubview:[_statusLabel autorelease]];
    
    UIImageView *lens = [[UIImageView alloc] initWithFrame:CGRectMake(0, _recordbar.frame.size.height + _recordbar.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height - (_recordbar.frame.size.height + _recordbar.frame.origin.y))];
    lens.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    lens.contentMode = UIViewContentModeCenter;
    [lens setImage:[UIImage imageNamed:@"lens"]];
    [self.view addSubview:[lens autorelease]];
}

#pragma mark - UI
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _record = [[[UISegmentedControl alloc] initWithItems:@[@"Start"]] autorelease];
    _record.momentary = YES;
    _record.segmentedControlStyle = UISegmentedControlStyleBar;
    _record.tintColor = [UIColor greenColor];
    [_record setAutoresizingMask:UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin];
    [_record addTarget:self action:@selector(record:) forControlEvents:UIControlEventValueChanged];
    
    _stop = [[[UISegmentedControl alloc] initWithItems:@[@"Stop"]] autorelease];
    _stop.momentary = YES;
    _stop.segmentedControlStyle = UISegmentedControlStyleBar;
    _stop.tintColor = [UIColor redColor];
    _stop.enabled = NO;
    [_stop setAutoresizingMask:UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin];
    [_stop addTarget:self action:@selector(stop:) forControlEvents:UIControlEventValueChanged];
    
    _progressView.hidden = YES;
    
    
    // Check for iPad for layout
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        _record.frame = CGRectMake(20, 103, 135, 33);
        _stop.frame = CGRectMake(170, 103, 135, 33);
    } else {
        _record.frame = CGRectMake(230, 150, 135, 33);
        _stop.frame = CGRectMake(400, 150, 135, 33);
    }
    
    
    [self.view addSubview:_record];
    [self.view addSubview:_stop];
    
    self.backgroundTask = UIBackgroundTaskInvalid;
    // Do any additional setup after loading the view from its nib.
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation == UIInterfaceOrientationPortrait);
    } else {
        return YES;
    }
}

#pragma mark - Starting / Stopping

- (void)record:(id)sender
{
    self.updateTimer = [NSTimer scheduledTimerWithTimeInterval:2.0
                                                        target:self
                                                      selector:@selector(touchScreen)
                                                      userInfo:nil
                                                       repeats:YES];
    
    
    self.backgroundTask = [[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler:^{
        NSLog(@"Background handler called. Not running background tasks anymore.");
        [[UIApplication sharedApplication] endBackgroundTask:self.backgroundTask];
        self.backgroundTask = UIBackgroundTaskInvalid;
    }];
    
    //[_screenRecorder takeScreenshot];
    
    /*
    // Update the UI
    _statusLabel.text = @"00:00:00";
    _stop.enabled = YES;
    _record.enabled = NO;
    
    // Remove the old video
    [[NSFileManager defaultManager] removeItemAtPath:[self inDocumentsDirectory:@"video.mp4"] error:nil];
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
	[dateFormatter setDateFormat:@"MM:dd:yyyy h:mm:ss a"];
	NSString *date = [dateFormatter stringFromDate:[NSDate date]];
	NSString *outName = [NSString stringWithFormat:@"%@.mp4", date];
	NSString *videoPath = [self inDocumentsDirectory:outName];
	[dateFormatter release];
    
    // Set the number of audio channels
    NSNumber *audioChannels = [[NSUserDefaults standardUserDefaults] objectForKey:@"channels"];
    NSNumber *sampleRate = [[NSUserDefaults standardUserDefaults] objectForKey:@"samplerate"];
    NSString *audioPath = [self inDocumentsDirectory:@"audio.caf"];
    
    _screenRecorder.videoOutPath = videoPath;
    _screenRecorder.audioOutPath = audioPath;
    _screenRecorder.numberOfAudioChannels = audioChannels;
    _screenRecorder.audioSampleRate = sampleRate;
    
    [_screenRecorder startRecordingScreen];
     */
}

- (void)takeScreenShot
{
    NSLog(@"Take screen shot");
    [_screenRecorder takeScreenshot];
}

- (void)touchScreen
{
    NSLog(@"Touch screen");
    
    CGPoint point = CGPointMake(280, 400);
    
    //[self handleMouseEventAtPoint:point];
    //[self handleMouseEventAtPoint2:point];
    
//    handleMouseEventAtPoint2(point, true, "org.coolstar.iControl");
//    usleep(1000);
//    handleMouseEventAtPoint2(point, false, "org.coolstar.iControl");
    
    [self handleMouseEventAtPoint:point];
//    [self handleMouseEventAtPoint:point];
//    return;
    
    double delayInSeconds = 0.25;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self handleMouseEventAtPoint:point];
        //[self handleMouseEventAtPoint2:point];
        //handleMouseEventAtPoint2(point, false, "org.coolstar.iControl");
    });
}

static mach_port_t getFrontMostAppPort()
{
    bool locked;
    bool passcode;
    mach_port_t *port;
    void *lib = dlopen(SBSERVPATH, RTLD_LAZY);
    int (*SBSSpringBoardServerPort)() = dlsym(lib, "SBSSpringBoardServerPort");
    void* (*SBGetScreenLockStatus)(mach_port_t* port, bool *lockStatus, bool *passcodeEnabled) = dlsym(lib, "SBGetScreenLockStatus");
    port = (mach_port_t *)SBSSpringBoardServerPort();
    dlclose(lib);
    SBGetScreenLockStatus(port, &locked, &passcode);
    void *(*SBFrontmostApplicationDisplayIdentifier)(mach_port_t *port, char *result) = dlsym(lib, "SBFrontmostApplicationDisplayIdentifier");
    char appId[256];
    memset(appId, 0, sizeof(appId));
    SBFrontmostApplicationDisplayIdentifier(port, appId);
    NSString * frontmostApp=[NSString stringWithFormat:@"%s",appId];

    NSLog(@"app id %s", appId);

    if([frontmostApp length] == 0 || locked)
    {
        NSLog(@"###DEBUG 1");
        //return GSGetPurpleSystemEventPort();
        return GetHomeScreenPort();
    }
    else
    {
        NSLog(@"###DEBUG 2");
        return GSCopyPurpleNamedPort(appId);
    }
}

static mach_port_t GetAppPort(const char* app_bundle)
{
    return GSCopyPurpleNamedPort(app_bundle);
}

static mach_port_t GetHomeScreenPort()
{
    return GSCopyPurpleNamedPort("com.apple.springboard");
}

-(void) handleMouseEventAtPoint:(CGPoint) point
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
    
    touchEvent->handInfo.type = getHandInfoType(touch_down);
    touchEvent->handInfo.pathInfosCount = 1;
    
    bzero(&touchEvent->handInfo.pathInfos[0], sizeof(GSPathInfo));
    touchEvent->handInfo.pathInfos[0].pathIndex     = 1;
    touchEvent->handInfo.pathInfos[0].pathIdentity  = 2;
    touchEvent->handInfo.pathInfos[0].pathProximity = 1 ? 0x03 : 0x00;
    touchEvent->handInfo.pathInfos[0].pathLocation  = point;
    
    GSSendEvent((GSEventRecord*)touchEvent, getFrontMostAppPort());
    //GSSendEvent((GSEventRecord*)touchEvent, GetAppPort("org.coolstar.iControl"));
    
    NSLog(@"Sent touch event, touch_down = %d", touch_down);
    
    touch_down = !touch_down;
}
//
//void handleMouseEventAtPoint2(CGPoint point, bool touch_down, const char* bundle)
//{
//    uint8_t gsTouchEvent[sizeof(GSEventRecord) + sizeof(GSHandInfo) + sizeof(GSPathInfo)];
//
//    
//    
//    // structure of touch GSEvent
//    struct GSTouchEvent
//    {
//        GSEventRecord record;
//        GSHandInfo    handInfo;
//    };
//    
//    struct GSTouchEvent *touchEvent = (struct GSTouchEvent *) &gsTouchEvent;
//    
//    bzero(touchEvent, sizeof(touchEvent));
//    
//    /*
//     typedef struct GSEventRecord {
//     GSEventType type; // 0x8
//     GSEventSubType subtype;	// 0xC
//     CGPoint location; 	// 0x10
//     CGPoint windowLocation;	// 0x18
//     int windowContextId;	// 0x20
//     uint64_t timestamp;	// 0x24, from mach_absolute_time
//     GSWindowRef window;	// 0x2C
//     GSEventFlags flags;	// 0x30
//     unsigned senderPID;	// 0x34
//     CFIndex infoSize; // 0x38
//     } GSEventRecord;
//     */
//    
//    // set up GSEvent
//    touchEvent->record.type = kGSEventHand;
//    touchEvent->record.subtype = kGSEventSubTypeUnknown; // lava
//    touchEvent->record.location = point;
//    touchEvent->record.windowLocation = point;
//    touchEvent->record.timestamp = GSCurrentEventTimestamp();
//    touchEvent->record.infoSize = sizeof(GSHandInfo) + sizeof(GSPathInfo);
//    touchEvent->handInfo.type = getHandInfoType(touch_down);
//    touchEvent->handInfo.pathInfosCount = 1;
//    bzero(&touchEvent->handInfo.pathInfos[0], sizeof(GSPathInfo));
//    touchEvent->handInfo.pathInfos[0].pathIndex     = 1;
//    touchEvent->handInfo.pathInfos[0].pathIdentity  = 2;
//    touchEvent->handInfo.pathInfos[0].pathProximity = 1 ? 0x03 : 0x00;
//    touchEvent->handInfo.pathInfos[0].pathLocation  = point;
//    
//    GSSendEvent((GSEventRecord*)touchEvent, getFrontMostAppPort());
//    //GSSendEvent((GSEventRecord*)touchEvent, GetAppPort("org.coolstar.iControl"));
//    //NSLog(@"app bundle %s", bundle);
//    //GSSendEvent((GSEventRecord*)touchEvent, GetAppPort(bundle));
//    
//    
//    NSLog(@"Sent touch event, touch_down = %d", touch_down);
//    
//    touch_down = !touch_down;
//}
//

static GSHandInfoType getHandInfoType(bool touch_down)
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


- (void)stop:(id)sender
{
    return;
    //[_screenRecorder stopRecordingScreen];
}

- (void)screenRecorderDidStopRecording:(CSScreenRecorder *)recorder
{
    // Disable the stop button
    _stop.enabled = NO;
    
    // Announce Encoding will begin
    _statusLabel.text = @"Encoding Movie...";
    
    // Show progress view
    _progressView.hidden = NO;

    // Update the UI for another round
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
    dispatch_async(queue, ^{
        dispatch_async(dispatch_get_main_queue(), ^{
            _statusLabel.text = @"Ready";
            _progressView.hidden = YES;
            _record.enabled = YES;
        });
    });
}

- (void)screenRecorder:(CSScreenRecorder *)recorder recordingTimeChanged:(NSTimeInterval)recordingInterval
{
    // get an NSDate object from NSTimeInterval
    NSDate *timerDate = [NSDate dateWithTimeIntervalSince1970:recordingInterval];
    
    // Make a date formatter (Possibly reuse instead of creating each time)
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"HH:mm:ss"];
    [dateFormatter setTimeZone:[NSTimeZone timeZoneForSecondsFromGMT:0.0]];
    
    // Set the current time since recording began
    NSString *timeString = [dateFormatter stringFromDate:timerDate];
    _statusLabel.text = timeString;
    [dateFormatter release];
}

// Stubs. Do Error handling shit here.
- (void)screenRecorder:(CSScreenRecorder *)recorder videoContextSetupFailedWithError:(NSError *)error
{
    
}

- (void)screenRecorder:(CSScreenRecorder *)recorder audioRecorderSetupFailedWithError:(NSError *)error
{
    
}

- (void)screenRecorder:(CSScreenRecorder *)recorder audioSessionSetupFailedWithError:(NSError *)error
{
    
}
#pragma mark - NSFileManager Methods

- (NSString *)inDocumentsDirectory:(NSString *)path {
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	return [documentsDirectory stringByAppendingPathComponent:path];
}

@end
