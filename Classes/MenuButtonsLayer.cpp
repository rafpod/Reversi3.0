//
//  MenuButtonsLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 08.11.2013.
//
//

#include "MenuButtonsLayer.h"
#include "VisibleRect.h"
#include "GameScene.h"
#include "OptionsScene.h"
#include "StatsScene.h"


//#define MAIN_MENU_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 44)

#define FONT_MENU (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 36 : 46)

#define MAIN_MENU_FONT_SIZE2  (cocos2d::CCEGLView::sharedOpenGLView()->getVisibleSize().width / cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width * FONT_MENU)

#define MENU_OFF_DIST_FROM_LOGO (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 30 : 40)

#define MENU_OFF_DIST_FROM_BTN (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 43 : 53)

#define RATIO_BTN_HEIGHT_TO_VIS_SIZE_HEIGHT_PERCENT 13.96
#define PERCENT_DISTANCE_FROM_LOGO 3.125
#define PERCENT_DISTANCE_FROM_BTN 4.47

#define PLAY_BTN_TAG        0
#define OPTIONS_BTN_TAG     1
#define RULES_BTN_TAG       2
#define STATS_BTN_TAG       3
#define MORE_GAMES_BTN_TAG  4



bool MenuButtonsLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{
        
        visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        origin = CCDirector::sharedDirector()->getVisibleOrigin();
        
        //langManager = new LanguageManager();
        langManager = LanguageManager::create();
        
        createItems();
        setBtnTag();
        setItemPositions();
        addItemsToLayer();
        
        this->setKeypadEnabled(true);
        
        return true;
    }
}

void MenuButtonsLayer::createItems(){
    
    //===========================
    //Create Main Logo
    //===========================
    mainLogo = CCSprite::create("lite_logo.png");
    
    
    //===========================
    //Create Buttons
    //===========================
    CCString *btnFileNameNormal = CCString::create("button_menu_0.png");
    CCString *btnFileNameSelected = CCString::create("button_menu_1.png");
    
    playButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(MenuButtonsLayer::menuBtnCallback),langManager->Translate(STRING_PLAY)->getCString(), MAIN_MENU_FONT_SIZE2);
    
    optionsButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(MenuButtonsLayer::menuBtnCallback),langManager->Translate(STRING_OPTIONS)->getCString(), MAIN_MENU_FONT_SIZE2);
    
    rulesButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(MenuButtonsLayer::menuBtnCallback),langManager->Translate(STRING_RULES)->getCString(), MAIN_MENU_FONT_SIZE2);
    
    statsButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(MenuButtonsLayer::menuBtnCallback), langManager->Translate(STRING_STATS)->getCString(), MAIN_MENU_FONT_SIZE2);
    
    moreGamesButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(MenuButtonsLayer::menuBtnCallback), langManager->Translate(STRING_MOREGAMES)->getCString(), MAIN_MENU_FONT_SIZE2);
    
    float scaleBtnH = VisibleRect::getVisibleRect().size.height/ CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height;
    
    playButton->setScale(scaleBtnH);
    optionsButton->setScale(scaleBtnH);
    rulesButton->setScale(scaleBtnH);
    statsButton->setScale(scaleBtnH);
    moreGamesButton->setScale(scaleBtnH);

    
    /*
    //=========================
    //Set adequate scale to buttons
    //=========================
    float currRatioBtnVisSizeY = playButton->getContentSize().height/visibleSize.height * 100;
    CCLOG("MenuBtn percent height: %f", currRatioBtnVisSizeY);
    
    float heightBtn, scaleBtn;
    
    if(currRatioBtnVisSizeY > RATIO_BTN_HEIGHT_TO_VIS_SIZE_HEIGHT_PERCENT){
        heightBtn = visibleSize.height * RATIO_BTN_HEIGHT_TO_VIS_SIZE_HEIGHT_PERCENT / 100;
        scaleBtn = heightBtn/playButton->getContentSize().height;
        
        //mainLogo->setScale(scaleBtn);
        
        //CCLOG("scaleBTNfirst : %f", scaleBtn);
        
        //scaleBtn = VisibleRect::getVisibleRect().size.height/ CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height;
        
        //CCLOG("scaleBTNfirst2 : %f", scaleBtn);
        
        playButton->setScale(scaleBtn);
        optionsButton->setScale(scaleBtn);
        rulesButton->setScale(scaleBtn);
        statsButton->setScale(scaleBtn);
        moreGamesButton->setScale(scaleBtn);
        
    }
    */
    //===========================
    //Create Main Menu
    //===========================
    mainMenu = CCMenu::create(playButton, optionsButton, rulesButton, statsButton, moreGamesButton, NULL);
    
    
}

void MenuButtonsLayer::setItemPositions(){
    
    //float distFromLastBtn = playButton->getContentSize().height/3.5;
    
    //mainLogo->setPosition(ccp(visibleSize.width/2 + origin.x, VisibleRect::top().y - mainLogo->getContentSize().width/2));
    //===========================
    //Set Logo Position
    //===========================
    mainLogo->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - mainLogo->getContentSize().width/2));
    
    //===========================
    //Set MenuButtons Position
    //===========================
    //float partDistFromLogo = visibleSize.height * PERCENT_DISTANCE_FROM_LOGO/100;
    //int designSizeHeight = CCDirector::sharedDirector()->getWinSize().height;
    
    /*if( designSizeHeight - visibleSize.height > 100){
        partDistFromLogo = visibleSize.height * (PERCENT_DISTANCE_FROM_LOGO-1)/100;
    }*/
    
    float partDistFromLogo = VisibleRect::getVisibleRect().size.height/CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * MENU_OFF_DIST_FROM_LOGO;
    
    playButton->setPosition(ccp(VisibleRect::center().x ,mainLogo->boundingBox().origin.y - playButton->getContentSize().height/2 - partDistFromLogo));
    
    //float partDistFromBtn = visibleSize.height * PERCENT_DISTANCE_FROM_BTN/100;
    
   float partDistFromBtn = VisibleRect::getVisibleRect().size.height/CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * MENU_OFF_DIST_FROM_BTN;
    
    optionsButton->setPosition(ccp(VisibleRect::center().x ,playButton->boundingBox().origin.y - partDistFromBtn));
    
    rulesButton->setPosition(ccp(VisibleRect::center().x ,optionsButton->boundingBox().origin.y - partDistFromBtn));
    statsButton->setPosition(ccp(VisibleRect::center().x ,rulesButton->boundingBox().origin.y - partDistFromBtn));
    moreGamesButton->setPosition(ccp(VisibleRect::center().x ,statsButton->boundingBox().origin.y - partDistFromBtn));
   
    
    //===========================
    //Set Menu Position
    //===========================
    mainMenu->setPosition(CCPointZero);
}

void MenuButtonsLayer::addItemsToLayer(){
    this->addChild(mainLogo,0);
    
    this->addChild(mainMenu,0);
    }

void MenuButtonsLayer::setBtnTag(){
    playButton->setTag(PLAY_BTN_TAG);
    optionsButton->setTag(OPTIONS_BTN_TAG);
    rulesButton->setTag(RULES_BTN_TAG);
    statsButton->setTag(STATS_BTN_TAG);
    moreGamesButton->setTag(MORE_GAMES_BTN_TAG);
}

void MenuButtonsLayer::menuBtnCallback(cocos2d::CCObject *pSender){
    
    MenuButton* pMenuItem = (MenuButton *)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    CCScene *nextScene;
    
    switch (tag) {
        case PLAY_BTN_TAG:
            nextScene = GameScene::create();
            
            CCDirector::sharedDirector()->setDepthTest(true);
            CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, nextScene,false));
            
            break;
        case OPTIONS_BTN_TAG:
            nextScene = OptionsScene::create();
            
            CCDirector::sharedDirector()->setDepthTest(true);
            CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, nextScene,false));
            
            break;
        
        case RULES_BTN_TAG:
            
            break;
        case STATS_BTN_TAG:
            nextScene = StatsScene::create();
            
            CCDirector::sharedDirector()->setDepthTest(true);
            CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, nextScene,false));
            
            break;
        case MORE_GAMES_BTN_TAG:
            
            break;
        default:
            break;
    }
    
}

void MenuButtonsLayer::keyBackClicked(){
    
    CCDirector::sharedDirector()->end();
    //exit(0);
}