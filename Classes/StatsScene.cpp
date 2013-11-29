//
//  StatsScene.cpp
//  ReversiGL
//
//  Created by RafalP on 21.11.2013.
//
//

#include "StatsScene.h"
#include "BackgroundLayer.h"
#include "StatsResultsLayer.h"
#include "StatsDetailsLayer.h"
#include "cocos2d.h"

using namespace cocos2d;

bool StatsScene::init(){
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
        StatsResultsLayer *stats = StatsResultsLayer::create();
        
        StatsDetailsLayer *details = StatsDetailsLayer::create();
        
        this->addChild(bg, 0);
        //this->addChild(stats,1);
        this->addChild(details,1);
        
        
        return true;
    }
}
