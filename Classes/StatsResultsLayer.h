//
//  StatsResultsLayer.h
//  ReversiGL
//
//  Created by RafalP on 21.11.2013.
//
//

#ifndef __ReversiGL__StatsResultsLayer__
#define __ReversiGL__StatsResultsLayer__

#include "cocos2d.h"
#include "LanguageManager.h"
#include "MenuButton.h"

USING_NS_CC;

class StatsResultsLayer: public cocos2d::CCLayer{
private:
    
    CCSize designSize;
    CCSize visibleSize;
    
    LanguageManager* langManager;
    
    CCLabelTTF *gamesTitleLabel;
    CCLabelTTF *wonTitleLabel;
    CCLabelTTF *lostTitleLabel;
    CCLabelTTF *drawTitleLabel;
    
    CCLabelTTF *gamesResultLabel;
    CCLabelTTF *wonResultLabel;
    CCLabelTTF *lostResultLabel;
    CCLabelTTF *drawResultLabel;
    
    CCLabelTTF *wonPercentLabel;
    CCLabelTTF *lostPercentLabel;
    CCLabelTTF *drawPercentLabel;
    
    CCLabelTTF *statsTitleLabel;
    
    CCString *resultString;
    CCString *percentString;
    
    int games;
    int won;
    int lost;
    int draw;
    
    int labelOffFromTop;
    int labelOffFromEachOther;
    int buttonOffFromLastLabel;
    
    
    MenuButton *resetButton;
    MenuButton *detailsButton;
    CCMenuItemImage *backButton;
    
    CCSprite *lineHeader, *lineBottom;
    
    CCMenu *statsMenu;
    
    bool init();
    
    void createItems();
    void setItemPositions();
    void addItemsToLayer();
    
    void createHeader();
    void createWonItems();
    void createLostItems();
    void createTiedItems();
    void createGamesItems();
    void createBottomButtons();
    
    void setHeaderPosition();
    void setWonPositionItems();
    void setLostPositionItems();
    void setTiedPositionItems();
    void setGamesPositionItems();
    void setBottomButtonsPosition();
    
    void getStats();
    
    //void createMarkerLine(CCLabelTTF* labelHeader, int index);
    void setStatsOffsets();
        
    void resetBtnCallback(CCObject* pSender);
    void backBtnCallback(CCObject* pSender);
    void detailsBtnCallback(CCObject* pSender);
    
    void keyBackClicked();
   
    
        
    
public:
    CREATE_FUNC(StatsResultsLayer);
    
};

#endif /* defined(__ReversiGL__StatsResultsLayer__) */
