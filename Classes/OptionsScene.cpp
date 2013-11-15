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

using namespace cocos2d;

bool OptionsScene::init(){
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
        //BgLayer *bg = BgLayer::createLayer("splash_background.png");
        OptionsButtonsLayer *opBtn = OptionsButtonsLayer::create();
        this->addChild(bg, 0);
        this->addChild(opBtn,1);
        
        return true;
    }
}
