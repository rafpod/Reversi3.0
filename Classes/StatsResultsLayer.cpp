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
#include "cocos2d.h"

USING_NS_CC;

#define STATS_LABEL_FONT_DEFAULT (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 32 : 34)
#define STATS_RESULT_FONT_DEFAULT (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 42 : 44)

#define STATS_PERCENT_FONT_DEFAULT (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 22 : 34)

#define STATS_FONT_SIZE (cocos2d::CCEGLView::sharedOpenGLView()->getVisibleSize().height/ cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * STATS_LABEL_FONT_DEFAULT)

#define STATS_RESULT_FONT_SIZE (cocos2d::CCEGLView::sharedOpenGLView()->getVisibleSize().height/ cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * STATS_RESULT_FONT_DEFAULT)

#define STATS_PERCENT_FONT_SIZE (cocos2d::CCEGLView::sharedOpenGLView()->getVisibleSize().height/ cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * STATS_PERCENT_FONT_DEFAULT )

//#define STATS_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 30)

bool StatsResultsLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{       
        
        designSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
        visibleSize = VisibleRect::getVisibleRect().size;
        
        langManager = LanguageManager::create();
        
        this->setStatsOffsets();
        
        this->getStats();
        
        this->createItems();
        this->setItemPositions();
        this->addItemsToLayer();
        
        /*CCRect prost = CCRectMake(VisibleRect::center().x, VisibleRect::center().y, 200, 100);
        
        CCSprite *a= CCSprite::create("test_shadow.png", prost);
        a->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
        this->addChild(a);*/
        
        this->setKeypadEnabled(true);
        
        
        return true;
    }

}

void StatsResultsLayer::createItems(){
    
    this->createHeader();
    
    this->createWonItems();
    
    this->createLostItems();
    
    this->createTiedItems();
    
    this->createGamesItems();
    
    this->createBottomButtons();
    
    statsMenu = CCMenu::create(detailsButton,resetButton,backButton, NULL);
}

void StatsResultsLayer::setItemPositions(){
    
    
    this->setHeaderPosition();
    
    this->setWonPositionItems();
    
    this->setLostPositionItems();
    
    this->setTiedPositionItems();
    
    this->setGamesPositionItems();
    
    this->setBottomButtonsPosition();
    
    statsMenu->setPosition(CCPointZero);
}

void StatsResultsLayer::addItemsToLayer(){
    
    this->addChild(statsTitleLabel,0);
    this->addChild(lineHeader,0);
    
    this->addChild(wonTitleLabel,0);
    this->addChild(wonResultLabel,0);
    this->addChild(wonPercentLabel,0);
    
    this->addChild(lostTitleLabel,0);
    this->addChild(lostResultLabel,0);
    this->addChild(lostPercentLabel,0);
    
    this->addChild(drawTitleLabel,0);
    this->addChild(drawResultLabel,0);
    this->addChild(drawPercentLabel,0);
    
    this->addChild(gamesTitleLabel,0);
    this->addChild(gamesResultLabel,0);
    
    this->addChild(statsMenu,0);
    
    this->addChild(lineBottom,0);
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
    
    wonPercentLabel->setString("0.00 %");
    lostPercentLabel->setString("0.00 %");
    drawPercentLabel->setString("0.00 %");
    
}


void StatsResultsLayer::createHeader(){
    
    statsTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS)->getCString(), "Georgia", STATS_FONT_SIZE);
    statsTitleLabel->setColor(ccc3(0,0,0));
    
    backButton = CCMenuItemImage::create("button_back_0.png", "button_back_1.png", "button_back_0.png", this, menu_selector(StatsResultsLayer::backBtnCallback));
    
    lineHeader = CCSprite::create("marker_header.png");
}

void StatsResultsLayer::createWonItems(){
    
    this->resultString = CCString::createWithFormat("%i",won);
    wonTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_WON)->getCString(), "Georgia", STATS_FONT_SIZE);
    wonTitleLabel->setColor(ccc3(0, 0, 0));
    
    wonResultLabel = CCLabelTTF::create(resultString->getCString(),"Georgia", STATS_RESULT_FONT_SIZE);
    wonResultLabel->setColor(ccc3(0, 0, 0));    
    
    
    float percent = games >0 ? static_cast<float> (won)/ static_cast<float>(games) * 100 : 0.0f;
    
    percentString = CCString::createWithFormat("%f  %c",percent, '%');
    
    wonPercentLabel = CCLabelTTF::create(percentString->getCString(),"Georgia", STATS_PERCENT_FONT_SIZE);
}

void StatsResultsLayer::createLostItems(){
    
    resultString = CCString::createWithFormat("%i",lost);
    lostTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_LOST)->getCString(), "Georgia", STATS_FONT_SIZE);
    lostTitleLabel->setColor(ccc3(0, 0, 0));
    
    lostResultLabel = CCLabelTTF::create(resultString->getCString(), "Georgia", STATS_RESULT_FONT_SIZE);
    lostResultLabel->setColor(ccc3(0, 0, 0));
    
    float percent = games >0 ? static_cast<float>(lost)/static_cast<float>(games) * 100 : 0.0f;
    
    percentString = CCString::createWithFormat("%f  %c",percent, '%');
    
    lostPercentLabel = CCLabelTTF::create(percentString->getCString(),"Georgia", STATS_PERCENT_FONT_SIZE);
}

void StatsResultsLayer::createTiedItems(){
    
    resultString = CCString::createWithFormat("%i",draw);
    drawTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_TIED)->getCString(), "Georgia", STATS_FONT_SIZE);
    drawTitleLabel->setColor(ccc3(0, 0, 0));
    
    drawResultLabel = CCLabelTTF::create(resultString->getCString(), "Georgia", STATS_RESULT_FONT_SIZE);
    drawResultLabel->setColor(ccc3(0, 0, 0));
    
    float percent = games >0 ? static_cast<float>(draw)/static_cast<float>(games) * 100 : 0.0f;
    
    //CCLOG("%f",  2.0f/9.0f*100);
    
    percentString = CCString::createWithFormat("%f %c",percent, '%');
    
    drawPercentLabel = CCLabelTTF::create(percentString->getCString(),"Georgia", STATS_PERCENT_FONT_SIZE);

}

void StatsResultsLayer::createGamesItems(){
    
    this->resultString = CCString::createWithFormat("%i",games);
    //int widthLabelDefault = designSize.height <=960 ? 210 : 220;
    
    //float labelWidth = visibleSize.width/designSize.width * widthLabelDefault;
    
    gamesTitleLabel = CCLabelTTF::create(langManager->Translate(STRING_STATS_GAMES)->getCString(), "Georgia", STATS_FONT_SIZE, CCSizeMake(210, 0), kCCTextAlignmentCenter);
    gamesTitleLabel->setColor(ccc3(0, 0, 0));
    
    gamesResultLabel = CCLabelTTF::create(resultString->getCString(), "Georgia", STATS_RESULT_FONT_SIZE);
    gamesResultLabel->setColor(ccc3(0, 0, 0));
}

void StatsResultsLayer::createBottomButtons(){
    
    resetButton = MenuButton::create("button_wide_0.png", "button_wide_1.png", this, menu_selector(StatsResultsLayer::resetBtnCallback), langManager->Translate(STRING_STATS_RESET)->getCString(), STATS_FONT_SIZE);
    
    detailsButton = MenuButton::create("button_wide_0.png", "button_wide_1.png", this, menu_selector(StatsResultsLayer::detailsBtnCallback), langManager->Translate(STRING_STATS_DETAILS)->getCString(), STATS_FONT_SIZE);
    
    lineBottom = CCSprite::create("marker_header.png");
}

void StatsResultsLayer::setHeaderPosition(){
    //float widthLabel = wonTitleLabel->getContentSize().width/2;
    
    statsTitleLabel->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - labelOffFromEachOther));
        
    lineHeader->setPosition(ccp(VisibleRect::center().x, statsTitleLabel->boundingBox().origin.y - lineHeader->getContentSize().height/2));
    
    backButton->setPosition(ccp(lineHeader->boundingBox().origin.x, lineHeader->getPositionY()));
}

void StatsResultsLayer::setWonPositionItems(){
    wonTitleLabel->setPosition(ccp(VisibleRect::center().x - wonTitleLabel->getContentSize().width/2, VisibleRect::top().y - labelOffFromTop));
    wonResultLabel->setPosition(ccp(VisibleRect::center().x + wonTitleLabel->getContentSize().width/2, wonTitleLabel->getPositionY() + wonResultLabel->getContentSize().height/4));
    
    wonPercentLabel->setPosition(ccp(wonResultLabel->getPositionX() + wonResultLabel->getContentSize().height ,wonTitleLabel->getPositionY() - wonResultLabel->getContentSize().height/4));
}

void StatsResultsLayer::setLostPositionItems(){
    lostTitleLabel->setPosition(ccp(wonTitleLabel->getPositionX(),wonTitleLabel->getPositionY() - labelOffFromEachOther));
    lostResultLabel->setPosition(ccp(wonResultLabel->getPositionX(), lostTitleLabel->getPositionY() + lostResultLabel->getContentSize().height/4));
    
    lostPercentLabel->setPosition(ccp(lostResultLabel->getPositionX() + lostResultLabel->getContentSize().height, lostTitleLabel->getPositionY() - lostResultLabel->getContentSize().height/4));
}

void StatsResultsLayer::setTiedPositionItems(){
    drawTitleLabel->setPosition(ccp(wonTitleLabel->getPositionX(),lostTitleLabel->getPositionY() - labelOffFromEachOther));
    drawResultLabel->setPosition(ccp(wonResultLabel->getPositionX(), drawTitleLabel->getPositionY() + drawResultLabel->getContentSize().height/4));
    
    drawPercentLabel->setPosition(ccp(drawResultLabel->getPositionX() + drawResultLabel->getContentSize().height, drawTitleLabel->getPositionY() - drawResultLabel->getContentSize().height/4));
}

void StatsResultsLayer::setGamesPositionItems(){
    gamesTitleLabel->setPosition(ccp(wonTitleLabel->getPositionX(), drawResultLabel->getPositionY() - labelOffFromEachOther));
    gamesResultLabel->setPosition(ccp(wonResultLabel->getPositionX(), gamesTitleLabel->getPositionY()));
}

void StatsResultsLayer::setBottomButtonsPosition(){
    
    detailsButton->setPosition(ccp(wonTitleLabel->getPositionX(), gamesTitleLabel->getPositionY()- buttonOffFromLastLabel));    
    resetButton->setPosition(ccp(wonResultLabel->getPositionX(),detailsButton->getPositionY()));
    
    lineBottom->setPosition(ccp(VisibleRect::center().x, resetButton->boundingBox().origin.y + resetButton->getContentSize().height));

}

void StatsResultsLayer::backBtnCallback(cocos2d::CCObject *pSender){
    this->keyBackClicked();
}

void StatsResultsLayer::keyBackClicked(){
    CCScene *backScene = MenuScene::create();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, backScene,true));
}

void StatsResultsLayer::detailsBtnCallback(cocos2d::CCObject *pSender){
    
}

void StatsResultsLayer::setStatsOffsets(){
    int offLabelTopDef = designSize.height <= 960  ? 230 : 240;
    int offEachOtherDef = designSize.height <= 960 ? 80:90;
    int offBtnDef = designSize.height <= 960 ? 140: 150;
    
    this->labelOffFromTop = visibleSize.height/designSize.height* offLabelTopDef;
    this->labelOffFromEachOther = visibleSize.height/designSize.height * offEachOtherDef;
    this->buttonOffFromLastLabel = visibleSize.height/designSize.height * offBtnDef;
}
