//
//  GameScene.cpp
//  ReversiGL
//
//  Created by RafalP on 18.10.2013.
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"
#include "BoardLayer.h"

using namespace cocos2d;

bool GameScene::init(){
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
       BoardLayer *board = BoardLayer::create();
        
        this->addChild(bg, 0);
        this->addChild(board,1);
             
        return true;
    }
}

GameScene::~GameScene(){
    CCLOG("DESTRUKCJA SCENY");
}
