//
//  StatsDetailsLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 27.11.2013.
//
//

#include "StatsDetailsLayer.h"
#include "VisibleRect.h"

bool StatsDetailsLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{
        
        visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
        designSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
        
        langManager = LanguageManager::create();
        
        this->setDetailsOffsets();
        
        this->createItems();
        
        this->setItemsPosition();
        
        this->addItemsToLayer();

        
        return true;
    }
}

void StatsDetailsLayer::createItems(){
    
    this->createHeader();
    
    wonLabel = CCLabelTTF::create("Won", "Georgia", 26);
    wonLabel->setColor(ccc3(0, 0, 0));
    
    lostLabel = CCLabelTTF::create("Lost", "Georgia", 26);
    lostLabel->setColor(ccc3(0, 0, 0));
    
    tiedLabel = CCLabelTTF::create("Tied", "Georgia", 26);
    tiedLabel->setColor(ccc3(0, 0, 0));
    
    allLabelH = CCLabelTTF::create("All", "Georgia", 26);
    allLabelH->setColor(ccc3(0, 0, 0));
    
    
    statsHeaderMenu = CCMenu::create(backButton, NULL);
    
}

void StatsDetailsLayer::setItemsPosition(){
    
    this->setHeaderPosition();
    
    wonLabel->setPosition(ccp(VisibleRect::center().x - 80, headerLabel->getPositionY() - labelOffFromHeader));
    
    statsHeaderMenu->setPosition(CCPointZero);
    
}

void StatsDetailsLayer::addItemsToLayer(){
    
    this->addChild(headerLabel);
    this->addChild(lineHeader);
    
    this->addChild(wonLabel);
    
    this->addChild(statsHeaderMenu);
}


void StatsDetailsLayer::createHeader(){
    headerLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS)->getCString(), "Georgia", 32);
    headerLabel->setColor(ccc3(0, 0, 0));
    
    lineHeader = CCSprite::create("marker_header.png");
    
    backButton = CCMenuItemImage::create("button_back_0.png", "button_back_1.png", "button_back_0.png", this, menu_selector(StatsDetailsLayer::backBtnCallback));
}

void StatsDetailsLayer::setHeaderPosition(){
    
    headerLabel->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - labelOffFromTop));
    
    lineHeader->setPosition(ccp(VisibleRect::center().x, headerLabel->boundingBox().origin.y - lineHeader->getContentSize().height/2));
    
    backButton->setPosition(ccp(lineHeader->boundingBox().origin.x, lineHeader->getPositionY()));
}

void StatsDetailsLayer::keyBackClicked(){
    
}

void StatsDetailsLayer::backBtnCallback(cocos2d::CCObject *pSender){
    
}

void StatsDetailsLayer::countStats(){
    
}

void StatsDetailsLayer::setDetailsOffsets(){
    
    int offFromTop = designSize.height <= 960 ? 80:90;
    int offFromHeader = designSize.height <=960 ? 100:110;
    
    this->labelOffFromTop = visibleSize.height/designSize.height * offFromTop;
    this->labelOffFromHeader = visibleSize.height/designSize.height * offFromHeader;
}


