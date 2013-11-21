//
//  OptionsScene.cpp
//  ReversiGL
//
//  Created by RafalP on 13.11.2013.
//
//

#include "OptionsScene.h"
#include "BackgroundLayer.h"
#include "OptionsButtonsLayer.h"
#include "CCScrollView.h"

using namespace cocos2d;
using namespace extension;

bool OptionsScene::init(){
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
        //BgLayer *bg = BgLayer::createLayer("splash_background.png");
        OptionsButtonsLayer *opBtn = OptionsButtonsLayer::create();
        this->addChild(bg, 0);
        
        /*
        CCScrollView* scrollView;
         scrollView = CCScrollView::create();
        scrollView->retain();
        scrollView->setContentSize(opBtn->getContentSize());
        scrollView->setDirection(kCCScrollViewDirectionVertical);
        scrollView->setContentOffset(CCPointZero, false);
        
        this->addChild(scrollView,1);
        
        //scrollView->setPosition(scrollView->getParent()->convertToNodeSpace(worldPosition));
        scrollView->setContainer(opBtn);
        */
        
        this->addChild(opBtn,1);
        
        return true;
    }
}
