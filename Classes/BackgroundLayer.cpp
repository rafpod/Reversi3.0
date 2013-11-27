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
        
        CCPoint autoScale = CCPointMake(CCEGLView::sharedOpenGLView()->getScaleX(), CCEGLView::sharedOpenGLView()->getScaleY());
        //CCLOG("(AutoScale)ScaleX is: %f and ScaleY is: %f", autoScale.x, autoScale.y);
        
        bool othelloIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("othelloIsEnabled",0);
        
        if (CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height> 960 && othelloIsEnabled) {
            bgSprite = CCSprite::create("bg_android.jpg");
        }else{
            bgSprite = CCSprite::create("bg.jpg");
        }
        
               
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
                
        this->addChild(bgSprite);
        
        
        //CCPoint leftBottom = VisibleRect::leftBottom();
        CCRect visRect = VisibleRect::getVisibleRect();
        /*
        CCLOG("(VisibleRect)LeftBottom x: %f and leftBottom y: %f",VisibleRect::leftBottom().x,VisibleRect::rightBottom().y);
        CCLOG("(VisibleRect)rightBottom x: %f and rightBottom y: %f",VisibleRect::rightBottom().x,VisibleRect::rightBottom().y);
        
        CCLOG("(VisibleRect)leftTop x: %f and rightTop y: %f",VisibleRect::leftTop().x,VisibleRect::leftTop().y);
        CCLOG("(VisibleRect)rightTop x: %f and rightTop y: %f",VisibleRect::rightTop().x,VisibleRect::rightTop().y);
        
        CCLOG("(VisibleRect)left x: %f and left y: %f",VisibleRect::left().x,VisibleRect::left().y);
        CCLOG("(VisibleRect)right x: %f and right y: %f",VisibleRect::right().x,VisibleRect::right().y);
        
        CCLOG("(VisibleRect)bottom x: %f and bottom y: %f",VisibleRect::bottom().x,VisibleRect::bottom().y);
        CCLOG("(VisibleRect)top x: %f and top y: %f",VisibleRect::top().x,VisibleRect::top().y);
        
        CCLOG("(VisibleRect)center x: %f and center y: %f",VisibleRect::center().x,VisibleRect::center().y);
        
        CCLOG("(VisRect)VisRect width: %f and VisRect height: %f and origin x: %f and origin y: %f",visRect.size.width, visRect.size.height, visRect.origin.x, visRect.origin.y);
        */
        return true;
    }
}
