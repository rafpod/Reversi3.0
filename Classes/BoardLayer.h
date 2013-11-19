//
//  BoardLayer.h
//  ReversiGL
//
//  Created by RafalP on 23.10.2013.
//
//

#ifndef __ReversiGL__BoardLayer__
#define __ReversiGL__BoardLayer__

#include "cocos2d.h"
#include "MenuButton.h"
#include "ScoreBoard.h"
#include "Othello.h"
#include "LanguageManager.h"

using namespace cocos2d;

class BoardLayer:public cocos2d::CCLayer{

private:    
    
    struct field curpos;
    struct field history[100];
    struct field viewpos;
    struct field helperPos;
    
    int histpos;	// undo steps available
    int status;		// game running?
    int playeris;	// human is player 0 or 1
    int lastx,lasty,dist;
    
    int xt,yt;
    int xl,yl;
    int thinking;
    int loaded_colors;
    int current_cross;
    int passing;
    
    int cross;
    int mode;
    int diff;
    
    int whoseMove;
    
    CCSprite *uiv[8][8],*uivx,*uiback;
    //New variables
    CCSprite* helperUIV[8][8];
    float scaleSprite;
    float tileSize;
    CCPoint anchorPointSprite;
    CCPoint positionOfWhiteMark;
    CCSize visibleSize;
    CCPoint origin;
    LanguageManager* langManager;
    int counterBlack;
    int counterWhite;
    
    int diffXForFirstItem;
    int diffXForLastItem;
    
    int addDistBoardY;
    int dialogStatus;
    int updateStatus;


    
    CCSprite *shadowSprite;
    CCSprite *boardSprite;
    CCSprite *pawn;
    
    ScoreBoard *leftScoreBoard;
    ScoreBoard *rightScoreBoard;
    
    MenuButton *undoButton;
    MenuButton *newButton;
    MenuButton *menuButton;
    
    CCMenu* menuBoardButtons;
    
    
    bool init();
    
    void createItems();
    void setItemsPositions();
    void addItemsToBoard();
    
    void updateBoard(float dt);    
    
    void createBeginningPawnsPosition();
    void undoUpdatePositions();
    void newGame();
    
    void updateActiveMark();
    void updateResults();
    
    void dialogBackButton(CCObject *pSender);    
    void dialogMustPassButton(CCObject *pSender);
    
    void gameOverTest();
    void mustPassTest();
    
    void updateWithAnimations();
    void update_pos(int x, int y);
    int posequal(struct field *a,struct field *b);
    
    void undobBtnCallback(CCObject* pSender);
    void newBtnCallback(CCObject* pSender);
    void menuBtnCallback(CCObject* pSender);
    
    void showMovements();
    void keyBackClicked();
    
    //To do
    ~BoardLayer();
    int cpuTurn();
    void setOptionsPreferences();
    
    
    
public:
    CREATE_FUNC(BoardLayer);
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
    
    
    /*
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent *event);
    */ 
};

#endif /* defined(__ReversiGL__BoardLayer__) */
