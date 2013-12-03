//
//  StatsHeaderLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 27.11.2013.
//
//

#include "StatsHeaderLayer.h"
#include "VisibleRect.h"

bool StatsHeaderLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{
        
        int offFromTop = designSize.height <= 960 ? 80:90;        
        
        this->labelOffFromTop = visibleSize.height/designSize.height * offFromTop;
        
        
        return true;
    }

}

void StatsHeaderLayer::createItems(){
    headerLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS)->getCString(), "Georgia", 32);
    headerLabel->setColor(ccc3(0, 0, 0));
    
    lineHeader = CCSprite::create("marker_header.png");
    
    backButton = CCMenuItemImage::create("button_back_0.png", "button_back_1.png", "button_back_0.png", this, menu_selector(StatsHeaderLayer::backBtnCallback));

}

void StatsHeaderLayer::setItemsPosition(){
    headerLabel->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - labelOffFromTop));
    
    lineHeader->setPosition(ccp(VisibleRect::center().x, headerLabel->boundingBox().origin.y - lineHeader->getContentSize().height/2));
    
    backButton->setPosition(ccp(lineHeader->boundingBox().origin.x, lineHeader->getPositionY()));
}

void StatsHeaderLayer::addItemsToLayer(){
    
}

void StatsHeaderLayer::keyBackClicked(){
    
}

void StatsHeaderLayer::backBtnCallback(cocos2d::CCObject *pSender){
    
}