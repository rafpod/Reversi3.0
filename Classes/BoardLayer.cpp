//
//  BoardLayer.cpp
//  ReversiGL
//
//  Created by RafalP on 23.10.2013.
//
//

#include "BoardLayer.h"
#include "VisibleRect.h"
#include "CCAlertView.h"
#include "MenuScene.h"
#include "AI.h"
#include "OptionButtonDefinitions.h"

using namespace cocos2d;

#define TILE_SIZE 60
#define SCORE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 24)
#define BOARD_MENU_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 22)
#define BTN_LEFT    1
#define BTN_RIGHT   2

#define ST_RUNNING	1
#define ST_OVER		2

#define DIALOG_OFF  0
#define DIALOG_ON   1

#define UPDATE_ON  1
#define UPDATE_OFF 2

#define HUMAN 1
#define AI    0
#define SELECTED_BOARD      1
#define UNSELECTED_BOARD    0


struct field startpos[2]={
    {
        {
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','X','O','.','.','.'},
            {'.','.','.','O','X','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'}
        },
        0	// turn
    },
    {
        {
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','X','X','.','.','.'},
            {'.','.','.','O','O','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'}
        },
        0	// turn
    }
};

//====================================================================================================
//                                      METHODS
//===================================================================================================


bool BoardLayer::init(){
    
    if (!CCLayer::init()) {
        return false;
    }else{
        
        this->initVariables();
       
        this->setOptionsPreferences();
        
        this->createItems();
        
        CCLOG("(ContentSizeBoard)X is: %f and Y is: %f", boardSprite->getContentSize().width, boardSprite->getContentSize().height);        
        
        this->setCoordToResolution();
        
        this->setBoardPosition();
        
        CCLOG("othello? %i",othelloIsEnabled);
        
        
        if (othelloIsEnabled) {
            /*widthBoard = boardSprite->getContentSize().width -2*50; //542, 2*42
            CCLOG("widthBoardCoord: %f", widthBoard);
            //float tileS = (boardSprite->getContentSize().width * 0.9)/8;
            tileSize = widthBoard/8*0.9;
            originBoardX = boardSprite->boundingBox().origin.x + 50.0f; //42
            originBoardY = boardSprite->boundingBox().origin.y + 50.0f; //45
            anchorPointSprite = ccp(0.2, 0.2);*/
            
            widthBoard = boardSprite->getContentSize().width;
            originBoardX = boardSprite->boundingBox().origin.x;
            originBoardY = boardSprite->boundingBox().origin.y;
            tileSize = floorf((boardSprite->getContentSize().width * scaleSprite)/8);
            tileSize -= 1;
            CCLOG("TILESIZE FLOOR %f", tileSize);
            anchorPointSprite = ccp(0.05, 0.09);
            
            CCLOG("originBoardXCoord: %f", originBoardX);
            CCLOG("originBoardYCoord: %f", originBoardY);
            CCLOG("tileSCoord: %f", tileSize);
        }else{
            
            widthBoard = boardSprite->getContentSize().width;
            originBoardX = boardSprite->boundingBox().origin.x;
            originBoardY = boardSprite->boundingBox().origin.y;
            
            if (visibleSize.width <= boardSprite->getContentSize().width + 10)
            {
                //iphone 1136
                tileSize = 53.35; //boardSprite->getContentSize().width*0.8/8 =54,4;
                anchorPointSprite = ccp(0.09, 0.1);
            }
            else
            {
                //tileSize = 60; //boardSprite->getContentSize().width*0.9/8 =61,2;
                tileSize = floorf((boardSprite->getContentSize().width * scaleSprite)/8);
                tileSize -= 1;
                CCLOG("TILESIZE FLOOR %f", tileSize);
                anchorPointSprite = ccp(0.05, 0.09);
                
            }
            
            CCLOG("widthBoardCoord: %f", widthBoard);
            CCLOG("originBoardXCoord: %f", originBoardX);
            CCLOG("originBoardYCoord: %f", originBoardY);
            CCLOG("tileSCoord: %f", tileSize);

        }
        /*
        widthBoard = boardSprite->getContentSize().width -2*50; //542, 2*42
        CCLOG("widthBoardCoord: %f", widthBoard);
        //float tileS = (boardSprite->getContentSize().width * 0.9)/8;
        tileSize = widthBoard/8*0.9;
        originBoardX = boardSprite->boundingBox().origin.x + 50.0f; //42
        originBoardY = boardSprite->boundingBox().origin.y + 50.0f; //45
        anchorPointSprite = ccp(0.18, 0.18);
        
        CCLOG("originBoardXCoord: %f", originBoardX);
        CCLOG("originBoardYCoord: %f", originBoardY);
        CCLOG("tileSCoord: %f", tileSize);
        */
        this->setItemsPositions();
        
        this->addItemsToBoard();
        
        this->setTouchEnabled(true);
        
        //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        
        this->newGame();
        
        this->schedule(schedule_selector(BoardLayer::updateBoard), 0.1);
        
        this->setKeypadEnabled(true);
        
        return true;
    }
}

void BoardLayer::initVariables(){
    playeris = 1;
    xt=0;
    yt=0;
    xl=0;
    yl=0;
    thinking=0;
    loaded_colors=0;
    current_cross=0;
    passing=0;
    
    scaleSprite = 1.0f;
    
    whoseMove = AI;
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //bottom left
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    langManager = LanguageManager::create();
}

void BoardLayer::setOptionsPreferences(){
    
    cross = CCUserDefault::sharedUserDefault()->getBoolForKey("straightFormIsEnabled",STRAIGHT_BTN_TAG);
    mode = CCUserDefault::sharedUserDefault()->getBoolForKey("pvcIsEnabled",PVC_BTN_TAG);
    diff = CCUserDefault::sharedUserDefault()->getIntegerForKey("difficulty",EASY_BTN_TAG);
    stoneColor = CCUserDefault::sharedUserDefault()->getIntegerForKey("colorBtn",BL_WHITE_BTN_TAG);
    showMoves = CCUserDefault::sharedUserDefault()->getBoolForKey("showMoveIsEnabled",SHOW_MOVE_OFF_BTN_TAG);
    liveScore = CCUserDefault::sharedUserDefault()->getBoolForKey("liveScoreIsEnabled", LIVE_SCORE_OFF_BTN_TAG);
    othelloIsEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey("othelloIsEnabled",WOOD_SKIN_BTN_TAG);
    
    switch (stoneColor) {
        case GR_RED_BTN_TAG:
            colorFileNameFirst = "stone_green.png";            
            colorFileNameSecond = "stone_red.png";
            postfixColor = "gr";
            
            colorScBrdLeftNorm = "button_red_0.png";
            colorScBrdLeftSel = "button_red_1.png";
            
            colorScBrdRightNorm = "button_green_0.png";
            colorScBrdRightSel = "button_green_1.png";
            
            break;
        case BLUE_RED_BTN_TAG:
            colorFileNameFirst = "stone_blue.png";
            colorFileNameSecond = "stone_red.png";
            postfixColor = "br";
            
            colorScBrdLeftNorm = "button_red_0.png";
            colorScBrdLeftSel = "button_red_1.png";
            
            colorScBrdRightNorm = "button_blue_0.png";
            colorScBrdRightSel = "button_blue_1.png";
            
            
            break;
        default:
            colorFileNameFirst = "stone_white.png";
            colorFileNameSecond = "stone_black.png";
            postfixColor = "wb";
            
            colorScBrdLeftNorm = "button_black_0.png";
            colorScBrdLeftSel = "button_black_1.png";
            
            colorScBrdRightNorm = "button_white_0.png";
            colorScBrdRightSel = "button_white_1.png";
            
            break;
    }
}


void BoardLayer::createItems(){
    
    this->createBoard();
    
    this->createScoreBoards();
    
    this->createMenuButtons();

}

void BoardLayer::setItemsPositions(){
        
    //this->setBoardPosition();
    
    this->setScoreBoardPosition();
    
    this->setMenuButtonPosition();

}

void BoardLayer::addItemsToBoard(){
    
    this->addBoardToLayer();
    
    this->addScoreBoardToLayer();
    
    this->addMenuToLayer();
    
}

void BoardLayer::setCoordToResolution(){
    
    if (othelloIsEnabled) {
        if (visibleSize.width <= boardSprite->getContentSize().width + 10)
        {
            //iphone 1136
            boardSprite->setScaleX(0.8);
            boardSprite->setScaleY(0.8);
            
            shadowSprite->setScaleY(0.79);
            shadowSprite->setScaleX(0.8);
            
            scaleSprite = 0.841f;
            tileSize = 53.35; //boardSprite->getContentSize().width*0.8/8 =54,4;
            anchorPointSprite = ccp(0.09, 0.1);
            
            diffXForFirstItem = 10;
            diffXForLastItem = -15;
            
            addDistBoardY = 100;
        }
        else
        {
            
            //Scale 0.9
            boardSprite->setScaleX(0.9);
            boardSprite->setScaleY(0.9);
            
            shadowSprite->setScaleY(0.89);
            shadowSprite->setScaleX(0.9);
            
            scaleSprite = 0.9f;
           // tileSize = 60; //boardSprite->getContentSize().width*0.9/8 =61,2;
            tileSize = floorf((boardSprite->getContentSize().width)/8);
            tileSize -= 1;
            anchorPointSprite = ccp(0.2, 0.2);
            
            CCLOG("TILESIZE FLOOR %f", tileSize);
            //anchorPointSprite = ccp(0.05, 0.09);
            
            
            diffXForFirstItem = 10;
            diffXForLastItem = 10;
            
            addDistBoardY = 100;
            
            
        }

    }else{
        if (visibleSize.width <= boardSprite->getContentSize().width + 10)
        {
            //iphone 1136
            boardSprite->setScaleX(0.8);
            boardSprite->setScaleY(0.8);
            
            shadowSprite->setScaleY(0.79);
            shadowSprite->setScaleX(0.8);
            
            scaleSprite = 0.841f;
            tileSize = 53.35; //boardSprite->getContentSize().width*0.8/8 =54,4;
            anchorPointSprite = ccp(0.09, 0.1);
            
            diffXForFirstItem = 10;
            diffXForLastItem = -15;
            
            addDistBoardY = 100;
        }
        else
        {
            //Scale 0.9
            boardSprite->setScaleX(0.9);
            boardSprite->setScaleY(0.9);
            
            shadowSprite->setScaleY(0.89);
            shadowSprite->setScaleX(0.9);
            
            scaleSprite = 0.9f;
            //tileSize = 60; //boardSprite->getContentSize().width*0.9/8 =61,2;
            tileSize = floorf((boardSprite->getContentSize().width * scaleSprite)/8);
            tileSize -= 1;
            CCLOG("TILESIZE FLOOR %f", tileSize);
            anchorPointSprite = ccp(0.05, 0.09);
            
            diffXForFirstItem = 10;
            diffXForLastItem = 10;
            
            addDistBoardY = 100;
        }

    }
}

//=======================================
//Methods of 3 Menu Buttons: undo, new i menu
//=======================================

void BoardLayer::undobBtnCallback(CCObject *pSender){
    
    if(status==ST_RUNNING && dialogStatus == DIALOG_OFF)
    {
        if (histpos>0) curpos=viewpos=history[--histpos];
        thinking=0;
        //createBeginningPawnsPosition();
        undoUpdatePositions();
    }
}

void BoardLayer::newBtnCallback(CCObject *pSender){
    
    if (dialogStatus == DIALOG_OFF)
    {
        CCAlertView *alertQuestion = CCAlertView::create(langManager->Translate(STRING_ATTENTION)->getCString(), langManager->Translate(STRING_QUESTION)->getCString(), langManager->Translate(STRING_RATENO)->getCString(), langManager->Translate(STRING_RATEYES)->getCString(), this, callfuncO_selector(BoardLayer::dialogBackButton), callfuncO_selector(BoardLayer::newGame));
        this->addChild(alertQuestion, 100);
        dialogStatus = DIALOG_ON;
    }
}

void BoardLayer::menuBtnCallback(CCObject *pSender){
    
    /*
    for (int x=7; x>=0; x--) {
        for (int y=0; y<8; y++) {
            uiv[x][y]->stopAllActions();
        }
    }
    */
    this->stopAllActions();
    
    CCScene *menuScene = MenuScene::create();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, menuScene,false));
    
    
   // CCDirector::sharedDirector()->end();
    //exit(0);
}
//=======================================
//END
//=======================================

void BoardLayer::dialogBackButton(CCObject *pSender) {
    dialogStatus = DIALOG_OFF;
}

void BoardLayer::dialogMustPassButton(CCObject *pSender) {
    //do stuff
    dialogStatus = DIALOG_OFF;
    passing =0;
    curpos.turn++;
    histpos++;
    updateActiveMark();
    
    if (showMoves) {
        showMovements();
    }
    
}

void BoardLayer::updateActiveMark(){
    
    if (mode == PVP_BTN_TAG) {
    
        whoseMove = HUMAN;
        
        if(!curpos.turn&1){
            leftScoreBoard->setSelectedBoard(true);
            rightScoreBoard->setSelectedBoard(false);
        }else{
            leftScoreBoard->setSelectedBoard(false);
            rightScoreBoard->setSelectedBoard(true);
        }
    }
    else
    {
        /*
        if (!playeris) {
            leftScoreBoard->setSelectedBoard(true);
            rightScoreBoard->setSelectedBoard(false,false);
        }else{
            leftScoreBoard->setSelectedBoard(false,false);
            rightScoreBoard->setSelectedBoard(true);

        }
         */
        
        if(!playeris) //if black is human
        {
            if(curpos.turn&1){
                leftScoreBoard->setSelectedBoard(UNSELECTED_BOARD);
                rightScoreBoard->setSelectedBoard(SELECTED_BOARD,AI);
                
                whoseMove = AI;
            }else{
                leftScoreBoard->setSelectedBoard(SELECTED_BOARD);
                rightScoreBoard->setSelectedBoard(UNSELECTED_BOARD,AI);
                
                whoseMove = HUMAN;
            }
        }else{
            if(curpos.turn&1){
                leftScoreBoard->setSelectedBoard(UNSELECTED_BOARD,AI);
                rightScoreBoard->setSelectedBoard(SELECTED_BOARD);
                
                whoseMove = HUMAN;
            }else{
                leftScoreBoard->setSelectedBoard(SELECTED_BOARD,AI);
                rightScoreBoard->setSelectedBoard(UNSELECTED_BOARD);
                
                whoseMove = AI;
            }

        }

    }
    
}
/**
 This method set current results on the score board
 */
void BoardLayer::updateResults(){
    
    counterBlack = 0;
    counterWhite = 0;
    
    for (int x=7; x>=0; x--){
		for (int y=0; y<8; y++){
			if (curpos.pos[x][y]=='X'){ counterWhite++;}
			else if (curpos.pos[x][y]=='O'){ counterBlack++;}
		}
	}
    
    leftScoreBoard->setScore(counterBlack);
    rightScoreBoard->setScore(counterWhite);
    
}


void BoardLayer::gameOverTest(){
    if (status == ST_RUNNING && gameover2(&curpos)) {
        status=ST_OVER;
        
        CCString *results;
        
        if (mode == PVP_BTN_TAG)
        {
            
            
            if(counterBlack == counterWhite)
            {
                results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_DRAW)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
            }
            else
            {
                if(counterBlack > counterWhite)
                {
                    if(stoneColor == BL_WHITE_BTN_TAG){
                        results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_BLACK_WON)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
                    }else{
                        results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_RED_WON)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
                    }
                    
                }
                else
                {
                    switch (stoneColor) {
                        case GR_RED_BTN_TAG:
                            results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_GREEN_WON)->getCString(), rightScoreBoard->getResult(), leftScoreBoard->getResult());
                            break;
                        case BLUE_RED_BTN_TAG:
                            results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_BLUE_WON)->getCString(), rightScoreBoard->getResult(), leftScoreBoard->getResult());
                        default:
                            results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_WHITE_WON)->getCString(), rightScoreBoard->getResult(),leftScoreBoard->getResult());
                            break;
                    }
                    
                }
            }
           
            
        }
        else
        {
            
            int games = CCUserDefault::sharedUserDefault()->getIntegerForKey("total_games");
            games +=1;
            CCUserDefault::sharedUserDefault()->setIntegerForKey("total_games", games);
            
            
            if(counterBlack == counterWhite)
            {
                results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_DRAW)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
                
                int draw = CCUserDefault::sharedUserDefault()->getIntegerForKey("draw_games");
                draw+=1;
                CCUserDefault::sharedUserDefault()->setIntegerForKey("draw_games", draw);
                
            }
            else
            {
                
                if(!playeris) //if black is human
                {
                    if(counterBlack > counterWhite){
                        results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_WON)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
                        
                        int won = CCUserDefault::sharedUserDefault()->getIntegerForKey("won_games");
                        won +=1;
                        CCUserDefault::sharedUserDefault()->setIntegerForKey("won_games", won);
                        
                        
                    }else{
                        results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_LOST)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
                        
                        int lost = CCUserDefault::sharedUserDefault()->getIntegerForKey("lost_games");
                        lost +=1;
                        CCUserDefault::sharedUserDefault()->setIntegerForKey("lost_games", lost);
                        
                    }
                    
                }else{
                    
                    if(counterBlack > counterWhite){
                        results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_LOST)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
                        
                        int lost = CCUserDefault::sharedUserDefault()->getIntegerForKey("lost_games");
                        lost +=1;
                        CCUserDefault::sharedUserDefault()->setIntegerForKey("lost_games", lost);
                        
                    }else{
                        results = CCString::createWithFormat("%s \n %i : %i", langManager->Translate(STRING_WON)->getCString(), leftScoreBoard->getResult(), rightScoreBoard->getResult());
                        
                        int won = CCUserDefault::sharedUserDefault()->getIntegerForKey("won_games");
                        won +=1;
                        CCUserDefault::sharedUserDefault()->setIntegerForKey("won_games", won);
                        
                    }
                    
                }

                
            }
            
            CCUserDefault::sharedUserDefault()->flush();
            
        }
        
        CCAlertView *alertEnding = CCAlertView::create(langManager->Translate(STRING_END)->getCString(), results->getCString(), langManager->Translate(STRING_BACK)->getCString(), langManager->Translate(STRING_NEW)->getCString(), this, callfuncO_selector(BoardLayer::dialogBackButton), callfuncO_selector(BoardLayer::newGame));
        this->addChild(alertEnding, 100);
        dialogStatus = DIALOG_ON;
        
    }

}

void BoardLayer::mustPassTest(){
   
    //if (status==ST_RUNNING && !cpuTurn()) {
    if(status == ST_RUNNING){
        if (passing == 0 && mustpass2(&curpos)) {
            passing=1;
            //==============
            //Here should pop up message box, which inform user that he can't do any move
            //==============
            // CCMessageBox("Text", "Title");
            
            CCString *announce;
            if (mode == PVC_BTN_TAG && whoseMove == AI) {
                announce = langManager->Translate(STRING_AI_MUSTPASS);
            }else{
                announce = langManager->Translate(STRING_MUSTPASS);
            }
            
            CCAlertView *alert = CCAlertView::create(langManager->Translate(STRING_NOTICE)->getCString(), announce->getCString(), langManager->Translate(STRING_OK)->getCString(), this, callfuncO_selector(BoardLayer::dialogMustPassButton));
            this->addChild(alert, 100);
            dialogStatus = DIALOG_ON;
            //curpos.turn++;
            //histpos++;
            //updateActiveMark();
            CCLOG("Can't move %i", passing);
        }else{
            CCLOG("move your body %i", passing);
        }
    }

}

void BoardLayer::updateBoard(float dt){
    
    //=======
    //REMEMBER TO CHECK
    //=======
    updateWithAnimations();
    
    if (dialogStatus == DIALOG_ON) {
        menuBoardButtons->setEnabled(false);
    }else{
        menuBoardButtons->setEnabled(true);
    }
    
    //=================
}

void BoardLayer::createBeginningPawnsPosition(){
    
    for (int x=7; x>=0; x--) {
        for(int y=0;y<8;y++){
            if(uiv[x][y]!=NULL){
                this->removeChild(uiv[x][y]);
            }
            
            if (helperUIV[x][y] !=NULL) {
                this->removeChild(helperUIV[x][y]);
            }
        }
    }
    
    float distFromOriginOnX = 0; //distance from origin of boardSprite, move on columns
    float distFromOriginOnY = 0; // move on rows
    
    //counterBlack = 0;
    //counterWhite = 0;
    
    for (int x=7; x>=0; x--)
    {
        distFromOriginOnX = 0;
		for (int y=0; y<8; y++)
        {
			//[uiv[y][x] stopAnimating];
            //viewpos.pos[x][y]
			if (curpos.pos[x][y]=='X')
            {
                //in original should be white
                uiv[x][y] = CCSprite::create(colorFileNameFirst);
                //CCLOG("White: uiv[x][y] uiv:[%i] [%i]",x,y);
                //counterWhite++;
            }
			else if (curpos.pos[x][y]=='O')
            {
                //in original should be black
                uiv[x][y] = CCSprite::create(colorFileNameSecond);
                //CCLOG("Black: uiv[x][y] uiv:[%i] [%i]",x,y);
                //counterBlack++;
            }
			else {
                uiv[x][y] = CCSprite::create(colorFileNameFirst);
                uiv[x][y]->setVisible(false);
                 
                //uiv[x][y] = NULL;
            }
            
            /*
            if (othelloIsEnabled) {
                
            
                uiv[x][y]->setPosition(ccp(originBoardX + distFromOriginOnX,originBoardY +distFromOriginOnY));
                uiv[x][y]->setAnchorPoint(anchorPointSprite);
                uiv[x][y]->setScale(scaleSprite);
                this->addChild(uiv[x][y]);
                
                //HELPER SPRITE
                helperUIV[x][y] = CCSprite::create("stone_select.png");
                helperUIV[x][y]->setPosition(ccp(originBoardX + distFromOriginOnX,originBoardY +distFromOriginOnY));
                helperUIV[x][y]->setAnchorPoint(anchorPointSprite);
                helperUIV[x][y]->setScale(scaleSprite);
                helperUIV[x][y]->setVisible(false);
                
                this->addChild(helperUIV[x][y]);
            }else{
            
                uiv[x][y]->setPosition(ccp(boardSprite->boundingBox().origin.x + distFromOriginOnX,boardSprite->boundingBox().origin.y +distFromOriginOnY));
                uiv[x][y]->setAnchorPoint(anchorPointSprite);
                uiv[x][y]->setScale(scaleSprite);
                this->addChild(uiv[x][y]);
            
            //HELPER SPRITE
            helperUIV[x][y] = CCSprite::create("stone_select.png");
            helperUIV[x][y]->setPosition(ccp(boardSprite->boundingBox().origin.x + distFromOriginOnX,boardSprite->boundingBox().origin.y +distFromOriginOnY));
            helperUIV[x][y]->setAnchorPoint(anchorPointSprite);
            helperUIV[x][y]->setScale(scaleSprite);
            helperUIV[x][y]->setVisible(false);
            
            this->addChild(helperUIV[x][y]);
            }//*/
            
            uiv[x][y]->setPosition(ccp(originBoardX + distFromOriginOnX,originBoardY +distFromOriginOnY));
            uiv[x][y]->setAnchorPoint(anchorPointSprite);
            uiv[x][y]->setScale(scaleSprite);
            this->addChild(uiv[x][y]);
            
            //HELPER SPRITE
            helperUIV[x][y] = CCSprite::create("stone_select.png");
            helperUIV[x][y]->setPosition(ccp(originBoardX + distFromOriginOnX,originBoardY +distFromOriginOnY));
            helperUIV[x][y]->setAnchorPoint(anchorPointSprite);
            helperUIV[x][y]->setScale(scaleSprite);
            helperUIV[x][y]->setVisible(false);
            
            this->addChild(helperUIV[x][y]);
            
            
            distFromOriginOnX+=tileSize;
            // xx+=TILE_SIZE;
            
		}
        
        distFromOriginOnY+=tileSize;
        // yy+=TILE_SIZE;
        
	}
    
    updateResults();
    
    
    /*float widthBoard = boardSprite->getContentSize().width -2*50; //542, 2*42
    CCLOG("widthBoard: %f", widthBoard);
    //float tileS = (boardSprite->getContentSize().width * 0.9)/8;
    float tileS = widthBoard/8*0.9;
    float originBoardX = boardSprite->boundingBox().origin.x + 50.0f; //42
    float originBoardY = boardSprite->boundingBox().origin.y + 50.0f; //45
    
    CCLOG("originBoardX: %f", originBoardX);
    CCLOG("originBoardY: %f", originBoardY);
    CCLOG("tileS: %f", tileS);
    */
    /*
    CCSprite* testSprite = CCSprite::create("stone_black.png");
    
    testSprite->setScale(0.9f);
    
    testSprite->setPosition(ccp(originBoardX, originBoardY));
    
    testSprite->setAnchorPoint(ccp(0.2, 0.2));
    
    this->addChild(testSprite);
    
    CCSprite* testSprite2 = CCSprite::create("stone_black.png");
    testSprite2->setPosition(ccp(originBoardX + tileS, originBoardY + tileS));
    testSprite2->setScale(0.9f);
    //testSprite2->setAnchorPoint(ccp(0.15, 0.15));
    testSprite2->setAnchorPoint(ccp(0.2,0.2));
    
    this->addChild(testSprite2);
    
    CCSprite* testSprite3 = CCSprite::create("stone_black.png");
    testSprite3->setScale(0.9f);
    
    testSprite3->setPosition(ccp(originBoardX + 2*tileS, originBoardY));
    
    //testSprite3->setAnchorPoint(ccp(0.15, 0.15));
    testSprite3->setAnchorPoint(ccp(0.2,0.2));
    
    this->addChild(testSprite3);
    */
    
}



void BoardLayer:: newGame() {    
    
	current_cross=cross; //cross=option which concerns to starting formation; int = int
	curpos=viewpos=(cross==CROSS_BTN_TAG) ? startpos[0] : startpos[1]; //curpos = struct field, startpost=table of struct with position
    
	histpos=0;
	status=ST_RUNNING; //status==1
	playeris=1-playeris; //if playeris = 0 then human is black. If playeris = 1 then AI is black
    
    dialogStatus = DIALOG_OFF;
    updateStatus = UPDATE_OFF;
    
  //  int mode=[defaults integerForKey:@"mode"]; //get mode/type of game pvp(1) or player vs computer(2)
    if(mode==PVP_BTN_TAG)
    {
        curpos.turn = playeris;
        whoseMove = HUMAN;
    }
   
	lastx=lasty=dist=-1;
	thinking=0;
	
    //updatePawnsPositions();//first creation of pawn image representation on the board
    createBeginningPawnsPosition();
    updateActiveMark();
    
    if (showMoves) {
        showMovements();
    }
    
    CCLOG("Playeris: %i, TURA: %i", playeris, curpos.turn);
    
}

void BoardLayer::undoUpdatePositions(){    
    
    for (int x=7; x>=0; x--)
    {
        for(int y=0; y<8; y++)
        {
            //==============================================
            //Update data about pawns with current positions
            //==============================================
            if (curpos.pos[x][y]=='X')
            {
                //uiv[x][y] = CCSprite::create("stone_white.png");
                uiv[x][y]->setTexture(CCTextureCache::sharedTextureCache()->addImage(colorFileNameFirst));
                uiv[x][y]->setVisible(true);
            }
            else if (curpos.pos[x][y]=='O')
            {
                //uiv[x][y] = CCSprite::create("stone_black.png");
                uiv[x][y]->setTexture(CCTextureCache::sharedTextureCache()->addImage(colorFileNameSecond));
                uiv[x][y]->setVisible(true);
            }
            else
            {
                //uiv[x][y] = NULL;
                uiv[x][y]->setVisible(false);
            }

        }
    }
    
    updateResults();
    updateActiveMark();
    
    if (showMoves) {
        showMovements();
    }
    
}


void updateSomething() {
	/*
    if (status==ST_RUNNING && xt && yt) {
		CGRect r;
		r.origin.x=xt-XSTEP/2;
		r.origin.y=yt-XSTEP/2;
		r.size.height=XSTEP;
		r.size.width=XSTEP;
		[uivx setFrame:r];
        
        int mode=[defaults integerForKey:@"mode"];
        
        if(mode == 1)
        {
            {
                if (curpos.turn&1) {
                    [uivx setImage:im_red];
                }
                else
                {
                    [uivx setImage:im_green];
                }
            }
        }
        else
        {
            if (playeris) [uivx setImage:im_red];
            else [uivx setImage:im_green];
        }
		[uivx setHidden:NO];
	} else {
		[uivx setHidden:YES];
	}
    */
}

void BoardLayer::ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event){
    
    CCTouch *touch = (CCTouch*)  (touches->anyObject());
    CCPoint location =  touch->getLocation();
    
    if(boardSprite->boundingBox().containsPoint(location)){
        xl=xt = location.x;
        yl=yt = location.y;
        
        //updateSomething();
    }
}

void BoardLayer::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event){
    
}

void BoardLayer::ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event){
    
    if (dialogStatus == DIALOG_OFF && updateStatus==UPDATE_OFF) {
        
    
    // Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocation();
    //location = CCDirector::sharedDirector()->convertToGL(location);
    
    CCLOG("(location)X is: %f and Y is: %f", location.x, location.y);
    
    CCLOG("(BoardBonds)X is: %f and Y is: %f", boardSprite->boundingBox().origin.x, boardSprite->boundingBox().origin.y);
   
       /* float EndX = originBoardX + widthBoard;
        float EndY = originBoardY + widthBoard;
        if (location.x > originBoardX && location.x < EndX && location.y > originBoardY && location.y < EndY)
            */
        
     //x,y to indeksy tablicy gry, ktory kafelek inaczej mowiac
    if(boardSprite->boundingBox().containsPoint(location)){
        
        float pawnX, pawnY;
        int Xx, Yy;
        float currentStartingPoint  = boardSprite->boundingBox().origin.x;
        //float currentStartingPoint = originBoardX;
        
        //float currentEndingPoint = currentStartingPoint + TILE_SIZE;
        float currentEndingPoint = currentStartingPoint + tileSize;
        
        
        float currentStartingPointY = boardSprite->boundingBox().origin.y;
        //float currentStartingPointY = originBoardY;
        
        //float currentEndingPointY = currentStartingPointY + TILE_SIZE;
        float currentEndingPointY = currentStartingPointY + tileSize;
        
        for (int x=7; x>=0; x--)
        {
            
            for (int y=0; y<8; y++)
            {
                //============================================
                //  Check which tile on gameboard, was tapped by user's finger. If we know it, we can set our pawn on center position of this tile.
                //===========================================
                if ((location.x > currentStartingPoint && location.x < currentEndingPoint) && (location.y >currentStartingPointY && location.y < currentEndingPointY)) {
                    //warun
                    //CCLOG("JESTEM pomiędzy punktami %f i %f w poziomie oraz punktami %f i %f w pionie, dokaldnie w punkcie X: %f Y: %f", currentStartingPoint,currentEndingPoint,currentStartingPointY, currentEndingPointY, location.x, location.y);
                    
                    Xx = x;
                    Yy = y;
                    CCLOG("Xx: %i i Yy: %i", Xx,Yy);
                    //===========
                    // In future i must apply  y, x coordinates instead of pawnX, pawnY because I deliver these coordinates to viewpos or curpos(i suppose this) for example: viewpos[y][x] = 'X' or '0'. Next i have to updatePawnPositions
                    //===========
                    
                }
                
                currentStartingPoint = currentEndingPoint;
               //currentEndingPoint +=TILE_SIZE;
                currentEndingPoint +=tileSize;
                
            }
            
            currentStartingPoint  = boardSprite->boundingBox().origin.x;
            //currentEndingPoint = currentStartingPoint + TILE_SIZE;
            currentEndingPoint = currentStartingPoint + tileSize;
            
            currentStartingPointY = currentEndingPointY;
            //currentEndingPointY +=TILE_SIZE;
            currentEndingPointY +=tileSize;
            
        }
        
        history[histpos]=curpos;
        if (move2(&curpos,Xx,Yy)) {
            histpos++;
            lastx=Xx; lasty=Yy; dist=0;
            CCLOG("Mozna postawić pionka");            
        }else{
            CCLOG("Nie mozna postawić pionka");
        }

    }
    
    }
}

//======================================================
//TO DO METHODS
//======================================================


BoardLayer::~BoardLayer(){
    //animationOfChangingPawn->release();
    //actionOfChangingPawn->release();
}

int BoardLayer::posequal(struct field *a,struct field *b)
{
	int x,y;
	
	for (y=0; y<8; y++)
    {
		for (x=0; x<8; x++)
        {
			if (a->pos[y][x] != b->pos[y][x])
            {
                return 0;
            }
		}
	}
	return 1;
}

/**
 //later
*/
void BoardLayer::update_pos(int x,int y) {
    //=====================================================================
    //viewpos assist uiv to set pawn on the board, curpos keeps current positions of pawns.
    //curpos is the latest actual position of the board. He is base and pattern for uiv to update its data.
    //viewpos is the previous position, position before current step/turn. Its position are visible on the board.
    //=======================================================================
    
	if (curpos.pos[x][y]==viewpos.pos[x][y]){
        CCLOG("Rowne");
        return;
    }
    
    
	//==============================================
    //Update data about pawns with current positions
    //==============================================
	if (curpos.pos[x][y]=='X')
    {
        //uiv[x][y] = CCSprite::create("stone_white.png");
        uiv[x][y]->setTexture(CCTextureCache::sharedTextureCache()->addImage(colorFileNameFirst));
        uiv[x][y]->setVisible(true);
    }
	else if (curpos.pos[x][y]=='O')
    {
        //uiv[x][y] = CCSprite::create("stone_black.png");
        uiv[x][y]->setTexture(CCTextureCache::sharedTextureCache()->addImage(colorFileNameSecond));
        uiv[x][y]->setVisible(true);
    }
    else
    {
        //uiv[x][y] = NULL;
        uiv[x][y]->setVisible(false);
    }
    
    
    
    CCAnimation* animationOfChangingPawn = CCAnimation::create();
    CCString *name;
    for (int i=1; i<=9; i++) {
        name = CCString::createWithFormat("anim_stone_%s%i.png",postfixColor,i);
        animationOfChangingPawn->addSpriteFrameWithFileName(name->getCString());
    }
    
    animationOfChangingPawn->setDelayPerUnit(0.25f/9.0f);
    animationOfChangingPawn->setRestoreOriginalFrame(true);
    //CCAnimate* action = CCAnimate::create(animationOfChangingPawn);
    
    //=======================================
    //Viewpos is position of pawns presents on the board, which is now deprecated, because currentpos, which held current
    //positions of pawn in current turn. So we can run animations of changing pawns to other color.
    //=======================================
	if (viewpos.pos[x][y]=='O') {
        //black result (white will change to black pawn)
		uiv[x][y]->runAction(CCAnimate::create(animationOfChangingPawn)->reverse());
	} else if (viewpos.pos[x][y]=='X') {
		//white result
        uiv[x][y]->runAction(CCAnimate::create(animationOfChangingPawn));
	}
	
    
	viewpos.pos[x][y]=curpos.pos[x][y]; //assign new pawn on position, it is the last pawn in row of turning pawns
    
    
}

/**
 This method updates all gameboard. So, the method checks, whether pawns changed their positions and if they did it, method updates it on the board. Moreover, this method updates scoreboard and checks whether user can do any movement or whether game is over.
*/
void BoardLayer:: updateWithAnimations(){
    
    static int ani_delay=0;
    
    if(lastx!=-1)
    {
        static int delay=0;
		delay++;
		if (delay>1)
        {
			delay=0;
			int step,x,y;
            
			for (step=-dist; step<=dist; step++)
            {
				x=lastx+step; y=lasty+dist;
				if (x>=0 && x<8 && y>=0 && y<8) update_pos(x,y);
				x=lastx+step; y=lasty-dist;
				if (x>=0 && x<8 && y>=0 && y<8) update_pos(x,y);
				x=lastx+dist; y=lasty+step;
				if (x>=0 && x<8 && y>=0 && y<8) update_pos(x,y);
				x=lastx-dist; y=lasty+step;
				if (x>=0 && x<8 && y>=0 && y<8) update_pos(x,y);
			}
            //if (dist==0) AudioServicesPlaySystemSound(snd_set);
			dist++;
			if (posequal(&curpos,&viewpos) || dist>8)
            {
                updateStatus = UPDATE_OFF;
				lastx=lasty=dist=-1;
				ani_delay=10;
                updateResults();
                updateActiveMark();
                gameOverTest();
                mustPassTest();
                
                if (showMoves) {
                    showMovements();
                }
                
			} else
            {
                updateStatus = UPDATE_ON;
                return;
            }
		} else return;
    }
    
    //================
    //AI
    //================
   
    static int min_cpu_turn;
	int best;
	if (min_cpu_turn>0) {
		min_cpu_turn--;
	}
    else if (status==ST_RUNNING && thinking && (best=bestmoveisdone2())!=-1)
    {
		thinking=0;
		if (best!=64) move2(&curpos,lastx=(best&7),lasty=(best/8));
		else { curpos.turn++; lastx=lasty=4; }
		dist=0;
		return;
	}	
    
    
	if (cpuTurn() && !thinking) {
		thinking=1; // here first time variable 'thinking' equals 1
		bestmove2(&curpos,diff); //diff means level of difficulty
		min_cpu_turn=4;
		return;
	}
	
    /*//block responsible for animations of pawns
	if (ani_delay>0) {
		ani_delay--;
		return;
	}
     */

    
}

void BoardLayer::showMovements(){
    
    //Hide direction of movement
    if(mode == PVC_BTN_TAG && whoseMove == AI){
        
        for (int x=7; x>=0; x--){
            for(int y=0; y<8; y++){
                helperUIV[x][y]->setVisible(false);
            }
        }
        return;
    }
        
    helperPos = curpos;

    
    moveHelper(&helperPos);
    
    
    for (int x=7; x>=0; x--)
    {
        for(int y=0; y<8; y++)
        {
            //==============================================
            //Update data about pawns with current positions
            //==============================================
            if (helperPos.pos[x][y]=='Z')
            {
                /*
                uiv[x][y]->setTexture(CCTextureCache::sharedTextureCache()->addImage("stone_select.png"));
                uiv[x][y]->setScale(0.9f);
                uiv[x][y]->setVisible(true);
                 */                
                helperUIV[x][y]->setVisible(true);
            }else{
                //uiv[x][y]->setVisible(false);
                helperUIV[x][y]->setVisible(false);
            }
            
        }
    }
}

int BoardLayer::cpuTurn(){
    
    //int mode=[defaults integerForKey:@"mode"];
    
    if (mode == PVP_BTN_TAG) {
       
        {
            return 0;
        }
    }
    
    if (!playeris) return curpos.turn&1;
	else return !(curpos.turn&1);
}

void BoardLayer::createBoard(){
    
    shadowSprite = CCSprite::create("test_shadow.png");
    boardSprite = CCSprite::create("test_board.png");
}

void BoardLayer::createScoreBoards(){
    
    CCString markNormal;
    CCString markSelected;
    
    leftScoreBoard = ScoreBoard::create(colorScBrdLeftNorm, colorScBrdLeftSel, "pmark_human_0.png","pmark_human_1.png", SCORE_FONT_SIZE, BTN_LEFT);
    
    rightScoreBoard = ScoreBoard::create(colorScBrdRightNorm,colorScBrdRightSel, "pmark_human_0.png", "pmark_human_1.png", SCORE_FONT_SIZE, BTN_RIGHT);
    
    if(liveScore){
        leftScoreBoard->setVisibleScore(true);
        rightScoreBoard->setVisibleScore(true);
    }else{
        leftScoreBoard->setVisibleScore(false);
        rightScoreBoard->setVisibleScore(false);
    }
    
}

void BoardLayer::createMenuButtons(){
    //===========================
    //Create Menu Buttons
    //===========================
    CCString *btnFileNameNormal = CCString::create("button_wide_0.png");
    CCString *btnFileNameSelected = CCString::create("button_wide_1.png");
    
    undoButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(BoardLayer::undobBtnCallback), langManager->Translate(STRING_UNDO_BTN)->getCString(), BOARD_MENU_FONT_SIZE);
    newButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(BoardLayer::newBtnCallback), langManager->Translate(STRING_NEW_BTN)->getCString(), BOARD_MENU_FONT_SIZE);
    menuButton = MenuButton::create(btnFileNameNormal->getCString(), btnFileNameSelected->getCString(), this, menu_selector(BoardLayer::menuBtnCallback), langManager->Translate(STRING_MENU_BTN)->getCString(), BOARD_MENU_FONT_SIZE);
    
    //===========================
    //Create MenuBoard
    //===========================
    menuBoardButtons = CCMenu::create(undoButton,newButton,menuButton,NULL);
}

void BoardLayer::setBoardPosition(){
    
    shadowSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - shadowSprite->getContentSize().height/2- 60));
    boardSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - boardSprite->getContentSize().height/2- addDistBoardY));
    
}

void BoardLayer::setScoreBoardPosition(){
    
    //leftScoreBoard->setPosition(ccp(boardSprite->boundingBox().origin.x + leftScoreBoard->getContentSize().width/3 + diffXForFirstItem, visibleSize.height + origin.y - 80));
    //rightScoreBoard->setPosition(ccp(boardSprite->getContentSize().width - rightScoreBoard->getContentSize().width/3 + diffXForLastItem, visibleSize.height + origin.y -80));
    
    CCLOG("Origin x Board: %f", boardSprite->boundingBox().origin.x);
    CCLOG("Origin x Board: %f", this->originBoardX);
    
    leftScoreBoard->setPosition(ccp(originBoardX + leftScoreBoard->getContentSize().width/3 + diffXForFirstItem, visibleSize.height + origin.y - 80));
    rightScoreBoard->setPosition(ccp(boardSprite->getContentSize().width - rightScoreBoard->getContentSize().width/3 + diffXForLastItem, visibleSize.height + origin.y -80));
    
}

void BoardLayer::setMenuButtonPosition(){
    
    //===========================
    //Set Menu Buttons position
    //===========================
    undoButton->setPosition(ccp(boardSprite->boundingBox().origin.x + undoButton->getContentSize().width/3 + diffXForFirstItem,boardSprite->boundingBox().origin.y - 40));
    
    newButton->setPosition(ccp(VisibleRect::center().x,boardSprite->boundingBox().origin.y - 40));
    
    menuButton->setPosition(ccp(boardSprite->getContentSize().width - menuButton->getContentSize().width/3 +diffXForLastItem,boardSprite->boundingBox().origin.y - 40));
    
    
    //===========================
    //Set MenuBoard position
    //===========================
    menuBoardButtons->setPosition(CCPointZero);
}

void BoardLayer::addBoardToLayer(){
    
    this->addChild(shadowSprite,-1);
    this->addChild(boardSprite,0);
}

void BoardLayer::addScoreBoardToLayer(){
    
    this->addChild(leftScoreBoard,1);
    this->addChild(rightScoreBoard,1);
    
}

void BoardLayer::addMenuToLayer(){
    
    this->addChild(menuBoardButtons, 2);
}

void BoardLayer::keyBackClicked(){
    CCLOG("BACK");
    CCScene *backScene = MenuScene::create();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5f, backScene,true));
}


