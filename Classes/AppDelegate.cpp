#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "AppMacros.h"
#include "OptionButtonDefinitions.h"
#include "ResourcesDef.h"

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
    
   /* CCSize designSize = CCSizeMake(1536, 2048);
    CCSize resourceSize = CCSizeMake(768, 1024);*/
    
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
    
    bool othelloIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("othelloIsEnabled",WOOD_SKIN_BTN_TAG);
    

    //SECOND OPTION PORTRAIT
    if (screenSize.height > 480)
    {
        //resourceSize = CCSizeMake(960, 640);
        resourceSize = CCSizeMake(640, 960);
        //resDirOrders.push_back("Group_D/640x960-iphonehd");
        //resDirOrders.push_back("Group_D");        
        
        if (othelloIsEnabled) {
            resDirOrders.push_back(NORMAL_RES_OTHELLO);
            //resDirOrders.push_back(NORMAL_RES_WOOD);
            
        }else{
            resDirOrders.push_back(NORMAL_RES_WOOD);
            //resDirOrders.push_back(NORMAL_RES_OTHELLO);
        }
        
        resDirOrders.push_back(NORMAL_RES_MAIN);
        
    }
    else
    {
        //resDirOrders.push_back("Group_B/320x480-iphone");
        //resDirOrders.push_back("Group_B");
        
        if (othelloIsEnabled) {
            resDirOrders.push_back(SMALL_RES_OTHELLO);
            resDirOrders.push_back(SMALL_RES_WOOD);
        }else{
            resDirOrders.push_back(SMALL_RES_WOOD);
            resDirOrders.push_back(SMALL_RES_OTHELLO);
        }
        
        resDirOrders.push_back(SMALL_RES_MAIN);
        
    }
    //CCLOG("SKIN1: %i", othelloIsEnabled);
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);   

/*
    //THIRD OPTION PORTRAIT
    if (screenSize.height > 1024)
    {
        //resourceSize = CCSizeMake(960, 640);
        resourceSize = CCSizeMake(1536, 2048);
        //resDirOrders.push_back("Group_D/640x960-iphonehd");
        //resDirOrders.push_back("Group_D");
        
        if (othelloIsEnabled) {
            resDirOrders.push_back(NORMAL_RES_OTHELLO);
            //resDirOrders.push_back(NORMAL_RES_WOOD);
            
        }else{
            resDirOrders.push_back(NORMAL_RES_WOOD);
            //resDirOrders.push_back(NORMAL_RES_OTHELLO);
        }
        
        resDirOrders.push_back(NORMAL_RES_MAIN);
        
    }
    else
    {
        //resDirOrders.push_back("Group_B/320x480-iphone");
        //resDirOrders.push_back("Group_B");
        
        if (othelloIsEnabled) {
            resDirOrders.push_back(SMALL_RES_OTHELLO);
            resDirOrders.push_back(SMALL_RES_WOOD);
        }else{
            resDirOrders.push_back(SMALL_RES_WOOD);
            resDirOrders.push_back(SMALL_RES_OTHELLO);
        }
        
        resDirOrders.push_back(SMALL_RES_MAIN);
        
    }
    //CCLOG("SKIN1: %i", othelloIsEnabled);
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
 */
    //pDirector->setContentScaleFactor(MIN(resourceSize.width/designSize.width,resourceSize.height/designSize.height));
    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

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
