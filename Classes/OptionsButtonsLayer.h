//
//  OptionsButtonsLayer.h
//  ReversiGL
//
//  Created by RafalP on 13.11.2013.
//
//

#ifndef __ReversiGL__OptionsButtonsLayer__
#define __ReversiGL__OptionsButtonsLayer__

#include "cocos2d.h"
#include "MenuButton.h"
#include "LanguageManager.h"
#include "ImageOptionButton.h"
#include "DiffButton.h"

using namespace cocos2d;
using namespace std;

class OptionsButtonsLayer:public cocos2d::CCLayer{
private:
    
    CCSize visibleSize;
    CCSize screenSize;
    CCPoint origin;
    
    float visHeight;
    float visWidth;
    
    bool othelloIsEnabled;
    
    vector<string> resDirOrders;
    
    CCString *btnFileNameNormal;
    CCString *btnFileNameSelected;
    
    const char* humanMark;
    const char* aiMark;
    
    const char* blackStone;
    const char* whiteStone;
    const char* blueStone;
    const char* redStone;
    const char* greenStone;
    
    LanguageManager* langManager;
    
    CCLabelTTF *modeLabel;
    CCLabelTTF *difficultyLabel;
    CCLabelTTF *startFormLabel;
    CCLabelTTF *colorsLabel;
    CCLabelTTF *boardLabel;
    CCLabelTTF *movesLabel;
    CCLabelTTF *liveScoreLabel;
    
    CCSprite *lineHeader[6];
    
    ImageOptionButton* pvpButton;
    ImageOptionButton* pvcButton;
    
    DiffButton *easyButton;
    DiffButton *mediumButton;
    DiffButton *hardButton;
    DiffButton *veryHardButton;
    DiffButton *hardestButton;
    
    MenuButton *crossButton;
    MenuButton *straightButton;
    
    ImageOptionButton *blackWhiteButton;
    ImageOptionButton *redGreenButton;
    ImageOptionButton *redBlueButton;
    
    //CCMenuItemToggle* skinButton;
    //CCMenuItemToggle* boardButton;
    
    MenuButton *woodButton;
    MenuButton *othelloButton;
    
    //MenuButton* boardButton;
    
    
    CCMenuItemToggle* showMovesButton;
    MenuButton *movesOnButton;
    MenuButton *movesOffButton;
    
    CCMenuItemToggle* liveScoreButton;
    MenuButton *liveScoreOnButton;
    MenuButton *liveScoreOffButton;
    
    //DiffButton *diffBtnTest;
    //DiffButton *diffBtnTest2;
    
    //MenuButton *liveScoreButton;
    
    CCMenuItemImage *backButton;
    
    CCMenu *mainMenu;
    CCMenu *menu2;
    CCMenu *backBtnMenu;
        
    int dist;
    
    
    bool init();
    
    void createItems();
    void setItemPositions();
    void addItemsToLayer();
    
    void initFileName();
    
    void createMarkerLine(CCLabelTTF* labelHeader, int index);
    
    void createGameModeItems();
    void createDiffItems();
    void createStartFormItems();
    void createColorSetItems();
    void createBoardItems();
    void createMovesItems();
    void createLiveScoreItems();    
    void createMenus();
    
    void setGameModeItemsPositions();
    void setDiffItemsPositions();
    void setStartFormItemsPositions();
    void setColorSetItemsPositions();
    void setBoardItemsPositions();
    void setMovesItemsPositions();
    void setLiveScoreItemsPositions();
    void setMenusPositions();
    
    void setBtnTags();
    
    void setActiveButtons();
    
    void modeBtnCallback(CCObject* pSender);
    void difficultyBtnCallback(CCObject* pSender);
    void startFormBtnCallback(CCObject* pSender);
    void colorBtnCallback(CCObject* pSender);
    void boardBtnCallback(CCObject* pSender);
    void movesBtnCallback(CCObject* pSender);
    void liveScoreBtnCallback(CCObject* pSender);
    void backBtnCallback(CCObject* pSender);    
    
    void setResources(const char* resNormal, const char* resSmall);
    
    void keyBackClicked();
    
    void setProperLabelScale(CCLabelTTF * item);
    //void setProperBtnScale(CCMenuItem * item);
    
    void setProperScale(ImageOptionButton* tabImage[], DiffButton* tabDiff[], MenuButton* tabMenu[], CCMenuItemToggle* tabTogg[]);
    void setScaleForItems();
    
    
    
public:
    CREATE_FUNC(OptionsButtonsLayer);
};

#endif /* defined(__ReversiGL__OptionsButtonsLayer__) */
