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

using namespace cocos2d;

class OptionsButtonsLayer:public cocos2d::CCLayer{
private:
    
    CCSize visibleSize;
    CCPoint origin;
    
    CCString *btnFileNameNormal;
    CCString *btnFileNameSelected;
    
    LanguageManager* langManager;
    
    CCLabelTTF *modeLabel;
    CCLabelTTF *difficultyLabel;
    CCLabelTTF *startFormLabel;
    CCLabelTTF *colorsLabel;
    CCLabelTTF *boardLabel;
    CCLabelTTF *movesLabel;
    CCLabelTTF *liveScoreLabel;
    
    CCSprite *lineHeader[6];
    
    //ImageOptionButton* pvpButton;
    //ImageOptionButton* pvcButton;
    
    MenuButton *pvpButton;
    MenuButton *pvcButton;
    
    MenuButton *easyButton;
    MenuButton *mediumButton;
    MenuButton *hardButton;
    MenuButton *veryHardButton;
    MenuButton *hardestButton;
    
    MenuButton *crossButton;
    MenuButton *straightButton;
    
    MenuButton *blackWhiteButton;
    MenuButton *redGreenButton;
    MenuButton *redBlueButton;
    
    MenuButton* boardButton;
    
    MenuButton *movesButton;
    
    //MenuButton *movesOffButton;
    
    MenuButton *liveScoreButton;
    
    //MenuButton *liveScoreOffButton;
    
    CCMenu *modeMenu;
    CCMenu *difficultyMenu;
    CCMenu *startFormMenu;
    CCMenu *colorsMenu;
    CCMenu *boardMenu;
    
    CCMenu *movLiveMenu;
    
    //CCMenu *movesMenu;
    //CCMenu *liveScoreMenu;
    
    int dist;
    
    
    bool init();
    
    void createItems();
    void setItemPositions();
    void addItemsToLayer();
    
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
    
    void modeBtnCallback(CCObject* pSender);
    void difficultyBtnCallback(CCObject* pSender);
    void startFormBtnCallback(CCObject* pSender);
    void colorBtnCallback(CCObject* pSender);
    void movesBtnCallback(CCObject* pSender);
    void liveScoreBtnCallback(CCObject* pSender);
    
    void keyBackClicked();
    
public:
    CREATE_FUNC(OptionsButtonsLayer);
};

#endif /* defined(__ReversiGL__OptionsButtonsLayer__) */
