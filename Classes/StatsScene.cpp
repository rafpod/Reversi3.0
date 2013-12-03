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

#define MAIN_LAYER 0
#define DETAILS_LAYER 1


bool StatsScene::init(){
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
        StatsResultsLayer *stats = StatsResultsLayer::create();
        
        //StatsDetailsLayer *details = StatsDetailsLayer::create();
        
        this->addChild(bg, 0);
        this->addChild(stats,1);
        //this->addChild(details,2);
        
        
        return true;
    }
}

bool StatsScene::init(cocos2d::CCLayer *layer){
    
    if (!CCScene::init()) {
        return false;
    }else{
        
        BackgroundLayer *bg = BackgroundLayer::create();
        
        int tag = (int)layer->getTag();
        
        if (tag == MAIN_LAYER) {
            layer = StatsResultsLayer::create();
        }else{
            layer = StatsDetailsLayer::create();
        }
        //StatsDetailsLayer *details = StatsDetailsLayer::create();
        
        this->addChild(bg, 0);
        this->addChild(layer,1);
        
        
        return true;
    }

}

StatsScene* StatsScene::create(CCLayer* layer){
    
    StatsScene * scene = new StatsScene();
    if (scene && scene->init(layer)) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return NULL;
    
}

