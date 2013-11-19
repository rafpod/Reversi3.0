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
#include "OptionButtonDefinitions.h"

using namespace cocos2d;

#define OPTIONS_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 30) //32
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
        
        this->initFileName();
        
        dist = 15;
        
        this->createItems();
        this->setBtnTags();
        this->setItemPositions();
        this->setActiveButtons();
        this->addItemsToLayer();
        
        this->setKeypadEnabled(true);
        
        //pvpButton->setSelectedBtn(false);
        //pvcButton->setSelectedBtn(true);
        
        /* //CONFIG TEST
        CCConfiguration *conf = CCConfiguration::sharedConfiguration();
        
        // conf->setObject("this.is.an.int.value", CCInteger::create(10) );
        conf->setObject("AIMode", CCBool::create(true) );
        // conf->setObject("this.is.a.string.value", CCString::create("hello world") );
        
        conf->dumpInfo();

        bool b_value = CCConfiguration::sharedConfiguration()->getBool("AIMode", false);
        CCLOG("%i", b_value);
        */
        
        bool b_value = CCUserDefault::sharedUserDefault()->getBoolForKey("pvcIsEnabled");
        CCLOG("%i", b_value);
        int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("difficulty");
        CCLOG("Diff %i", num);
        
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
    
    this->addChild(mainMenu,0);
    this->addChild(backBtnMenu,1);
    
}

void OptionsButtonsLayer::initFileName(){
    btnFileNameNormal = CCString::create("button_wide_0.png");
    btnFileNameSelected = CCString::create("button_wide_1.png");
    
    this->humanMark = "pmark_human_1.png";
    this->aiMark = "pmark_AI_1.png";
    this->blackStone = "stone_black.png";
    this->whiteStone = "stone_white.png";
    this->blueStone = "stone_blue.png";
    this->redStone = "stone_red.png";
    this->greenStone = "stone_green.png";
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
    
    
    pvpButton=ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), "vs", DIFFICULTY_FONT_SIZE, humanMark, humanMark);
    //pvpButton->setScale(1.1f);
    
    //pvpButton->setSelectedBtn(false);
    
    pvcButton=ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), "vs", DIFFICULTY_FONT_SIZE, humanMark, aiMark);
    //pvcButton->setScale(1.1f);
    
    //pvcButton->setSelectedBtn(true);
    
    backButton = CCMenuItemImage::create("button_back_0.png", "button_back_1.png", "button_back_0.png", this, menu_selector(OptionsButtonsLayer::backBtnCallback));
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
    easyButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,ONE_IMG_BTN);
    mediumButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,TWO_IMG_BTN);
    hardButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,THREE_IMG_BTN);
    veryHardButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,FOUR_IMG_BTN);
    hardestButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,FIVE_IMG_BTN);
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
    
    blackWhiteButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), blackStone, whiteStone,TWO_IMG_BTN);
    
   
    redGreenButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), greenStone, redStone,TWO_IMG_BTN);
    
    
    redBlueButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), blueStone, redStone,TWO_IMG_BTN);
    
    blackWhiteButton->setScale(1.1);
    redGreenButton->setScale(1.1);
    redBlueButton->setScale(1.1);
}

void OptionsButtonsLayer::createBoardItems(){
    //===========================
    //Create Label
    //===========================
    boardLabel = CCLabelTTF::create(langManager->Translate(STRING_BOARD)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    boardLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Button
    //===========================
    boardButton =MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_WOOD)->getCString(), OPTIONS_FONT_SIZE2);
}

void OptionsButtonsLayer::createMovesItems(){
    //===========================
    //Create Label
    //===========================
    //movesLabel = CCLabelTTF::create(langManager->Translate(STRING_SHOW_MOVES)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    //CCString *temp = ccs(langManager->Translate(STRING_SHOW_MOVES)->getCString());
    
    //CCLOG("lenght: %i", temp->length());
    
    movesLabel = CCLabelTTF::create(langManager->Translate(STRING_SHOW_MOVES)->getCString(), "Georgia", OPTIONS_FONT_SIZE, CCSizeMake(200, 0), kCCTextAlignmentCenter);
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
    mainMenu = CCMenu::create(pvpButton,pvcButton, easyButton,mediumButton,hardButton,veryHardButton, hardestButton,crossButton,straightButton, blackWhiteButton,redGreenButton,redBlueButton,boardButton,movesButton, liveScoreButton, NULL);
    
    backBtnMenu = CCMenu::create(backButton, NULL);
    
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
    
    backButton->setPosition(ccp(lineHeader[0]->boundingBox().origin.x, lineHeader[0]->getPositionY()));
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
    movesLabel->setPosition(ccp(VisibleRect::center().x - movesLabel->getContentSize().width/1.7,boardButton->getPositionY() - movesLabel->getContentSize().height/1.6 - 30));
    
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
    
    mainMenu->setPosition(CCPointZero);
    
    backBtnMenu->setPosition(CCPointZero);

}

void OptionsButtonsLayer::setBtnTags(){
    pvpButton->setTag(PVP_BTN_TAG);
    pvcButton->setTag(PVC_BTN_TAG);
    
    easyButton->setTag(EASY_BTN_TAG);
    mediumButton->setTag(MEDIUM_BTN_TAG);
    hardButton->setTag(HARD_BTN_TAG);
    veryHardButton->setTag(VERY_HARD_BTN_TAG);
    hardestButton->setTag(HARDEST_BTN_TAG);
    
    crossButton->setTag(CROSS_BTN_TAG);
    straightButton->setTag(STRAIGHT_BTN_TAG);
    
    blackWhiteButton->setTag(BL_WHITE_BTN_TAG);
    redBlueButton->setTag(BLUE_RED_BTN_TAG);
    redGreenButton->setTag(GR_RED_BTN_TAG);
}

void OptionsButtonsLayer::setActiveButtons(){
    
    bool pvcIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("pvcIsEnabled");
    if (pvcIsEnabled) {        
        pvpButton->setSelectedBtn(false);
        pvcButton->setSelectedBtn(true);
    }else{
        pvpButton->setSelectedBtn(true);
        pvcButton->setSelectedBtn(false);
    }
    
    int diffLvl = CCUserDefault::sharedUserDefault()->getIntegerForKey("difficulty");
    
    
    switch (diffLvl) {
        case MEDIUM_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(true);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(false);
            
            break;
        case HARD_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(true);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(false);
            
            break;
        case VERY_HARD_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(true);
            hardestButton->setSelectedBtn(false);
            
            break;
        case HARDEST_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(true);
            
            break;
        default:
            easyButton->setSelectedBtn(true);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(false);
            break;
    }
    
    bool straightFormIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("straightFormIsEnabled");
    
    if (straightFormIsEnabled) {
        crossButton->setSelectedBtn(false);
        straightButton->setSelectedBtn(true);
    }else{
        crossButton->setSelectedBtn(true);
        straightButton->setSelectedBtn(false);
    }
    
    int colorBtn = CCUserDefault::sharedUserDefault()->getIntegerForKey("colorBtn");
    
    switch (colorBtn) {
        case GR_RED_BTN_TAG:
            blackWhiteButton->setSelectedBtn(false);
            redGreenButton->setSelectedBtn(true);
            redBlueButton->setSelectedBtn(false);
            
            break;
        case BLUE_RED_BTN_TAG:
            blackWhiteButton->setSelectedBtn(false);
            redGreenButton->setSelectedBtn(false);
            redBlueButton->setSelectedBtn(true);
            
            break;
        default:
            blackWhiteButton->setSelectedBtn(true);
            redGreenButton->setSelectedBtn(false);
            redBlueButton->setSelectedBtn(false);
            
            break;
    }
    
}

void OptionsButtonsLayer::modeBtnCallback(CCObject *pSender){
    
    ImageOptionButton* pMenuItem = (ImageOptionButton *)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    
    
    
    switch (tag) {
        case PVP_BTN_TAG:
            pvpButton->setSelectedBtn(true);
            pvcButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setBoolForKey("pvcIsEnabled", false);
            
            break;
        case PVC_BTN_TAG:
            pvpButton->setSelectedBtn(false);
            pvcButton->setSelectedBtn(true);
            
            CCUserDefault::sharedUserDefault()->setBoolForKey("pvcIsEnabled", true);
            
            break;
        default:
            break;
            
    }
    
    CCUserDefault::sharedUserDefault()->flush();

}

void OptionsButtonsLayer::difficultyBtnCallback(cocos2d::CCObject *pSender){
    ImageOptionButton* pMenuItem = (ImageOptionButton *)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    
    switch (tag) {
        case EASY_BTN_TAG:
            easyButton->setSelectedBtn(true);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("difficulty", EASY_BTN_TAG);
            
            break;
        case MEDIUM_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(true);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("difficulty", MEDIUM_BTN_TAG);
            
            break;
        case HARD_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(true);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("difficulty", HARD_BTN_TAG);
            
            break;
        case VERY_HARD_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(true);
            hardestButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("difficulty", VERY_HARD_BTN_TAG);
            
            break;
        
        case HARDEST_BTN_TAG:
            easyButton->setSelectedBtn(false);
            mediumButton->setSelectedBtn(false);
            hardButton->setSelectedBtn(false);
            veryHardButton->setSelectedBtn(false);
            hardestButton->setSelectedBtn(true);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("difficulty", HARDEST_BTN_TAG);
            
            break;
        default:
            break;
            
    }
    
    CCUserDefault::sharedUserDefault()->flush();

}

void OptionsButtonsLayer::startFormBtnCallback(cocos2d::CCObject *pSender){
    MenuButton* pMenuItem = (MenuButton *)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    
    switch (tag) {
        case CROSS_BTN_TAG:
            crossButton->setSelectedBtn(true);
            straightButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setBoolForKey("straightFormIsEnabled", false);
            
            break;
        case STRAIGHT_BTN_TAG:
            crossButton->setSelectedBtn(false);
            straightButton->setSelectedBtn(true);
            
            CCUserDefault::sharedUserDefault()->setBoolForKey("straightFormIsEnabled", true);
            
            break;
        default:
            break;
    }
    
    CCUserDefault::sharedUserDefault()->flush();

}

void OptionsButtonsLayer::colorBtnCallback(cocos2d::CCObject *pSender){
    
    ImageOptionButton* pMenuItem = (ImageOptionButton *)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    
    switch (tag) {
        case GR_RED_BTN_TAG:
            blackWhiteButton->setSelectedBtn(false);
            redGreenButton->setSelectedBtn(true);
            redBlueButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("colorBtn", 1);
            
            break;
        case BLUE_RED_BTN_TAG:
            blackWhiteButton->setSelectedBtn(false);
            redGreenButton->setSelectedBtn(false);
            redBlueButton->setSelectedBtn(true);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("colorBtn", 2);
            
            break;
        default:
            blackWhiteButton->setSelectedBtn(true);
            redGreenButton->setSelectedBtn(false);
            redBlueButton->setSelectedBtn(false);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("colorBtn", 0);
            
            break;
    }
    
    CCUserDefault::sharedUserDefault()->flush();

}

void OptionsButtonsLayer::boardBtnCallback(cocos2d::CCObject *pSender){
    
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

void OptionsButtonsLayer::backBtnCallback(cocos2d::CCObject *pSender){
    this->keyBackClicked();
}
