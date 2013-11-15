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

bool OptionsButtonsLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{
        CCLOG("START OPTIONS");
        visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        origin = CCDirector::sharedDirector()->getVisibleOrigin();        
        
        langManager = LanguageManager::create();
        
        createItems();
        setItemPositions();
        addItemsToLayer();
        
        this->setKeypadEnabled(true);
        
        return true;
    }
}

void OptionsButtonsLayer::createItems(){
    
    
    //===========================
    //Create Game Modes Items
    //===========================
    modeLabel = CCLabelTTF::create(langManager->Translate(STRING_MODES)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    modeLabel->setColor(ccc3(0, 0, 0));
    
    CCString *btnFileNameNormal = CCString::create("button_menu_0.png");
    CCString *btnFileNameSelected = CCString::create("button_menu_1.png");
    
    pvpButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), langManager->Translate(STRING_PVP)->getCString(), MODE_FONT_SIZE);
    pvpButton->setScale(0.65f);
    
    pvcButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), langManager->Translate(STRING_PVC)->getCString(), MODE_FONT_SIZE);
    pvcButton->setScale(0.65f);
    
    //===========================
    //Create Difficulty Items
    //===========================
    difficultyLabel = CCLabelTTF::create(langManager->Translate(STRING_DIFFICULTY)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    difficultyLabel->setColor(ccc3(0, 0, 0));
    
    CCString *btnFileNameNormal2 = CCString::create("button_wide_0.png");
    CCString *btnFileNameSelected2 = CCString::create("button_wide_1.png");
    
    easyButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_EASY)->getCString(), DIFFICULTY_FONT_SIZE);
    mediumButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_MEDIUM)->getCString(), DIFFICULTY_FONT_SIZE);
    hardButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_HARD)->getCString(), DIFFICULTY_FONT_SIZE);
    veryHardButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_VERY_HARD)->getCString(), DIFFICULTY_FONT_SIZE);
    hardestButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_THE_HARDEST)->getCString(), DIFFICULTY_FONT_SIZE);
    //hardestButton->setScale(1.1);
    
    //===========================
    //Create StartForm Items
    //===========================
    startFormLabel = CCLabelTTF::create(langManager->Translate(STRING_START_FORM)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    startFormLabel->setColor(ccc3(0, 0, 0));
    
    crossButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_CROSS)->getCString(), OPTIONS_FONT_SIZE2);
    //crossButton->setScale(0.65f);
    
    straightButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_STRAIGHT)->getCString(), OPTIONS_FONT_SIZE2);
    //straightButton->setScale(0.65f);
    
    //===========================
    //Create Colors of Stones Items
    //===========================
    colorsLabel = CCLabelTTF::create(langManager->Translate(STRING_COLORS)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    colorsLabel->setColor(ccc3(0, 0, 0));
    
    blackWhiteButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_BLACK_WHITE)->getCString(), OPTIONS_FONT_SIZE2);
    //blackWhiteButton->setScale(0.65f);
    
    redBlueButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_RED_BLUE)->getCString(), OPTIONS_FONT_SIZE2);
    //redBlueButton->setScale(0.65f);
    
    //===========================
    //Create Moves Items
    //===========================
    movesLabel = CCLabelTTF::create(langManager->Translate(STRING_SHOW_MOVES)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    movesLabel->setColor(ccc3(0, 0, 0));
    
    movesOnButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::movesBtnCallback), langManager->Translate(STRING_ON)->getCString(), OPTIONS_FONT_SIZE2);
    //movesOnButton->setScale(0.65f);
    
    movesOffButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::movesBtnCallback), langManager->Translate(STRING_OFF)->getCString(), OPTIONS_FONT_SIZE2);
    //movesOffButton->setScale(0.65f);
    
    //===========================
    //Create LiveScore Items
    //===========================
    liveScoreLabel = CCLabelTTF::create(langManager->Translate(STRING_LIVE_SCORE)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    liveScoreLabel->setColor(ccc3(0, 0, 0));
    
    liveScoreOnButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), langManager->Translate(STRING_ON)->getCString(), OPTIONS_FONT_SIZE2);
    //liveScoreOnButton->setScale(0.65f);
    
    liveScoreOffButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), langManager->Translate(STRING_OFF)->getCString(), OPTIONS_FONT_SIZE2);
    //liveScoreOffButton->setScale(0.65f);
    
    //===========================
    //Create menus
    //===========================
    modeMenu = CCMenu::create(pvpButton,pvcButton, NULL);
    difficultyMenu = CCMenu::create(easyButton,mediumButton,hardButton,veryHardButton, hardestButton, NULL);
    startFormMenu = CCMenu::create(crossButton,straightButton, NULL);
    colorsMenu = CCMenu::create(blackWhiteButton,redBlueButton, NULL);
    movesMenu = CCMenu::create(movesOnButton, movesOffButton, NULL);
    liveScoreMenu = CCMenu::create(liveScoreOnButton, liveScoreOffButton, NULL);
}


/**
 BIG BUTTONS
 *//*
void OptionsButtonsLayer::createItems(){
    
    
    //===========================
    //Create Game Modes Items
    //===========================
    modeLabel = CCLabelTTF::create(langManager->Translate(STRING_MODES)->getCString(), "Arial", OPTIONS_FONT_SIZE);
    modeLabel->setColor(ccc3(0, 0, 0));
    
    CCString *btnFileNameNormal = CCString::create("button_menu_0.png");
    CCString *btnFileNameSelected = CCString::create("button_menu_1.png");
    
    pvpButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), langManager->Translate(STRING_PVP)->getCString(), OPTIONS_FONT_SIZE2);
    pvpButton->setScale(0.65f); //0.65
    
    pvcButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), langManager->Translate(STRING_PVC)->getCString(), OPTIONS_FONT_SIZE2);
    pvcButton->setScale(0.65f);
    
    //===========================
    //Create Difficulty Items
    //===========================
    difficultyLabel = CCLabelTTF::create(langManager->Translate(STRING_DIFFICULTY)->getCString(), "Arial", OPTIONS_FONT_SIZE);
    difficultyLabel->setColor(ccc3(0, 0, 0));
    
    CCString *btnFileNameNormal2 = CCString::create("button_wide_0.png");
    CCString *btnFileNameSelected2 = CCString::create("button_wide_1.png");
    
    easyButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_EASY)->getCString(), DIFFICULTY_FONT_SIZE);
    mediumButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_MEDIUM)->getCString(), DIFFICULTY_FONT_SIZE);
    hardButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_HARD)->getCString(), DIFFICULTY_FONT_SIZE);
    veryHardButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_VERY_HARD)->getCString(), DIFFICULTY_FONT_SIZE);
    hardestButton = MenuButton::create(btnFileNameNormal2->getCString(), btnFileNameSelected2->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), langManager->Translate(STRING_THE_HARDEST)->getCString(), DIFFICULTY_FONT_SIZE);
    //hardestButton->setScale(1.1);
    
    //===========================
    //Create StartForm Items
    //===========================
    startFormLabel = CCLabelTTF::create(langManager->Translate(STRING_START_FORM)->getCString(), "Arial", OPTIONS_FONT_SIZE);
    startFormLabel->setColor(ccc3(0, 0, 0));
    
    crossButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_CROSS)->getCString(), OPTIONS_FONT_SIZE2);
    crossButton->setScale(0.55f);
    
    straightButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_STRAIGHT)->getCString(), OPTIONS_FONT_SIZE2);
    straightButton->setScale(0.55f);
    
    //===========================
    //Create Colors of Stones Items
    //===========================
    colorsLabel = CCLabelTTF::create(langManager->Translate(STRING_COLORS)->getCString(), "Arial", OPTIONS_FONT_SIZE);
    colorsLabel->setColor(ccc3(0, 0, 0));
    
    blackWhiteButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_BLACK_WHITE)->getCString(), OPTIONS_FONT_SIZE2);
    blackWhiteButton->setScale(0.55f);
    
    redBlueButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), langManager->Translate(STRING_RED_BLUE)->getCString(), OPTIONS_FONT_SIZE2);
    redBlueButton->setScale(0.55f);
    
    //===========================
    //Create Moves Items
    //===========================
    movesLabel = CCLabelTTF::create(langManager->Translate(STRING_SHOW_MOVES)->getCString(), "Arial", OPTIONS_FONT_SIZE);
    movesLabel->setColor(ccc3(0, 0, 0));
    
    movesOnButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::movesBtnCallback), langManager->Translate(STRING_ON)->getCString(), OPTIONS_FONT_SIZE2);
    movesOnButton->setScale(0.55f);
    
    movesOffButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::movesBtnCallback), langManager->Translate(STRING_OFF)->getCString(), OPTIONS_FONT_SIZE2);
    movesOffButton->setScale(0.55f);
    
    //===========================
    //Create LiveScore Items
    //===========================
    liveScoreLabel = CCLabelTTF::create(langManager->Translate(STRING_LIVE_SCORE)->getCString(), "Arial", OPTIONS_FONT_SIZE);
    liveScoreLabel->setColor(ccc3(0, 0, 0));
    
    liveScoreOnButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), langManager->Translate(STRING_ON)->getCString(), OPTIONS_FONT_SIZE2);
    liveScoreOnButton->setScale(0.55f);
    
    liveScoreOffButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), langManager->Translate(STRING_OFF)->getCString(), OPTIONS_FONT_SIZE2);
    liveScoreOffButton->setScale(0.55f);
    
    //===========================
    //Create menus
    //===========================
    modeMenu = CCMenu::create(pvpButton,pvcButton, NULL);
    difficultyMenu = CCMenu::create(easyButton,mediumButton,hardButton,veryHardButton, hardestButton, NULL);
    startFormMenu = CCMenu::create(crossButton,straightButton, NULL);
    colorsMenu = CCMenu::create(blackWhiteButton,redBlueButton, NULL);
    movesMenu = CCMenu::create(movesOnButton, movesOffButton, NULL);
    liveScoreMenu = CCMenu::create(liveScoreOnButton, liveScoreOffButton, NULL);
}
*/

void OptionsButtonsLayer::setItemPositions(){
    //==============================
    //Set Game Modes Items position
    //==============================
    modeLabel->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y - modeLabel->getContentSize().height - 20));
    pvpButton->setPosition(ccp(VisibleRect::left().x + pvpButton->getContentSize().width/2, modeLabel->getPositionY() - pvpButton->getContentSize().height/2));
    pvcButton->setPosition(ccp(pvpButton->getPositionX() + pvcButton->getContentSize().width/1.45, modeLabel->getPositionY() - pvcButton->getContentSize().height/2));
    
    //===========================
    //Set Difficulty Items position
    //===========================
    difficultyLabel->setPosition(ccp(VisibleRect::center().x,pvpButton->getPositionY() - difficultyLabel->getContentSize().height - 20));
    easyButton->setPosition(ccp(pvpButton->boundingBox().origin.x + easyButton->getContentSize().width/2, difficultyLabel->getPositionY() - easyButton->getContentSize().height/2));
    mediumButton->setPosition(ccp(easyButton->getPositionX() + mediumButton->getContentSize().width, difficultyLabel->getPositionY() - mediumButton->getContentSize().height/2));
    hardButton->setPosition(ccp(mediumButton->getPositionX() + hardButton->getContentSize().width, difficultyLabel->getPositionY() - hardButton->getContentSize().height/2));
    veryHardButton->setPosition(ccp(easyButton->boundingBox().origin.x + easyButton->getContentSize().width, easyButton->getPositionY() - veryHardButton->getContentSize().height/1.5));
    hardestButton->setPosition(ccp(mediumButton->boundingBox().origin.x + mediumButton->getContentSize().width, easyButton->getPositionY() - veryHardButton->getContentSize().height/1.5));
    
    //==============================
    //Set Start Formation Items position
    //==============================
    startFormLabel->setPosition(ccp(VisibleRect::center().x,veryHardButton->getPositionY() - startFormLabel->getContentSize().height - 20));
    crossButton->setPosition(ccp(veryHardButton->getPositionX(), startFormLabel->getPositionY() - crossButton->getContentSize().height/2));
    straightButton->setPosition(ccp(hardestButton->getPositionX(), crossButton->getPositionY()));
   
    crossButton->setScale(1.1);
    straightButton->setScale(1.1);
    
    //==============================
    //Set Colors Items position
    //==============================
    colorsLabel->setPosition(ccp(VisibleRect::center().x,crossButton->getPositionY() - colorsLabel->getContentSize().height - 20));
    blackWhiteButton->setPosition(ccp(veryHardButton->getPositionX(), colorsLabel->getPositionY() - blackWhiteButton->getContentSize().height/2));
    redBlueButton->setPosition(ccp(hardestButton->getPositionX(), blackWhiteButton->getPositionY()));
    
    blackWhiteButton->setScale(1.1);
    redBlueButton->setScale(1.1);
    
    //==============================
    //Set Moves Items position
    //==============================
    movesLabel->setPosition(ccp(VisibleRect::center().x,blackWhiteButton->getPositionY() - movesLabel->getContentSize().height - 20));
    movesOnButton->setPosition(ccp(veryHardButton->getPositionX(), movesLabel->getPositionY() - movesOnButton->getContentSize().height/2));
    movesOffButton->setPosition(ccp(hardestButton->getPositionX(), movesOnButton->getPositionY()));
    
    movesOnButton->setScale(1.1);
    movesOffButton->setScale(1.1);
    
    //==============================
    //Set Colors Items position
    //==============================
    liveScoreLabel->setPosition(ccp(VisibleRect::center().x,movesOnButton->getPositionY() - liveScoreLabel->getContentSize().height - 20));
    liveScoreOnButton->setPosition(ccp(veryHardButton->getPositionX(), liveScoreLabel->getPositionY() - liveScoreOnButton->getContentSize().height/2));
    liveScoreOffButton->setPosition(ccp(hardestButton->getPositionX(), liveScoreOnButton->getPositionY()));
    
    liveScoreOnButton->setScale(1.1);
    liveScoreOffButton->setScale(1.1);
    
    //===========================
    //Set Menu position
    //===========================
    modeMenu->setPosition(CCPointZero);
    difficultyMenu->setPosition(CCPointZero);
    startFormMenu->setPosition(CCPointZero);
    colorsMenu->setPosition(CCPointZero);
    movesMenu->setPosition(CCPointZero);
    liveScoreMenu->setPosition(CCPointZero);
}


/**
 BIG BUTTONS
 *//*
void OptionsButtonsLayer::setItemPositions(){
    //==============================
    //Set Game Modes Items position
    //==============================
    modeLabel->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y - modeLabel->getContentSize().height - 20));
    pvpButton->setPosition(ccp(VisibleRect::left().x + pvpButton->getContentSize().width/2, modeLabel->getPositionY() - pvpButton->getContentSize().height/2.5));
    pvcButton->setPosition(ccp(pvpButton->getPositionX() + pvcButton->getContentSize().width/1.45, pvpButton->getPositionY()));
    
    //===========================
    //Set Difficulty Items position
    //===========================
    difficultyLabel->setPosition(ccp(VisibleRect::center().x,pvpButton->getPositionY() - difficultyLabel->getContentSize().height - 20));
    easyButton->setPosition(ccp(pvpButton->boundingBox().origin.x + easyButton->getContentSize().width/2, difficultyLabel->getPositionY() - easyButton->getContentSize().height/2));
    mediumButton->setPosition(ccp(easyButton->getPositionX() + mediumButton->getContentSize().width, difficultyLabel->getPositionY() - mediumButton->getContentSize().height/2));
    hardButton->setPosition(ccp(mediumButton->getPositionX() + hardButton->getContentSize().width, difficultyLabel->getPositionY() - hardButton->getContentSize().height/2));
    veryHardButton->setPosition(ccp(easyButton->boundingBox().origin.x + easyButton->getContentSize().width, easyButton->getPositionY() - veryHardButton->getContentSize().height/1.5));
    hardestButton->setPosition(ccp(mediumButton->boundingBox().origin.x + mediumButton->getContentSize().width, easyButton->getPositionY() - veryHardButton->getContentSize().height/1.5));
    
    //==============================
    //Set Start Formation Items position
    //==============================
    startFormLabel->setPosition(ccp(VisibleRect::center().x,veryHardButton->getPositionY() - startFormLabel->getContentSize().height - 20));
    crossButton->setPosition(ccp(VisibleRect::left().x + crossButton->getContentSize().width/2, startFormLabel->getPositionY() - crossButton->getContentSize().height/2.5));
    straightButton->setPosition(ccp(crossButton->getPositionX() + straightButton->getContentSize().width/1.45, crossButton->getPositionY()));
    
    //==============================
    //Set Colors Items position
    //==============================
    colorsLabel->setPosition(ccp(VisibleRect::center().x,crossButton->getPositionY() - colorsLabel->getContentSize().height - 20));
    blackWhiteButton->setPosition(ccp(VisibleRect::left().x + blackWhiteButton->getContentSize().width/2, colorsLabel->getPositionY() - blackWhiteButton->getContentSize().height/2.5));
    redBlueButton->setPosition(ccp(blackWhiteButton->getPositionX() + redBlueButton->getContentSize().width/1.45, blackWhiteButton->getPositionY()));
    
    //==============================
    //Set Moves Items position
    //==============================
    movesLabel->setPosition(ccp(VisibleRect::center().x,blackWhiteButton->getPositionY() - movesLabel->getContentSize().height - 20));
    movesOnButton->setPosition(ccp(VisibleRect::left().x + movesOnButton->getContentSize().width/2, movesLabel->getPositionY() - movesOnButton->getContentSize().height/2.5));
    movesOffButton->setPosition(ccp(movesOnButton->getPositionX() + movesOffButton->getContentSize().width/1.45, movesOnButton->getPositionY()));
    
    //==============================
    //Set Colors Items position
    //==============================
    liveScoreLabel->setPosition(ccp(VisibleRect::center().x,movesOnButton->getPositionY() - liveScoreLabel->getContentSize().height - 20));
    liveScoreOnButton->setPosition(ccp(VisibleRect::left().x + liveScoreOnButton->getContentSize().width/2, liveScoreLabel->getPositionY() - liveScoreOnButton->getContentSize().height/2.5));
    liveScoreOffButton->setPosition(ccp(liveScoreOnButton->getPositionX() + liveScoreOffButton->getContentSize().width/1.45, liveScoreOnButton->getPositionY()));
    
    //===========================
    //Set Menu position
    //===========================
    modeMenu->setPosition(CCPointZero);
    difficultyMenu->setPosition(CCPointZero);
    startFormMenu->setPosition(CCPointZero);
    colorsMenu->setPosition(CCPointZero);
    movesMenu->setPosition(CCPointZero);
    liveScoreMenu->setPosition(CCPointZero);
}
*/


void OptionsButtonsLayer::addItemsToLayer(){
    this->addChild(modeLabel,1);
    this->addChild(difficultyLabel,1);
    this->addChild(startFormLabel,1);
    this->addChild(colorsLabel,1);
    this->addChild(movesLabel,1);
    this->addChild(liveScoreLabel,1);
    
    this->addChild(modeMenu,0);
    this->addChild(difficultyMenu,0);
    this->addChild(startFormMenu,0);
    this->addChild(colorsMenu,0);
    this->addChild(movesMenu,0);
    this->addChild(liveScoreMenu,0);
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