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
    
    LanguageManager* langManager;
    
    CCLabelTTF *gamesTitleLabel;
    CCLabelTTF *wonTitleLabel;
    CCLabelTTF *lostTitleLabel;
    CCLabelTTF *drawTitleLabel;
    
    CCLabelTTF *gamesResultLabel;
    CCLabelTTF *wonResultLabel;
    CCLabelTTF *lostResultLabel;
    CCLabelTTF *drawResultLabel;
    
    CCLabelTTF *statsTitleLabel;
    
    int games;
    int won;
    int lost;
    int draw;
    
    MenuButton *resetButton;
    CCMenuItemImage *backButton;
    
    CCSprite *lineHeader[4];
    
    CCMenu *statsMenu;
    
    bool init();
    
    void createItems();
    void setItemPositions();
    void addItemsToLayer();
    
    void getStats();
    
    void createMarkerLine(CCLabelTTF* labelHeader, int index);
        
    void resetBtnCallback(CCObject* pSender);
    void backBtnCallback(CCObject* pSender);
    
    void keyBackClicked();
    
public:
    CREATE_FUNC(StatsResultsLayer);
    
};

#endif /* defined(__ReversiGL__StatsResultsLayer__) */
