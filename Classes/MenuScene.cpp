//
//  MenuScene.cpp
//  ReversiGL
//
//  Created by RafalP on 07.11.2013.
//
//

#include "MenuScene.h"
#include "BackgroundLayer.h"
#include "BgLayer.h"
#include "MenuButtonsLayer.h"

using namespace cocos2d;

bool MenuScene::init(){
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
        //BgLayer *bg = BgLayer::createLayer("splash_background.png");
        MenuButtonsLayer *mBL = MenuButtonsLayer::create();
        this->addChild(bg, 0);
        this->addChild(mBL,1);
        
        return true;
    }
}
