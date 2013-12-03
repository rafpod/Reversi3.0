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
    int stoneColor;
    bool showMoves;
    bool liveScore;
    bool othelloIsEnabled;
    
    int whoseMove;
    
    struct diffStorage diffResultStorage;
        
    
    CCSprite *uiv[8][8],*uivx,*uiback;
    //New variables
    CCSprite* helperUIV[8][8];
    float scaleSprite;
    float tileSize;
    CCPoint anchorPointSprite;
    CCPoint positionOfWhiteMark;
    
    CCSize visibleSize;
    CCPoint origin;
    CCSize designSize;
    CCSize visSize;    
    
    //CCSpriteBatchNode *batchNodeSprites;
    
    LanguageManager* langManager;
    int counterBlack;
    int counterWhite;
    
    int diffXForFirstItem;
    int diffXForLastItem;
    
    int scoreBoardOffAboveBoard;
    int boardOffFromTop;
    int shadowOffFromTop;
    
    int dialogStatus;
    int updateStatus;
    
    
    const char* colorFileNameFirst;
    const char* colorFileNameSecond;
    const char* postfixColor;
    
    const char* colorScBrdLeftNorm;
    const char* colorScBrdRightNorm;
    
    const char* colorScBrdLeftSel;
    const char* colorScBrdRightSel;
    
    
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
    
    void createBoard();
    void createScoreBoards();
    void createMenuButtons();
    
    void setBoardPosition();
    void setScoreBoardPosition();
    void setMenuButtonPosition();
    
    void addBoardToLayer();
    void addScoreBoardToLayer();
    void addMenuToLayer();
    
    void setOptionsPreferences();
    void initVariables();

    
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
    int cpuTurn();
    
    //To do
    ~BoardLayer();
    
    void setCoordToResolution();
    
    void getDetailsStats();
    void setDetailsStats();
    
    
public:
    CREATE_FUNC(BoardLayer);
    //void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    //void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    //void ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
    
    
    
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    void ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent *event);
    
};

#endif /* defined(__ReversiGL__BoardLayer__) */
