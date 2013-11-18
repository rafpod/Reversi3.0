//
//  OptionsButtonsLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 13.11.2013.
//
//

#include "OptionsButtonsLayer.h"
#include "VisibleRect.h"
#include "MenuScene.h"

using namespace cocos2d;

#define OPTIONS_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 32) //32
#define MODE_FONT_SIZE     (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 32)
#define OPTIONS_FONT_SIZE2  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 16) //26
#define DIFFICULTY_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 20)
#define SHOW_MOVES_HEADER_INDEX 5

#define ONE_IMG_BTN     1
#define TWO_IMG_BTN     2
#define THREE_IMG_BTN   3
#define FOUR_IMG_BTN    4
#define FIVE_IMG_BTN    5


bool OptionsButtonsLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{
        CCLOG("START OPTIONS");
        visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        origin = CCDirector::sharedDirector()->getVisibleOrigin();        
        
        langManager = LanguageManager::create();
        
        btnFileNameNormal = CCString::create("button_wide_0.png");
        btnFileNameSelected = CCString::create("button_wide_1.png");
        
        
        dist = 15;
        
        createItems();
        setItemPositions();
        addItemsToLayer();
        
        this->setKeypadEnabled(true);
        
        
        //testButton=ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), "vs", DIFFICULTY_FONT_SIZE, "pmark_human_1.png", "pmark_AI_1.png");
        
        //testButton->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
        //this->addChild(testButton, 2);
        
        
       // testButton2=ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), "stone_black.png", "stone_white.png",FOUR_IMG_BTN);
        
       // testButton2->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + 100));
        //this->addChild(testButton2, 2);
       // testButton2->setScale(1.1);
        
        return true;
    }
}

void OptionsButtonsLayer::createItems(){
    
    this->createGameModeItems();
    
    this->createDiffItems();
    
    this->createStartFormItems();
    
    this->createColorSetItems();
   
    this->createBoardItems();
   
    this->createMovesItems();
    
    this->createLiveScoreItems();
    
    this->createMenus();
}


void OptionsButtonsLayer::setItemPositions(){
    
    this->setGameModeItemsPositions();
    
    this->setDiffItemsPositions();
    
    this->setStartFormItemsPositions();
    
    this->setColorSetItemsPositions();
    
    this->setBoardItemsPositions();
    
    this->setMovesItemsPositions();
    
    this->setLiveScoreItemsPositions();
    
    this->setMenusPositions();
}



void OptionsButtonsLayer::addItemsToLayer(){
    this->addChild(modeLabel,1);
    this->addChild(difficultyLabel,1);
    this->addChild(startFormLabel,1);
    this->addChild(colorsLabel,1);
    this->addChild(boardLabel,1);
    this->addChild(movesLabel,1);
    this->addChild(liveScoreLabel,1);
    
    this->addChild(modeMenu,0);
    this->addChild(difficultyMenu,0);
    this->addChild(startFormMenu,0);
    this->addChild(colorsMenu,0);
    this->addChild(boardMenu,0);
    this->addChild(movLiveMenu,0);
    
    //this->addChild(movesMenu,0);
    //this->addChild(liveScoreMenu,0);
}

void OptionsButtonsLayer::createMarkerLine(CCLabelTTF* labelHeader, int index){
    
    lineHeader[index] = CCSprite::create("marker_header.png");
    lineHeader[index]->setPosition(ccp(VisibleRect::center().x, labelHeader->boundingBox().origin.y - lineHeader[index]->getContentSize().height/2));
    this->addChild(lineHeader[index],1);
    
}

void OptionsButtonsLayer::createGameModeItems(){
    //===========================
    //Create Label
    //===========================
    modeLabel = CCLabelTTF::create(langManager->Translate(STRING_MODES)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    modeLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    pvpButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), langManager->Translate(STRING_PVP)->getCString(), MODE_FONT_SIZE);
    //pvpButton->setScale(0.65f);
    pvpButton->setScale(1.1f);
    
    pvcButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), langManager->Translate(STRING_PVC)->getCString(), MODE_FONT_SIZE);
    //pvcButton->setScale(0.65f);
    pvcButton->setScale(1.1f);    
    
}

void OptionsButtonsLayer::createDiffItems(){
    //===========================
    //Create Label Items
    //===========================
    difficultyLabel = CCLabelTTF::create(langManager->Translate(STRING_DIFFICULTY)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    difficultyLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    easyButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_EASY)->getCString(), DIFFICULTY_FONT_SIZE);
    mediumButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_MEDIUM)->getCString(), DIFFICULTY_FONT_SIZE);
    hardButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_HARD)->getCString(), DIFFICULTY_FONT_SIZE);
    veryHardButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_VERY_HARD)->getCString(), DIFFICULTY_FONT_SIZE);
    hardestButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_THE_HARDEST)->getCString(), DIFFICULTY_FONT_SIZE);
    //hardestButton->setScale(1.1);
}

void OptionsButtonsLayer::createStartFormItems(){
    //===========================
    //Create Label Items
    //===========================
    startFormLabel = CCLabelTTF::create(langManager->Translate(STRING_START_FORM)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    startFormLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    crossButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_CROSS)->getCString(), OPTIONS_FONT_SIZE2);
    //crossButton->setScale(0.65f);
    
    straightButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_STRAIGHT)->getCString(), OPTIONS_FONT_SIZE2);
    //straightButton->setScale(0.65f);
    
    crossButton->setScale(1.1);
    straightButton->setScale(1.1);
}

void OptionsButtonsLayer::createColorSetItems(){
    //===========================
    //Create Label
    //===========================
    colorsLabel = CCLabelTTF::create(langManager->Translate(STRING_COLORS)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    colorsLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    blackWhiteButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_BLACK_WHITE)->getCString(), OPTIONS_FONT_SIZE2);
    //blackWhiteButton->setScale(0.65f);
    
    redGreenButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_RED_BLUE)->getCString(), OPTIONS_FONT_SIZE2);
    
    redBlueButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_RED_BLUE)->getCString(), OPTIONS_FONT_SIZE2);
    //redBlueButton->setScale(0.65f);
    
    blackWhiteButton->setScale(1.1);
    redGreenButton->setScale(1.1);
    redBlueButton->setScale(1.1);
}

void OptionsButtonsLayer::createBoardItems(){
    //===========================
    //Create Label
    //===========================
    boardLabel = CCLabelTTF::create(langManager->Translate(STRING_COLORS)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    boardLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Button
    //===========================
    boardButton =MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_RED_BLUE)->getCString(), OPTIONS_FONT_SIZE2);
}

void OptionsButtonsLayer::createMovesItems(){
    //===========================
    //Create Label
    //===========================
    //movesLabel = CCLabelTTF::create(langManager->Translate(STRING_SHOW_MOVES)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    CCString *temp = ccs(langManager->Translate(STRING_SHOW_MOVES)->getCString());
    
    CCLOG("lenght: %i", temp->length());
    
    movesLabel = CCLabelTTF::create(langManager->Translate(STRING_SHOW_MOVES)->getCString(), "Georgia", OPTIONS_FONT_SIZE, CCSizeMake(250, 0), kCCTextAlignmentCenter);
    movesLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    movesButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::movesBtnCallback), langManager->Translate(STRING_ON)->getCString(), OPTIONS_FONT_SIZE2);
    //movesOnButton->setScale(0.65f);
    /*
     movesOffButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::movesBtnCallback), langManager->Translate(STRING_OFF)->getCString(), OPTIONS_FONT_SIZE2);*/
    //movesOffButton->setScale(0.65f);
}

void OptionsButtonsLayer::createLiveScoreItems(){
    //===========================
    //Create Label
    //===========================
    //liveScoreLabel = CCLabelTTF::create(langManager->Translate(STRING_LIVE_SCORE)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    liveScoreLabel = CCLabelTTF::create(langManager->Translate(STRING_LIVE_SCORE)->getCString(), "Georgia", OPTIONS_FONT_SIZE, CCSizeMake(150, 0), kCCTextAlignmentCenter);
    liveScoreLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    liveScoreButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), langManager->Translate(STRING_ON)->getCString(), OPTIONS_FONT_SIZE2);
    //liveScoreOnButton->setScale(0.65f);
    /*
     liveScoreOffButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), langManager->Translate(STRING_OFF)->getCString(), OPTIONS_FONT_SIZE2);*/
    //liveScoreOffButton->setScale(0.65f);
}

void OptionsButtonsLayer::createMenus(){
    //===========================
    //Create menus
    //===========================
    modeMenu = CCMenu::create(pvpButton,pvcButton, NULL);
    difficultyMenu = CCMenu::create(easyButton,mediumButton,hardButton,veryHardButton, hardestButton, NULL);
    startFormMenu = CCMenu::create(crossButton,straightButton, NULL);
    colorsMenu = CCMenu::create(blackWhiteButton,redGreenButton,redBlueButton, NULL);
    boardMenu = CCMenu::create(boardButton, NULL);
    movLiveMenu = CCMenu::create(movesButton, liveScoreButton, NULL);
    //movesMenu = CCMenu::create(movesOnButton, movesOffButton, NULL);
    //liveScoreMenu = CCMenu::create(liveScoreOnButton, liveScoreOffButton, NULL);
}

//===========================
//SET POSITIONS METHODS
//===========================

void OptionsButtonsLayer::setGameModeItemsPositions(){
    //==============================
    //Set Label position
    //==============================
    modeLabel->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y - modeLabel->getContentSize().height - 30));
    
    //==============================
    //Set Buttons position
    //==============================
    /* pvpButton->setPosition(ccp(VisibleRect::left().x + pvpButton->getContentSize().width/2, modeLabel->getPositionY() - pvpButton->getContentSize().height/2));
     pvcButton->setPosition(ccp(pvpButton->getPositionX() + pvcButton->getContentSize().width/1.45, modeLabel->getPositionY() - pvcButton->getContentSize().height/2));
     */
    pvpButton->setPosition(ccp(VisibleRect::center().x - pvpButton->getContentSize().width/2, modeLabel->getPositionY() - pvpButton->getContentSize().height/2 - dist));
    pvcButton->setPosition(ccp(VisibleRect::center().x + pvcButton->getContentSize().width/2, modeLabel->getPositionY() - pvcButton->getContentSize().height/2 - dist));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(modeLabel,0);
}

void OptionsButtonsLayer::setDiffItemsPositions(){
    //===========================
    //Set Label position
    //===========================
    difficultyLabel->setPosition(ccp(VisibleRect::center().x,pvpButton->getPositionY() - difficultyLabel->getContentSize().height - 30));
    
    //==============================
    //Set Buttons position
    //==============================
    easyButton->setPosition(ccp(pvpButton->boundingBox().origin.x + pvpButton->getContentSize().width/2 - easyButton->getContentSize().width/2, difficultyLabel->getPositionY() - easyButton->getContentSize().height/2 - dist));
    mediumButton->setPosition(ccp(easyButton->getPositionX() + mediumButton->getContentSize().width, easyButton->getPositionY()));
    hardButton->setPosition(ccp(mediumButton->getPositionX() + hardButton->getContentSize().width, easyButton->getPositionY()));
    veryHardButton->setPosition(ccp(easyButton->boundingBox().origin.x + easyButton->getContentSize().width, easyButton->getPositionY() - veryHardButton->getContentSize().height/1.5));
    hardestButton->setPosition(ccp(mediumButton->boundingBox().origin.x + mediumButton->getContentSize().width, easyButton->getPositionY() - veryHardButton->getContentSize().height/1.5));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(difficultyLabel,1);
}

void OptionsButtonsLayer::setStartFormItemsPositions(){
    //==============================
    //Set Label position
    //==============================
    startFormLabel->setPosition(ccp(VisibleRect::center().x,veryHardButton->getPositionY() - startFormLabel->getContentSize().height - 30));
    
    //==============================
    //Set Buttons position
    //==============================
    crossButton->setPosition(ccp(veryHardButton->getPositionX(), startFormLabel->getPositionY() - crossButton->getContentSize().height/2 - dist));
    straightButton->setPosition(ccp(hardestButton->getPositionX(), crossButton->getPositionY()));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(startFormLabel,2);
}

void OptionsButtonsLayer::setColorSetItemsPositions(){
    //==============================
    //Set Label position
    //==============================
    colorsLabel->setPosition(ccp(VisibleRect::center().x,crossButton->getPositionY() - colorsLabel->getContentSize().height - 30));
    
    //==============================
    //Set Buttons position
    //==============================
    blackWhiteButton->setPosition(ccp(easyButton->getPositionX(), colorsLabel->getPositionY() - blackWhiteButton->getContentSize().height/2 - dist));
    redGreenButton->setPosition(ccp(mediumButton->getPositionX(), blackWhiteButton->getPositionY()));
    redBlueButton->setPosition(ccp(hardButton->getPositionX(), blackWhiteButton->getPositionY()));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(colorsLabel,3);
}

void OptionsButtonsLayer::setBoardItemsPositions(){
    //==============================
    //Set Label position
    //==============================
    boardLabel->setPosition(ccp(VisibleRect::center().x,blackWhiteButton->getPositionY() - boardLabel->getContentSize().height - 30));
    
    //==============================
    //Set Button position
    //==============================
    boardButton->setPosition(ccp(VisibleRect::center().x, boardLabel->getPositionY()- boardButton->getContentSize().height/2 - dist));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(boardLabel,4);
}

void OptionsButtonsLayer::setMovesItemsPositions(){
    //==============================
    //Set Label position
    //==============================
    movesLabel->setPosition(ccp(VisibleRect::center().x - movesLabel->getContentSize().width/2,boardButton->getPositionY() - movesLabel->getContentSize().height/1.6 - 30));
    
    //==============================
    //Set Button position
    //==============================
    movesButton->setPosition(ccp(movesLabel->boundingBox().origin.x + movesLabel->getContentSize().width/2, movesLabel->boundingBox().origin.y - movesButton->getContentSize().height/3.5 - dist));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(movesLabel,5);

}

void OptionsButtonsLayer::setLiveScoreItemsPositions(){
    //==============================
    //Set LiveScore Items position
    //==============================
    liveScoreLabel->setPosition(ccp(boardButton->boundingBox().origin.x + boardButton->getContentSize().width + liveScoreLabel->getContentSize().width/4,lineHeader[SHOW_MOVES_HEADER_INDEX]->getPositionY() + liveScoreLabel->getContentSize().height/2));
    
    //==============================
    //Set Buttons position
    //==============================
    liveScoreButton->setPosition(ccp(liveScoreLabel->boundingBox().origin.x + liveScoreLabel->getContentSize().width/2, movesButton->getPositionY()));

}

void OptionsButtonsLayer::setMenusPositions(){
    
    modeMenu->setPosition(CCPointZero);
    difficultyMenu->setPosition(CCPointZero);
    startFormMenu->setPosition(CCPointZero);
    colorsMenu->setPosition(CCPointZero);
    boardMenu->setPosition(CCPointZero);
    movLiveMenu->setPosition(CCPointZero);
}

void OptionsButtonsLayer::modeBtnCallback(CCObject *pSender){
    
}

void OptionsButtonsLayer::difficultyBtnCallback(cocos2d::CCObject *pSender){
    
}

void OptionsButtonsLayer::startFormBtnCallback(cocos2d::CCObject *pSender){
    
}

void OptionsButtonsLayer::colorBtnCallback(cocos2d::CCObject *pSender){
    
}

void OptionsButtonsLayer::movesBtnCallback(cocos2d::CCObject *pSender){
    
}

void OptionsButtonsLayer::liveScoreBtnCallback(cocos2d::CCObject *pSender){
    
}

void OptionsButtonsLayer::keyBackClicked(){
    CCLOG("BACK");
    
    CCScene *backScene = MenuScene::create();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, backScene,true));
}