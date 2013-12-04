#import <UIKit/UIKit.h>

@class RootViewController;

/*
@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}
*/


 //Nowe
@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController *viewController;
}

-(void) orientationDidChanged:(NSNotification*)notification;

//@property (nonatomic, retain) UIWindow *window;
//@property (nonatomic, retain) RootViewController *viewController;

@end

