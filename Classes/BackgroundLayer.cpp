//
//  BackgroundLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 18.10.2013.
//
//

#include "BackgroundLayer.h"
#include "cocos2d.h"
#include "VisibleRect.h"



bool BackgroundLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        
        //bottom left
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCLOG("(Director VisibleSize)WidthVisibleSize is: %f and heightVisibleSize is: %f", visibleSize.width, visibleSize.height);
        CCLOG("(Director Origin)WidthOrigin is: %f and heightOrigin is: %f", origin.x, origin.y);
        CCLOG("(Director WinSize)WidthWinSize is: %f and heightWinSize is: %f", winSize.width, winSize.height);
        
       // CCPoint autoScale = CCPointMake(CCEGLView::sharedOpenGLView()->getScaleX(), CCEGLView::sharedOpenGLView()->getScaleY());
        //CCLOG("(AutoScale)ScaleX is: %f and ScaleY is: %f", autoScale.x, autoScale.y);
        
        bool othelloIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("othelloIsEnabled",0);
        TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
        CCLOG("platform %i", platform);
        
                
        //this->batchNode = CCSpriteBatchNode::create("background.pvr.ccz");
        //this->addChild(batchNode);
        
        //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background.plist");
        
        if (CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height> 960 && othelloIsEnabled) {
            if (platform ==kTargetIphone || platform == kTargetIpad) {
                //bgSprite = CCSprite::createWithSpriteFrameName("bg.jpg");
                bgSprite = CCSprite::create("bg.jpg");
            }else{
                //bgSprite = CCSprite::createWithSpriteFrameName("bg_android.jpg");
                bgSprite = CCSprite::create("bg_android.jpg");
            }
        }else{
           //bgSprite = CCSprite::createWithSpriteFrameName("bg.jpg");
            bgSprite = CCSprite::create("bg.jpg");
        }
        
        //bgSprite = CCSprite::createWithSpriteFrameName("bg.jpg");
        
               
        float scaleY = 1;
        float scaleX = 1;
        
        if(visibleSize.height > bgSprite->getContentSize().height){
            
            scaleY = bgSprite->getContentSize().height/visibleSize.height;
        }
        
        if(visibleSize.height < bgSprite->getContentSize().height){
            
        
            scaleY = visibleSize.height/bgSprite->getContentSize().height;
            

        }
        
        if (visibleSize.width < bgSprite->getContentSize().width) {
            scaleX = visibleSize.width/bgSprite->getContentSize().width;
        }
        
        if (visibleSize.width > bgSprite->getContentSize().width) {
            scaleX = bgSprite->getContentSize().width/visibleSize.width;
        }
        
        
        bgSprite->setScaleY(scaleY);
        bgSprite->setScaleX(scaleX);
       
        
        CCLOG("(ContentSizeBackground)X is: %f and Y is: %f", bgSprite->getContentSize().width, bgSprite->getContentSize().height);
        
        
       // CCPoint mm =CCPointMake(bgSprite->getContentSize().width/2, bgSprite->getContentSize().height/2);
        //bgSprite->setAnchorPoint(CCPointMake(0.5, 0.5));
        
        bgSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        
        //this->batchNode->addChild(bgSprite, 0);
        this->addChild(bgSprite,0);
        
        return true;
    }
}
