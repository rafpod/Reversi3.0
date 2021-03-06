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
#include "OptionsScene.h"
#include "ResourcesDef.h"

using namespace cocos2d;

/*
#define FONT_OPTION_LABEL (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 28 : 32)
#define FONT_OPTION_BTN (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 16 : 20)
#define FONT_OPTION_DIFF (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 20 : 24)

#define OPTIONS_FONT_SIZE_LABEL  (cocos2d::CCEGLView::sharedOpenGLView()->getVisibleSize().height/ cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * FONT_OPTION_LABEL) //32
#define OPTIONS_FONT_SIZE_BTN  (cocos2d::CCEGLView::sharedOpenGLView()->getVisibleSize().height/ cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * FONT_OPTION_BTN) //26
#define DIFFICULTY_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getVisibleSize().height/ cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height * FONT_OPTION_DIFF)
 
 //#define OPTION_OFF_BTN (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 15 : 17)
 //#define OPTION_OFF_LABEL (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height <= 960 ? 30 : 32)
*/
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
        
        visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        origin = CCDirector::sharedDirector()->getVisibleOrigin();
        screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
        
        othelloIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("othelloIsEnabled",WOOD_SKIN_BTN_TAG);
        
        langManager = LanguageManager::create();
        
        visHeight = VisibleRect::getVisibleRect().size.height;
        visWidth = VisibleRect::getVisibleRect().size.width;
        
        designHeight = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height;
        designWidth = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width;
        
        TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
        
        if (platform ==kTargetIphone && visibleSize.height > 960) {
            isHighIphone = true;
        }else{
            isHighIphone = false;
        }
                
        this->initFileName();
        
        this->setOptionOffsets();
        this->setFontSize();
                
        this->createItems();
        this->setBtnTags();
        this->setItemPositions();
        this->setActiveButtons();
        this->addItemsToLayer();
        
        this->setItemsScale();
        
        this->setKeypadEnabled(true);
              
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
    //this->addChild(menu2,0);
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
    
    if (isHighIphone && othelloIsEnabled) {
        lineHeader[index]->setScale(0.8f);
    }else if(isHighIphone && !othelloIsEnabled){
        lineHeader[index]->setScale(0.85f);
    }
    
    this->addChild(lineHeader[index],1);
    
}

void OptionsButtonsLayer::createGameModeItems(){
    //===========================
    //Create Label
    //===========================
    modeLabel = CCLabelTTF::create(langManager->Translate(STRING_MODES)->getCString(), "Georgia", fontSizeLabel);
    modeLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    
    
    pvpButton=ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), "vs", fontSizeDiff, humanMark, humanMark);
    //pvpButton->setScale(1.1f);
    
    //pvpButton->setSelectedBtn(false);
    
    pvcButton=ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::modeBtnCallback), "vs", fontSizeDiff, humanMark, aiMark);
    //pvcButton->setScale(1.1f);
    
    //pvcButton->setSelectedBtn(true);
    
    backButton = CCMenuItemImage::create("button_back_0.png", "button_back_1.png", "button_back_0.png", this, menu_selector(OptionsButtonsLayer::backBtnCallback));
    
}

void OptionsButtonsLayer::createDiffItems(){
    //===========================
    //Create Label Items
    //===========================
    difficultyLabel = CCLabelTTF::create(langManager->Translate(STRING_DIFFICULTY)->getCString(), "Georgia", fontSizeLabel);
    difficultyLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    easyButton = DiffButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,ONE_IMG_BTN);
    mediumButton = DiffButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,TWO_IMG_BTN);
    hardButton = DiffButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,THREE_IMG_BTN);
    veryHardButton = DiffButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,FOUR_IMG_BTN);
    hardestButton = DiffButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::difficultyBtnCallback), blackStone, whiteStone,FIVE_IMG_BTN);
    //hardestButton->setScale(1.1);
}

void OptionsButtonsLayer::createStartFormItems(){
    //===========================
    //Create Label Items
    //===========================
    startFormLabel = CCLabelTTF::create(langManager->Translate(STRING_START_FORM)->getCString(), "Georgia",fontSizeLabel);
    startFormLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    crossButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_CROSS)->getCString(),fontSizeBtn);
    //crossButton->setScale(0.65f);
    
    straightButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::startFormBtnCallback), langManager->Translate(STRING_STRAIGHT)->getCString(), fontSizeBtn);
    //straightButton->setScale(0.65f);
    
    //crossButton->setScale(1.1);
    //straightButton->setScale(1.1);
}

void OptionsButtonsLayer::createColorSetItems(){
    //===========================
    //Create Label
    //===========================
    colorsLabel = CCLabelTTF::create(langManager->Translate(STRING_COLORS)->getCString(), "Georgia",fontSizeLabel);
    colorsLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    
    blackWhiteButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), blackStone, whiteStone,TWO_IMG_BTN);
    
   
    redGreenButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), redStone, greenStone,TWO_IMG_BTN);
    
    
    redBlueButton = ImageOptionButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::colorBtnCallback), redStone, blueStone,TWO_IMG_BTN);
    
    //blackWhiteButton->setScale(1.1);
    //redGreenButton->setScale(1.1);
    //redBlueButton->setScale(1.1);
}

void OptionsButtonsLayer::createBoardItems(){
    //===========================
    //Create Label
    //===========================
    boardLabel = CCLabelTTF::create(langManager->Translate(STRING_BOARD)->getCString(), "Georgia", fontSizeLabel);
    boardLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Button
    //===========================
    //boardButton =MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_WOOD)->getCString(), OPTIONS_FONT_SIZE2);
    
    CCString *fileNormalReverse;
    CCString *fileSelectedReverse;
    
    
    if (othelloIsEnabled) {
        if (screenSize.height>1500) {
            
            fileNormalReverse = ccs("1536x2048/wood/button_wide_0.png");
            fileSelectedReverse = ccs("1536x2048/wood/button_wide_1.png");
            
        }else if (screenSize.height>960){
            
            fileNormalReverse = ccs("768x1024/wood/button_wide_0.png");
            fileSelectedReverse = ccs("768x1024/wood/button_wide_1.png");
            
        }else if (screenSize.height>480) {
            
            fileNormalReverse = ccs("640x960-iphonehd/wood/button_wide_0.png");
            fileSelectedReverse = ccs("640x960-iphonehd/wood/button_wide_1.png");
            
        }else{
            
            fileNormalReverse = ccs("320x480-iphone/wood/button_wide_0.png");
            fileSelectedReverse = ccs("320x480-iphone/wood/button_wide_1.png");
        }
        
        woodButton = MenuButton::create(fileNormalReverse->getCString(), fileSelectedReverse->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_WOOD)->getCString(),fontSizeBtn);
        
        othelloButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_OTHELLO)->getCString(), fontSizeBtn);
        
    }else{
        if (screenSize.height>1500) {
            
            fileNormalReverse = ccs("1536x2048/othello/button_wide_0.png");
            fileSelectedReverse = ccs("1536x2048/othello/button_wide_1.png");
            
        }else if (screenSize.height>960){
            
            fileNormalReverse = ccs("768x1024/othello/button_wide_0.png");
            fileSelectedReverse = ccs("768x1024/othello/button_wide_1.png");
            
        }else if (screenSize.height>480) {
            fileNormalReverse = ccs("640x960-iphonehd/othello/button_wide_0.png");
            fileSelectedReverse = ccs("640x960-iphonehd/othello/button_wide_1.png");
            
            
        }else{
            fileNormalReverse = ccs("320x480-iphone/othello/button_wide_0.png");
            fileSelectedReverse = ccs("320x480-iphone/othello/button_wide_1.png");
            
        }
        woodButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_WOOD)->getCString(), fontSizeBtn);
        othelloButton = MenuButton::create(fileNormalReverse->getCString(), fileSelectedReverse->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_OTHELLO)->getCString(), fontSizeBtn);
    }
    /*
    if (othelloIsEnabled) {
        if (screenSize.height>1024) {
            fileNormalReverse = ccs("1536x2048/wood/button_wide_0.png");
            fileSelectedReverse = ccs("1536x2048/wood/button_wide_1.png");
            
            
        }else{
            fileNormalReverse = ccs("768x1024/wood/button_wide_0.png");
            fileSelectedReverse = ccs("768x1024/wood/button_wide_1.png");
        }
        
        woodButton = MenuButton::create(fileNormalReverse->getCString(), fileSelectedReverse->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_WOOD)->getCString(), OPTIONS_FONT_SIZE2);
        
        othelloButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_OTHELLO)->getCString(), OPTIONS_FONT_SIZE2);
        
    }else{
        if (screenSize.height>1024) {
            fileNormalReverse = ccs("1536x2048/othello/button_wide_0.png");
            fileSelectedReverse = ccs("1536x2048/othello/button_wide_1.png");
            
            
        }else{
            fileNormalReverse = ccs("768x1024/othello/button_wide_0.png");
            fileSelectedReverse = ccs("768x1024/othello/button_wide_1.png");
            
        }
        woodButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_WOOD)->getCString(), OPTIONS_FONT_SIZE2);
        othelloButton = MenuButton::create(fileNormalReverse->getCString(), fileSelectedReverse->getCString(), this, menu_selector(OptionsButtonsLayer::boardBtnCallback), langManager->Translate(STRING_OTHELLO)->getCString(), OPTIONS_FONT_SIZE2);
    }
    */
    
    //boardButton = CCMenuItemToggle::createWithTarget(this, menu_selector(OptionsButtonsLayer::boardBtnCallback), woodButton, othelloButton, NULL);

    
}

void OptionsButtonsLayer::createMovesItems(){
    //===========================
    //Create Label
    //===========================
    CCLOG("Procent Moves: %f",200/visWidth *100);
    
    float labelWidth = visWidth/CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width*210;  //0.3125*visWidth;
    
    movesLabel = CCLabelTTF::create(langManager->Translate(STRING_SHOW_MOVES)->getCString(), "Georgia", fontSizeLabel, CCSizeMake(labelWidth, 0), kCCTextAlignmentCenter);
    movesLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    
    //movesOnButton->setScale(0.65f);
    
    movesOnButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, NULL, langManager->Translate(STRING_ON)->getCString(), fontSizeBtn);
    movesOffButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, NULL, langManager->Translate(STRING_OFF)->getCString(), fontSizeBtn);
    
    showMovesButton = CCMenuItemToggle::createWithTarget(this, menu_selector(OptionsButtonsLayer::movesBtnCallback), movesOffButton, movesOnButton, NULL);
    
        
    //movesOffButton->setScale(0.65f);
}

void OptionsButtonsLayer::createLiveScoreItems(){
    //===========================
    //Create Label
    //===========================
    //liveScoreLabel = CCLabelTTF::create(langManager->Translate(STRING_LIVE_SCORE)->getCString(), "Georgia", OPTIONS_FONT_SIZE);
    float labelWidth = visWidth/CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width*170;
    
    liveScoreLabel = CCLabelTTF::create(langManager->Translate(STRING_LIVE_SCORE)->getCString(), "Georgia", fontSizeLabel, CCSizeMake(labelWidth, 0), kCCTextAlignmentCenter);
    liveScoreLabel->setColor(ccc3(0, 0, 0));
    
    //===========================
    //Create Buttons
    //===========================
    //liveScoreButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), langManager->Translate(STRING_ON)->getCString(), OPTIONS_FONT_SIZE2);
    //liveScoreOnButton->setScale(0.65f);
    
    liveScoreOnButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, NULL, langManager->Translate(STRING_ON)->getCString(), fontSizeBtn);
    liveScoreOffButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, NULL, langManager->Translate(STRING_OFF)->getCString(), fontSizeBtn);
    
    liveScoreButton = CCMenuItemToggle::createWithTarget(this, menu_selector(OptionsButtonsLayer::liveScoreBtnCallback), liveScoreOffButton, liveScoreOnButton, NULL);
    //liveScoreOffButton->setScale(0.65f);
}

void OptionsButtonsLayer::createMenus(){
    //===========================
    //Create menus
    //===========================
    mainMenu = CCMenu::create(pvpButton,pvcButton, easyButton,mediumButton,hardButton,veryHardButton, hardestButton,crossButton,straightButton, blackWhiteButton,redGreenButton,redBlueButton,woodButton, othelloButton,showMovesButton, liveScoreButton, NULL);
    
    //menu2 = CCMenu::create(skinButton, NULL);
    
    backBtnMenu = CCMenu::create(backButton, NULL);
    
}

//===========================
//SET POSITIONS METHODS
//===========================

void OptionsButtonsLayer::setGameModeItemsPositions(){
    //==============================
    //Set Label position
    //==============================
    //CCLOG("MODE offset: %f", 30/visHeight*100);
    
    modeLabel->setPosition(ccp(VisibleRect::center().x,VisibleRect::top().y - modeLabel->getContentSize().height - distOffLabel));
    
    //==============================
    //Set Buttons position
    //==============================
    pvcButton->setPosition(ccp(VisibleRect::center().x - pvcButton->getContentSize().width/2, modeLabel->getPositionY() - pvcButton->getContentSize().height/2 - distOffBtn));
    
    pvpButton->setPosition(ccp(VisibleRect::center().x + pvpButton->getContentSize().width/2, modeLabel->getPositionY() - pvpButton->getContentSize().height/2 - distOffBtn));
    
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(modeLabel,0);
    
    if(visWidth/designWidth != 1){
        //backButton->setPosition(ccp(lineHeader[0]->boundingBox().origin.x + backButton->getContentSize().width/3.8, lineHeader[0]->getPositionY()));
        
        backButton->setPosition(ccp(lineHeader[0]->boundingBox().origin.x, lineHeader[0]->getPositionY()));
        
    }else{
        backButton->setPosition(ccp(lineHeader[0]->boundingBox().origin.x, lineHeader[0]->getPositionY()));
    }
}

void OptionsButtonsLayer::setDiffItemsPositions(){
    //===========================
    //Set Label position
    //===========================
    difficultyLabel->setPosition(ccp(VisibleRect::center().x,pvcButton->getPositionY() - difficultyLabel->getContentSize().height - distOffLabel));
    
    //==============================
    //Set Buttons position
    //==============================
    easyButton->setPosition(ccp(pvcButton->boundingBox().origin.x + pvcButton->getContentSize().width/2 - easyButton->getContentSize().width/2, difficultyLabel->getPositionY() - easyButton->getContentSize().height/2 - distOffBtn));
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
    startFormLabel->setPosition(ccp(VisibleRect::center().x,veryHardButton->getPositionY() - startFormLabel->getContentSize().height - distOffLabel));
    
    //==============================
    //Set Buttons position
    //==============================
    crossButton->setPosition(ccp(veryHardButton->getPositionX(), startFormLabel->getPositionY() - crossButton->getContentSize().height/2 - distOffBtn));
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
    colorsLabel->setPosition(ccp(VisibleRect::center().x,crossButton->getPositionY() - colorsLabel->getContentSize().height - distOffLabel));
    
    //==============================
    //Set Buttons position
    //==============================
    blackWhiteButton->setPosition(ccp(easyButton->getPositionX(), colorsLabel->getPositionY() - blackWhiteButton->getContentSize().height/2 - distOffBtn));
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
    boardLabel->setPosition(ccp(VisibleRect::center().x,blackWhiteButton->getPositionY() - boardLabel->getContentSize().height - distOffLabel));
    
    //==============================
    //Set Button position
    //==============================
    
    woodButton->setPosition(ccp(crossButton->getPositionX(), boardLabel->getPositionY()- woodButton->getContentSize().height/2 - distOffBtn));
    othelloButton->setPosition(ccp(straightButton->getPositionX(), woodButton->getPositionY()));
    
    //skinButton->setPosition(ccp(VisibleRect::center().x, boardLabel->getPositionY()- skinButton->getContentSize().height/2 - dist));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(boardLabel,4);
}

void OptionsButtonsLayer::setMovesItemsPositions(){
    //==============================
    //Set Label position
    //==============================
    movesLabel->setPosition(ccp(VisibleRect::center().x - movesLabel->getContentSize().width/1.7,woodButton->getPositionY() - movesLabel->getContentSize().height/1.6 - distOffLabel));
    
    //==============================
    //Set Button position
    //==============================
    //movesButton->setPosition(ccp(movesLabel->boundingBox().origin.x + movesLabel->getContentSize().width/2, movesLabel->boundingBox().origin.y - movesButton->getContentSize().height/3.5 - dist));
    
    showMovesButton->setPosition(ccp(movesLabel->boundingBox().origin.x + movesLabel->getContentSize().width/2, movesLabel->boundingBox().origin.y - showMovesButton->getContentSize().height/3.5 - distOffBtn));
    
    //============================================
    //Create Set Positions and Add Marker to Layer
    //============================================
    createMarkerLine(movesLabel,5);

}

void OptionsButtonsLayer::setLiveScoreItemsPositions(){
    //==============================
    //Set LiveScore Items position
    //==============================
    liveScoreLabel->setPosition(ccp(VisibleRect::center().x + movesLabel->getContentSize().width/1.7,lineHeader[SHOW_MOVES_HEADER_INDEX]->getPositionY() + liveScoreLabel->getContentSize().height/2));
    
    //==============================
    //Set Buttons position
    //==============================
    liveScoreButton->setPosition(ccp(liveScoreLabel->boundingBox().origin.x + liveScoreLabel->getContentSize().width/2, showMovesButton->getPositionY()));

}

void OptionsButtonsLayer::setMenusPositions(){
    
    mainMenu->setPosition(CCPointZero);
    //menu2->setPosition(CCPointZero);
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
    
    woodButton->setTag(WOOD_SKIN_BTN_TAG);
    othelloButton->setTag(OTHELLO_SKIN_BTN_TAG);
   
}

void OptionsButtonsLayer::setActiveButtons(){
    
    bool pvcIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("pvcIsEnabled",PVC_BTN_TAG);
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
    
    bool straightFormIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("straightFormIsEnabled",STRAIGHT_BTN_TAG);
    
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
    
    bool showMoveIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("showMoveIsEnabled");
    
    if(showMoveIsEnabled){
        showMovesButton->setSelectedIndex(SHOW_MOVE_ON_BTN_TAG);
    }else{
        showMovesButton->setSelectedIndex(SHOW_MOVE_OFF_BTN_TAG);
    }
    
    bool liveScoreIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("liveScoreIsEnabled");
    
    if (liveScoreIsEnabled) {
        liveScoreButton->setSelectedIndex(LIVE_SCORE_ON_BTN_TAG);
    }else{
        liveScoreButton->setSelectedIndex(LIVE_SCORE_OFF_BTN_TAG);
    }
    
     othelloIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("othelloIsEnabled",WOOD_SKIN_BTN_TAG);
    
    if (othelloIsEnabled) {
        //boardButton->setSelectedIndex(OTHELLO_SKIN_BTN_TAG);
        woodButton->setSelectedBtn(false);
        othelloButton->setSelectedBtn(true);
        
    }else{
        //boardButton->setSelectedIndex(WOOD_SKIN_BTN_TAG);
        woodButton->setSelectedBtn(true);
        othelloButton->setSelectedBtn(false);
    }
    
    CCLOG("SKIN: %i", othelloIsEnabled);
    
    
    //CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);

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
    
    std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), "Test_Res");
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    
    /*
    if (boardButton->getSelectedIndex()) {
        //CCLOG("OTHELLO ON %i", boardButton->getSelectedIndex());
        CCUserDefault::sharedUserDefault()->setBoolForKey("othelloIsEnabled", true);
        
        this->setResources(NORMAL_RES_OTHELLO, SMALL_RES_OTHELLO);
        this->setResources(NORMAL_RES_WOOD, SMALL_RES_WOOD);
        
        
    }else{
        CCUserDefault::sharedUserDefault()->setBoolForKey("othelloIsEnabled", false);
        //CCLOG("WOOD ON %i", boardButton->getSelectedIndex());
        
        this->setResources(NORMAL_RES_WOOD, SMALL_RES_WOOD);
        this->setResources(NORMAL_RES_OTHELLO, SMALL_RES_OTHELLO);
    }
    
    CCUserDefault::sharedUserDefault()->flush();
    */
    
    MenuButton* pMenuItem = (MenuButton *)(pSender);
    int tag = (int)pMenuItem->getTag();
    
    //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("background.plist");
    
    
    switch (tag) {
        case WOOD_SKIN_BTN_TAG:
            othelloButton->setSelectedBtn(false);
            woodButton->setSelectedBtn(true);
            
            this->setResources(SMALL_RES_WOOD, NORMAL_RES_WOOD, BIG_RES_WOOD, BIGGEST_RES_WOOD);
            this->setResources(SMALL_RES_OTHELLO, NORMAL_RES_OTHELLO, BIG_RES_OTHELLO, BIGGEST_RES_OTHELLO);
            
            CCUserDefault::sharedUserDefault()->setBoolForKey("othelloIsEnabled", false);
            
            break;
        case OTHELLO_SKIN_BTN_TAG:
            othelloButton->setSelectedBtn(true);
            woodButton->setSelectedBtn(false);

            this->setResources(SMALL_RES_OTHELLO, NORMAL_RES_OTHELLO, BIG_RES_OTHELLO, BIGGEST_RES_OTHELLO);
            this->setResources(SMALL_RES_WOOD, NORMAL_RES_WOOD, BIG_RES_WOOD, BIGGEST_RES_WOOD);
            
            CCUserDefault::sharedUserDefault()->setBoolForKey("othelloIsEnabled", true);
            
            break;
        default:
            break;
    }
    
    CCUserDefault::sharedUserDefault()->flush();
    
    
    this->setResources(SMALL_RES_MAIN, NORMAL_RES_MAIN, BIG_RES_MAIN, BIGGEST_RES_MAIN);
    
    
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pawns.plist");
    
    CCScene *optionsScene = OptionsScene::create();
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.1f, optionsScene,false));
    
}

void OptionsButtonsLayer::movesBtnCallback(cocos2d::CCObject *pSender){
   
    if(showMovesButton->getSelectedIndex()){
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("showMoveIsEnabled", true);
        
    }else{
        CCUserDefault::sharedUserDefault()->setBoolForKey("showMoveIsEnabled", false);
        
    }
    
    CCUserDefault::sharedUserDefault()->flush();
}

void OptionsButtonsLayer::liveScoreBtnCallback(cocos2d::CCObject *pSender){
    
    if (liveScoreButton->getSelectedIndex()) {
       
        CCUserDefault::sharedUserDefault()->setBoolForKey("liveScoreIsEnabled", true);
        
    }else{
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("liveScoreIsEnabled", false);
        
    }
    
    CCUserDefault::sharedUserDefault()->flush();
}

void OptionsButtonsLayer::setResources(const char *resSmall, const char* resNormal, const char* resBig, const char* resBiggest){
    
    if(screenSize.height > 1500){
        resDirOrders.push_back(resBiggest);
    }else if(screenSize.height > 960){
        resDirOrders.push_back(resBig);
    }else if(screenSize.height > 480){
        resDirOrders.push_back(resNormal);
    }else{
        resDirOrders.push_back(resSmall);
    }
    /*
    if(screenSize.height > 1024){
        resDirOrders.push_back(resNormal);
    }else{
        resDirOrders.push_back(resSmall);
    }*/
}

void OptionsButtonsLayer::keyBackClicked(){
    
    CCScene *backScene = MenuScene::create();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, backScene,true));
}

void OptionsButtonsLayer::backBtnCallback(cocos2d::CCObject *pSender){
    this->keyBackClicked();
}

void OptionsButtonsLayer::setFontSize(){
    
    int fontOptionLabel, fontOptionBtn, fontOptionDiff;
    
    if(designHeight <= 960){
        fontOptionLabel = 28;
        fontOptionBtn = 16;
        fontOptionDiff = 20;
    }else{
        fontOptionLabel = 32;
        fontOptionBtn = 20;
        fontOptionDiff = 24;
    }
    
    this->fontSizeLabel = visHeight/designHeight * fontOptionLabel;
    this->fontSizeBtn = visHeight/designHeight * fontOptionBtn;
    this->fontSizeDiff = visHeight/designHeight * fontOptionDiff;
}

void OptionsButtonsLayer::setOptionOffsets(){
    
    int smallerDesignHeight = 960;
    int optionOffBtn = designHeight <= smallerDesignHeight ? 15: 15;
    int optionOffLabel = designHeight <= smallerDesignHeight ? 30 : 30;
    
    distOffBtn = visHeight/designHeight * optionOffBtn;
    distOffLabel = visHeight/designHeight * optionOffLabel;
}

void OptionsButtonsLayer::setItemsScale(){
    
    if (isHighIphone) {
        float scale;
        if (othelloIsEnabled) {
            scale = 0.8;
        }else{
            scale = 0.9;
        }
        
            
            pvpButton->setScale(scale);
            pvcButton->setScale(scale);
            
            easyButton->setScale(scale);
            mediumButton->setScale(scale);
            hardButton->setScale(scale);
            veryHardButton->setScale(scale);
            hardestButton->setScale(scale);
            
            crossButton->setScale(scale);
            straightButton->setScale(scale);
            
            blackWhiteButton->setScale(scale);
            redGreenButton->setScale(scale);
            redBlueButton->setScale(scale);
            
            woodButton->setScale(scale);
            othelloButton->setScale(scale);
            
            showMovesButton->setScale(scale);
            liveScoreButton->setScale(scale);
            
            backButton->setScale(scale);
       
    }
}
