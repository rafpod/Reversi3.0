//
//  StatsResultsLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 21.11.2013.
//
//

#include "StatsResultsLayer.h"
#include "MenuScene.h"
#include "VisibleRect.h"

USING_NS_CC;

#define STATS_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 30)

bool StatsResultsLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{       
        
        langManager = LanguageManager::create();
        
        this->getStats();
        
        this->createItems();
        this->setItemPositions();
        this->addItemsToLayer();
        
        
        this->setKeypadEnabled(true);
        
        
        return true;
    }

}

void StatsResultsLayer::createItems(){
    
    CCString *resultString = CCString::createWithFormat("%i",games);
    
    statsTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS)->getCString(), "Georgia", STATS_FONT_SIZE);
    statsTitleLabel->setColor(ccc3(0,0,0));
    
    
    gamesTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_GAMES)->getCString(), "Georgia", STATS_FONT_SIZE);
    gamesTitleLabel->setColor(ccc3(0, 0, 0));
    
    gamesResultLabel = CCLabelTTF::create(resultString->getCString(), "Georgia", STATS_FONT_SIZE);
    gamesResultLabel->setColor(ccc3(0, 0, 0));
    
    resultString = CCString::createWithFormat("%i",won);
    wonTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_WON)->getCString(), "Georgia", STATS_FONT_SIZE);
    wonTitleLabel->setColor(ccc3(0, 0, 0));
    wonResultLabel = CCLabelTTF::create(resultString->getCString(), "Georgia", STATS_FONT_SIZE);
    wonResultLabel->setColor(ccc3(0, 0, 0));
    
    resultString = CCString::createWithFormat("%i",lost);
    lostTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_LOST)->getCString(), "Georgia", STATS_FONT_SIZE);
    lostTitleLabel->setColor(ccc3(0, 0, 0));
    lostResultLabel = CCLabelTTF::create(resultString->getCString(), "Georgia", STATS_FONT_SIZE);
    lostResultLabel->setColor(ccc3(0, 0, 0));
    
    resultString = CCString::createWithFormat("%i",draw);
    drawTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_TIED)->getCString(), "Georgia", STATS_FONT_SIZE);
    drawTitleLabel->setColor(ccc3(0, 0, 0));
    drawResultLabel = CCLabelTTF::create(resultString->getCString(), "Georgia", STATS_FONT_SIZE);
    drawResultLabel->setColor(ccc3(0, 0, 0));
    
    resetButton = MenuButton::create("button_wide_0.png", "button_wide_1.png", this, menu_selector(StatsResultsLayer::resetBtnCallback), langManager->Translate(STRING_STATS_RESET)->getCString(), STATS_FONT_SIZE);
    
    backButton = CCMenuItemImage::create("button_back_0.png", "button_back_1.png", "button_back_0.png", this, menu_selector(StatsResultsLayer::backBtnCallback));
    
    statsMenu = CCMenu::create(resetButton,backButton, NULL);
}

void StatsResultsLayer::setItemPositions(){
    
    gamesTitleLabel->setPosition(ccp(VisibleRect::center().x - gamesTitleLabel->getContentSize().width/2, VisibleRect::top().y - 120));
    
    gamesResultLabel->setPosition(ccp(VisibleRect::center().x + gamesTitleLabel->getContentSize().width/2, gamesTitleLabel->getPositionY()));
    
    this->createMarkerLine(gamesTitleLabel, 0);
    
    wonTitleLabel->setPosition(ccp(gamesTitleLabel->boundingBox().origin.x + wonTitleLabel->getContentSize().width/2, gamesTitleLabel->getPositionY() - 40));
    wonResultLabel->setPosition(ccp(gamesResultLabel->getPositionX(), gamesResultLabel->getPositionY() - 40));
    
    this->createMarkerLine(wonTitleLabel, 1);
    
    lostTitleLabel->setPosition(ccp(gamesTitleLabel->boundingBox().origin.x + lostTitleLabel->getContentSize().width/2,wonTitleLabel->getPositionY() - 40));
    lostResultLabel->setPosition(ccp(gamesResultLabel->getPositionX(), wonResultLabel->getPositionY() - 40));
    
    this->createMarkerLine(lostTitleLabel, 2);
    
    drawTitleLabel->setPosition(ccp(gamesTitleLabel->boundingBox().origin.x + drawTitleLabel->getContentSize().width/2,lostTitleLabel->getPositionY() -40));
    drawResultLabel->setPosition(ccp(gamesResultLabel->getPositionX(), lostResultLabel->getPositionY() - 40));
    
    this->createMarkerLine(drawTitleLabel, 3);
    
    statsTitleLabel->setPosition(ccp(VisibleRect::center().x, gamesTitleLabel->getPositionY()+40));
    this->createMarkerLine(statsTitleLabel, 0);
    
    resetButton->setPosition(ccp(VisibleRect::center().x,drawTitleLabel->getPositionY() - 2*40));
    
    backButton->setPosition(ccp(lineHeader[0]->boundingBox().origin.x, lineHeader[0]->getPositionY()));
    
    statsMenu->setPosition(CCPointZero);
}

void StatsResultsLayer::addItemsToLayer(){
    this->addChild(gamesTitleLabel,0);
    this->addChild(gamesResultLabel,0);
    
    this->addChild(wonTitleLabel,0);
    this->addChild(wonResultLabel,0);
    
    this->addChild(lostTitleLabel,0);
    this->addChild(lostResultLabel,0);
    
    this->addChild(drawTitleLabel,0);
    this->addChild(drawResultLabel,0);
    
    this->addChild(statsTitleLabel,0);
    
    this->addChild(statsMenu,0);
}

void StatsResultsLayer::getStats(){
    games = CCUserDefault::sharedUserDefault()->getIntegerForKey("total_games");
    won = CCUserDefault::sharedUserDefault()->getIntegerForKey("won_games");
    lost = CCUserDefault::sharedUserDefault()->getIntegerForKey("lost_games");
    draw = CCUserDefault::sharedUserDefault()->getIntegerForKey("draw_games");
}

void StatsResultsLayer::resetBtnCallback(cocos2d::CCObject *pSender){
    won = 0;
    games = 0;
    lost = 0;
    draw = 0;
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("total_games", games);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("won_games", won);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("lost_games", lost);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("draw_games", draw);
    
    CCUserDefault::sharedUserDefault()->flush();
    
    gamesResultLabel->setString("0");
    wonResultLabel->setString("0");
    lostResultLabel->setString("0");
    drawResultLabel->setString("0");
    
}

void StatsResultsLayer::createMarkerLine(CCLabelTTF* labelHeader, int index){
    
    lineHeader[index] = CCSprite::create("marker_header.png");
    
    lineHeader[index]->setPosition(ccp(VisibleRect::center().x, labelHeader->boundingBox().origin.y - lineHeader[index]->getContentSize().height/2));
    
    this->addChild(lineHeader[index],0);
    
}


void StatsResultsLayer::backBtnCallback(cocos2d::CCObject *pSender){
    this->keyBackClicked();
}

void StatsResultsLayer::keyBackClicked(){
    CCScene *backScene = MenuScene::create();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, backScene,true));
}