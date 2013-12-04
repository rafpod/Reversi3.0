#import "AppController.h"
#import "EAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the EAGLView
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGB565
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    cocos2d::CCApplication::sharedApplication()->run();
    
    
    //NOWA
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationDidChanged:) name:@"UIDeviceOrientationDidChangeNotification" object:nil];
    
    /*//2 NOWA
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleDidChangeStatusBarOrientationNotification:)
        name:UIApplicationDidChangeStatusBarOrientationNotification object:nil];*/
    

    return YES;
}

//NOWA
-(void) orientationDidChanged:(NSNotification*)notification
{
    
    UIDeviceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
    if (orientation == UIDeviceOrientationPortrait || orientation == UIDeviceOrientationPortraitUpsideDown)
    {
        
        cocos2d::CCSize s = cocos2d::CCEGLView::sharedOpenGLView()->getFrameSize();
        NSLog(@"TEST ORIENT %d ii %f x %f",[[UIDevice currentDevice] orientation], s.width, s.height);

        if (s.width < s.height)
            cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize(s.width, s.height);
        else
            cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize(s.height, s.width);
        
        //cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionNoBorder);
    }
    else if (orientation == UIDeviceOrientationLandscapeLeft || orientation == UIDeviceOrientationLandscapeRight)
    {
        cocos2d::CCSize s = cocos2d::CCEGLView::sharedOpenGLView()->getFrameSize();
        NSLog(@"TEST ORIENT2 %d ii %f x %f",[[UIDevice currentDevice] orientation], s.width, s.height);

        if (s.width > s.height)
            cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize(s.width, s.height);
        else
            cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize(s.height, s.width);
        //cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionNoBorder);
    }
    
    
    //cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize(700,1200);
    
NSLog(@"current orientation %d ii %f",[[UIDevice currentDevice] orientation], cocos2d::CCEGLView::sharedOpenGLView()->getFrameSize().width);
    
}
//KONIEC NOWEJ

//DRUGA NOWA
- (void)handleDidChangeStatusBarOrientationNotification:(NSNotification *)notification; {
    //NSLog("The orientation is %", [notification.userInfo objectForKey: UIApplicationStatusBarOrientationUserInfoKey]);
    cocos2d::CCDirector* director = cocos2d::CCDirector::sharedDirector();
    cocos2d::CCEGLView* eglView = director->getOpenGLView();
    
    AppDelegate::onOrientationChange(UIInterfaceOrientationIsLandscape(UIApplication.sharedApplication.statusBarOrientation), eglView->getFrameSize().width, eglView->getFrameSize().height);
    
}
//KONIEC NOWEJ

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
