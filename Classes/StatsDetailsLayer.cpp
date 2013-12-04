//
//  StatsDetailsLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 27.11.2013.
//
//

#include "StatsDetailsLayer.h"
#include "VisibleRect.h"
#include "MenuScene.h"
#include "StatsScene.h"
#include "StatsResultsLayer.h"


bool StatsDetailsLayer::init(){
    
    if(!CCLayer::init()){
        return false;
    }else{
        
        visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
        designSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
        
        langManager = LanguageManager::create();        
        
        blackColor = ccs("stone_black.png");
        whiteColor = ccs("stone_white.png");
        
        this->getStats();
        
        this->setDetailsOffsets();
        
        this->createItems();
        
        this->setItemsPosition();
        
        this->addItemsToLayer();
        
        this->createPawnsImages();
        
        this->createLabelStats();
        
        

        
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
    
    
    allLabelV = CCLabelTTF::create("ALL", "Georgia", 26);
    allLabelV->setColor(ccc3(0, 0, 0));
    
    hardestLabel = CCLabelTTF::create(langManager->Translate(STRING_THE_HARDEST)->getCString(), "Georgia", 20);
    hardestLabel->setColor(ccc3(0, 0, 0));
    
    veryHardLabel = CCLabelTTF::create(langManager->Translate(STRING_VERY_HARD)->getCString(), "Georgia", 20);
    veryHardLabel->setColor(ccc3(0, 0, 0));
    
    hardLabel = CCLabelTTF::create(langManager->Translate(STRING_HARD)->getCString(), "Georgia", 20);
    hardLabel->setColor(ccc3(0, 0, 0));
    
    mediumLabel = CCLabelTTF::create(langManager->Translate(STRING_MEDIUM)->getCString(), "Georgia", 20);
    mediumLabel->setColor(ccc3(0, 0, 0));
    
    easyLabel = CCLabelTTF::create(langManager->Translate(STRING_EASY)->getCString(), "Georgia", 20);
    easyLabel->setColor(ccc3(0, 0, 0));
    
    
    
    statsHeaderMenu = CCMenu::create(backButton, NULL);
    
}

void StatsDetailsLayer::setItemsPosition(){
    
    this->setHeaderPosition();
    
    float horizOffset = 100;
    float vertOffset = 75;
    
    wonLabel->setPosition(ccp(VisibleRect::center().x - horizOffset, headerLabel->getPositionY() - labelOffFromHeader));
    lostLabel->setPosition(ccp(wonLabel->getPositionX() + horizOffset, wonLabel->getPositionY()));
    tiedLabel->setPosition(ccp(lostLabel->getPositionX() + horizOffset, wonLabel->getPositionY()));
    allLabelH->setPosition(ccp(tiedLabel->getPositionX() + horizOffset, wonLabel->getPositionY()));
    
    
    allLabelV->setPosition(ccp(wonLabel->getPositionX() - horizOffset, wonLabel->getPositionY()- vertOffset));
    hardestLabel->setPosition(ccp(allLabelV->getPositionX(), allLabelV->getPositionY() - vertOffset));
    veryHardLabel->setPosition(ccp(allLabelV->getPositionX(), hardestLabel->getPositionY() - vertOffset));
    hardLabel->setPosition(ccp(allLabelV->getPositionX(), veryHardLabel->getPositionY() - vertOffset));
    mediumLabel->setPosition(ccp(allLabelV->getPositionX(), hardLabel->getPositionY() - vertOffset));
    easyLabel->setPosition(ccp(allLabelV->getPositionX(), mediumLabel->getPositionY() - vertOffset));
    
    statsHeaderMenu->setPosition(CCPointZero);
    
}

void StatsDetailsLayer::addItemsToLayer(){
    
    this->addChild(headerLabel);
    this->addChild(lineHeader);
    
    this->addChild(wonLabel);
    this->addChild(lostLabel);
    this->addChild(tiedLabel);
    this->addChild(allLabelH);
    
    this->addChild(allLabelV);
    this->addChild(hardestLabel);
    this->addChild(veryHardLabel);
    this->addChild(hardLabel);
    this->addChild(mediumLabel);
    this->addChild(easyLabel);
    
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
    CCScene *statsResultScene = StatsScene::create();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, statsResultScene,true));
    
    /*
    StatsResultsLayer* resLayer = StatsResultsLayer::create();
    this->getParent()->addChild(resLayer,1);
    this->removeFromParent();*/
    
    /*
    StatsResultsLayer *resLayer;
    resLayer->setTag(0);
    CCScene *mainStatsScene = StatsScene::create(resLayer);
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, mainStatsScene,true));*/
    
}

void StatsDetailsLayer::backBtnCallback(cocos2d::CCObject *pSender){
     this->keyBackClicked();
}

void StatsDetailsLayer::countStats(){
    
}

void StatsDetailsLayer::setDetailsOffsets(){
    
    int offFromTop = designSize.height <= 960 ? 80:90;
    int offFromHeader = designSize.height <=960 ? 100:110;
    
    this->labelOffFromTop = visibleSize.height/designSize.height * offFromTop;
    this->labelOffFromHeader = visibleSize.height/designSize.height * offFromHeader;
}

void StatsDetailsLayer::createPawnsRow(int number){
    
    float scale = 0.52f;
    
   
    CCSprite* tab[number];
    
    for(int i=0; i<number;i++){
        if (i%2==0) {
            tab[i] = CCSprite::create(blackColor->getCString());
        }else{
            tab[i] = CCSprite::create(whiteColor->getCString());
        }
        tab[i]->setScale(scale);
    }
    
    float offFromLabel = tab[0]->getContentSize().height/3.5;
    
    
    switch (number) {
        case 1:
            tab[0]->setPosition(ccp(easyLabel->getPositionX(), easyLabel->getPositionY() - offFromLabel));
            
            this->addChild(tab[0],2);
            break;
            
        case 2:
            tab[0]->setPosition(ccp(mediumLabel->getPositionX() - tab[0]->getContentSize().width/8, mediumLabel->getPositionY() - offFromLabel));
            tab[1]->setPosition(ccp(mediumLabel->getPositionX() + tab[0]->getContentSize().width/8, mediumLabel->getPositionY() - offFromLabel));
            this->addChild(tab[0],2);
            this->addChild(tab[1],2);
            
            break;
            
        case 3:
             tab[0]->setPosition(ccp(hardLabel->getPositionX() - tab[0]->getContentSize().width/4, hardLabel->getPositionY() - offFromLabel));
            tab[1]->setPosition(ccp(hardLabel->getPositionX(), hardLabel->getPositionY() - offFromLabel));
            tab[2]->setPosition(ccp(hardLabel->getPositionX() + tab[0]->getContentSize().width/4, hardLabel->getPositionY() - offFromLabel));
            
            this->addChild(tab[0],1);
            this->addChild(tab[1],2);
            this->addChild(tab[2],3);

            break;
            
        case 4:
            tab[0]->setPosition(ccp(veryHardLabel->getPositionX() - tab[0]->getContentSize().width/3, veryHardLabel->getPositionY() - offFromLabel));
            tab[1]->setPosition(ccp(veryHardLabel->getPositionX() - tab[0]->getContentSize().width/9, veryHardLabel->getPositionY() - offFromLabel));
            tab[2]->setPosition(ccp(veryHardLabel->getPositionX() + tab[0]->getContentSize().width/9, veryHardLabel->getPositionY() - offFromLabel));
            tab[3]->setPosition(ccp(veryHardLabel->getPositionX() + tab[0]->getContentSize().width/3, veryHardLabel->getPositionY() - offFromLabel));
            
            
            this->addChild(tab[0],1);
            this->addChild(tab[1],2);
            this->addChild(tab[2],3);
            this->addChild(tab[3],4);
            
            
            break;
            
        case 5:
            
            tab[0]->setPosition(ccp(hardestLabel->getPositionX() - tab[0]->getContentSize().width/2, hardestLabel->getPositionY() - offFromLabel));
            tab[1]->setPosition(ccp(hardestLabel->getPositionX() - tab[0]->getContentSize().width/4, hardestLabel->getPositionY() - offFromLabel));
            tab[2]->setPosition(ccp(hardestLabel->getPositionX(), hardestLabel->getPositionY() - offFromLabel));
            tab[3]->setPosition(ccp(hardestLabel->getPositionX() + tab[0]->getContentSize().width/4, hardestLabel->getPositionY() - offFromLabel));
            tab[4]->setPosition(ccp(hardestLabel->getPositionX() + tab[0]->getContentSize().width/2, hardestLabel->getPositionY() - offFromLabel));
            
            
            this->addChild(tab[0],1);
            this->addChild(tab[1],2);
            this->addChild(tab[2],3);
            this->addChild(tab[3],4);
            this->addChild(tab[4],5);

            
            break;
        default:
            break;
    }

    
}

void StatsDetailsLayer::createPawnsImages(){
    
    this->createPawnsRow(1);
    this->createPawnsRow(2);
    this->createPawnsRow(3);
    this->createPawnsRow(4);
    this->createPawnsRow(5);
    
}

void StatsDetailsLayer::getStats(){
    
        
    tabResultValue[0][0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("won_games");
    tabResultValue[0][1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("lost_games");
    tabResultValue[0][2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("draw_games");
    tabResultValue[0][3] = CCUserDefault::sharedUserDefault()->getIntegerForKey("total_games");
    
    
    tabResultValue[1][0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hardest_won_games");
    tabResultValue[1][1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hardest_lost_games");
    tabResultValue[1][2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hardest_draw_games");
    tabResultValue[1][3] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hardest_total_games");
    
    
    tabResultValue[2][0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("veryHard_won_games");
    tabResultValue[2][1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("veryHard_lost_games");
    tabResultValue[2][2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("veryHard_draw_games");
    tabResultValue[2][3] = CCUserDefault::sharedUserDefault()->getIntegerForKey("veryHard_total_games");
    
    
    tabResultValue[3][0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hard_won_games");
    tabResultValue[3][1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hard_lost_games");
    tabResultValue[3][2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hard_draw_games");
    tabResultValue[3][3] = CCUserDefault::sharedUserDefault()->getIntegerForKey("hard_total_games");
    
   
    
    tabResultValue[4][0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("medium_won_games");
    tabResultValue[4][1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("medium_lost_games");
    tabResultValue[4][2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("medium_draw_games");
    tabResultValue[4][3] = CCUserDefault::sharedUserDefault()->getIntegerForKey("medium_total_games");
    
    
    
    tabResultValue[5][0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("easy_won_games");
    tabResultValue[5][1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("easy_lost_games");
    tabResultValue[5][2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("easy_draw_games");
    tabResultValue[5][3] = CCUserDefault::sharedUserDefault()->getIntegerForKey("easy_total_games");
    
    
}

void StatsDetailsLayer::setStats(){
    
}

void StatsDetailsLayer::createLabelStats(){
    
    float begPosX = wonLabel->getPositionX();
    float begPosY = allLabelV->getPositionY();
    int offsetX = 0;
    int offsetY = 0;
    
    CCString* result;
    
    for (int x =0; x<6; x++) {
        
        offsetX = 0;
                
        for (int y=0; y<4; y++) {
            result = CCString::createWithFormat("%i", tabResultValue[x][y]);
            tabResult[x][y]=CCLabelTTF::create(result->getCString(), "Georgia", 24);
            tabResult[x][y]->setColor(ccc3(0, 0, 0));
            
            tabResult[x][y]->setPosition(ccp(begPosX + offsetX, begPosY - offsetY));
            
            this->addChild(tabResult[x][y]);
            
            offsetX += 100;
        }
        
        offsetY +=75;
    }    
    
}
