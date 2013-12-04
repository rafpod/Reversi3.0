//
//  StatsDetailsScene.cpp
//  ReversiGL
//
//  Created by RafalP on 04.12.2013.
//
//

#include "StatsDetailsScene.h"
#include "BackgroundLayer.h"
#include "StatsDetailsLayer.h"

bool StatsDetailsScene::init(){
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
        StatsDetailsLayer *details = StatsDetailsLayer::create();
        
        this->addChild(bg, 0);
        this->addChild(details,1);
        
        
        return true;
    }
}
