#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "AppMacros.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
        
    //PORTRAIT SIZES
    //CCSize designSize = CCSizeMake(1536, 2548);
    //CCSize designSize = CCSizeMake(1280, 1920);
    CCSize designSize = CCSizeMake(640, 960);
    CCSize resourceSize = CCSizeMake(320, 480);
   
    //Real screen size in pixels
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();    
    
    CCLOG("(CCEGLView FrameSize)WidthScreenSize is: %f and heightScreenSize is: %f", screenSize.width, screenSize.height);
    
    std::vector<std::string> resDirOrders;
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    
    std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), "Test_Res");
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

    /*
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
         //FIRST OPTION PORTRAIT
         if (screenSize.height > 1136)
         {
             //resourceSize = CCSizeMake(2048, 1536);
             resourceSize = CCSizeMake(1536, 2048);
             resDirOrders.push_back("Group_I/1536x2048-ipadhd");
             resDirOrders.push_back("Group_I");
         }
         else if (screenSize.height > 1024)
         {
             //resourceSize = CCSizeMake(1536, 768);
             resourceSize = CCSizeMake(640, 1136);
             resDirOrders.push_back("Group_D/640x1136-iphone5");
             resDirOrders.push_back("Group_D");
         }
         else if (screenSize.height > 960)
         {
             //resourceSize = CCSizeMake(1536, 768);
             resourceSize = CCSizeMake(768, 1024);
             resDirOrders.push_back("Group_E/768x1024-ipad");
             resDirOrders.push_back("Group_E");
         }else if (screenSize.height > 480)
         {
             //resourceSize = CCSizeMake(960, 640);
             resourceSize = CCSizeMake(640, 960);
             resDirOrders.push_back("Group_D/640x960-iphonehd");
             resDirOrders.push_back("Group_D");
         }
         else
         {
             resDirOrders.push_back("Group_B/320x480-iphone");
             resDirOrders.push_back("Group_B");
         }

    }
    else if (platform == kTargetAndroid || platform == kTargetWindows)
    {
     
        if (screenSize.height > 2048)
        {
            if(screenSize.width>1536){
                resourceSize = CCSizeMake(1600, 2560);
                resDirOrders.push_back("Group_I/1600x2560");
            }else{
                resourceSize = CCSizeMake(1536, 2560);
                resDirOrders.push_back("Group_I/1536x2560");
            }
            
            resDirOrders.push_back("Group_I");
            
            
        }
        else if (screenSize.height > 1920)
        {
            resourceSize = CCSizeMake(1536, 2048);
            resDirOrders.push_back("Group_I/1536x2048-ipadhd");
            resDirOrders.push_back("Group_I");
        }
        else if(screenSize.height > 1440)
        {
            if(screenSize.width > 1200){
                resourceSize = CCSizeMake(1280, 1920);
                resDirOrders.push_back("Group_H/1280x1920");
            }else if (screenSize.width > 1080){
                resourceSize = CCSizeMake(1200, 1920);
                resDirOrders.push_back("Group_H/1280x1920");
            }else{
                resourceSize = CCSizeMake(1080, 1920);
                resDirOrders.push_back("Group_H/1080x1920");
            }
            
            resDirOrders.push_back("Group_H");
        }
        else if(screenSize.height>1280)
        {
            resourceSize = CCSizeMake(900, 1440);
            resDirOrders.push_back("Group_G/900x1440");
            resDirOrders.push_back("Group_G");
        }
        else if(screenSize.height > 1024)
        {
            if(screenSize.width > 768){
                resourceSize = CCSizeMake(800, 1280);
                resDirOrders.push_back("Group_F/800x1280");
            }else if (screenSize.width > 720){
                resourceSize = CCSizeMake(768, 1280);
                resDirOrders.push_back("Group_F/768x1280");
            }else{
                resourceSize = CCSizeMake(720, 1280);
                resDirOrders.push_back("Group_F/720x1280");
            }
            
            resDirOrders.push_back("Group_F");
        }
        else if (screenSize.height > 960)
        {
            if (screenSize.width > 600) {
                resourceSize = CCSizeMake(768, 1024);
                resDirOrders.push_back("Group_E/768x1024-ipad");
            }else{
                resourceSize = CCSizeMake(600, 1024);
                resDirOrders.push_back("Group_E/600x1024");
            }
            
            
            resDirOrders.push_back("Group_E");
        }
        else if (screenSize.height > 854)
        {
            if(screenSize.width > 540){
                resourceSize = CCSizeMake(640, 960);
                resDirOrders.push_back("Group_D/640x960-iphonehd");
            }else{
                resourceSize = CCSizeMake(540, 960);
                resDirOrders.push_back("Group_D/540x960");
            }
            
            resDirOrders.push_back("Group_D");
        }
        else if (screenSize.height > 800)
        {
            resourceSize = CCSizeMake(480, 854);
            resDirOrders.push_back("Group_C/480x854");
            resDirOrders.push_back("Group_C");
        }
        else if (screenSize.height > 640)
        {
            resourceSize = CCSizeMake(480, 800);
            resDirOrders.push_back("Group_C/480x800");
            resDirOrders.push_back("Group_C");            
        }
        else if (screenSize.height > 480)
        {
            resourceSize = CCSizeMake(360, 640);
            resDirOrders.push_back("Group_B/360x640");
            resDirOrders.push_back("Group_B");
        }
        else if (screenSize.height > 400)
        {
            resourceSize = CCSizeMake(320, 480);
            resDirOrders.push_back("Group_B/320x480-iphone");
            resDirOrders.push_back("Group_B");
        }
        else if (screenSize.height > 320)
        {
            resourceSize = CCSizeMake(240, 400);
            resDirOrders.push_back("Group_A/240x400");
            resDirOrders.push_back("Group_A");
        }
        else
        {
            resourceSize = CCSizeMake(240, 320);
            resDirOrders.push_back("Group_A/240x320");
            resDirOrders.push_back("Group_A");
        }
        
    }
*/
  
    /* //FIRST OPTION PORTRAIT
    if (screenSize.height > 960)
    {
        //resourceSize = CCSizeMake(2048, 1536);
        resourceSize = CCSizeMake(1280, 1920);
        //resDirOrders.push_back("Group_H/1280x1920");
        //resDirOrders.push_back("Group_H");
        resDirOrders.push_back("1280x1920");
    }
    else if (screenSize.height > 480)
    {
        //resourceSize = CCSizeMake(960, 640);
        resourceSize = CCSizeMake(640, 960);
        //resDirOrders.push_back("Group_D/640x960-iphonehd");
        //resDirOrders.push_back("Group_D");
        resDirOrders.push_back("640x960-iphonehd");
    }
    else
    {
        //resDirOrders.push_back("Group_B/320x480-iphone");
        //resDirOrders.push_back("Group_B");
        resDirOrders.push_back("320x480-iphone");
    }
    */
    
    
    //SECOND OPTION PORTRAIT
    if (screenSize.height > 480)
    {
        //resourceSize = CCSizeMake(960, 640);
        resourceSize = CCSizeMake(640, 960);
        //resDirOrders.push_back("Group_D/640x960-iphonehd");
        //resDirOrders.push_back("Group_D");
        resDirOrders.push_back("640x960-iphonehd/wood");
        resDirOrders.push_back("640x960-iphonehd/othello");
        resDirOrders.push_back("640x960-iphonehd");
    }
    else
    {
        //resDirOrders.push_back("Group_B/320x480-iphone");
        //resDirOrders.push_back("Group_B");
        resDirOrders.push_back("320x480-iphone/wood");
        resDirOrders.push_back("320x480-iphonehd/othello");
        resDirOrders.push_back("320x480-iphone");
    }
    
     
    
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
   
    
    
    //pDirector->setContentScaleFactor(MIN(resourceSize.width/designSize.width,resourceSize.height/designSize.height));
    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
   // CCScene *pScene = HelloWorld::scene();
    GameScene *pScene = GameScene::create();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
   
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
