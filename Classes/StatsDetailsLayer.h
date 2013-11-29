//
//  StatsDetailsLayer.h
//  ReversiGL
//
//  Created by RafalP on 27.11.2013.
//
//

#ifndef __ReversiGL__StatsDetailsLayer__
#define __ReversiGL__StatsDetailsLayer__

#include "cocos2d.h"
#include "LanguageManager.h"

using namespace cocos2d;

class StatsDetailsLayer: public cocos2d::CCLayer{
private:
    
    CCSize designSize;
    CCSize visibleSize;
    
    CCLabelTTF* wonLabel;
    CCLabelTTF* lostLabel;
    CCLabelTTF* tiedLabel;
    CCLabelTTF* allLabelH;
    
    CCLabelTTF* tabResult[4][6];
    CCLabelTTF* tabPercent[4][6];
    
    int tabResultValue[4][6];
    float tabPercentValue[4][6];
    
    CCLabelTTF* allLabelV;
    CCLabelTTF* hardestLabel;
    CCLabelTTF* veryHard;
    CCLabelTTF* hardLabel;
    CCLabelTTF* mediumLabel;
    CCLabelTTF* easyLabel;
    
    CCLabelTTF* headerLabel;
    
    CCSprite *lineHeader;
    
    int labelOffFromTop;
    int labelOffFromHeader;
    
    LanguageManager* langManager;
    
    CCLabelTTF *statsTitleLabel;
    
    CCMenuItemImage *backButton;
    
    CCMenu *statsHeaderMenu;
    
    bool init();
    
    void createItems();
    void setItemsPosition();
    void addItemsToLayer();
    
    void backBtnCallback(CCObject* pSender);
    void keyBackClicked();
    
    void createHeader();
    void setHeaderPosition();    
    
    void setDetailsOffsets();
    
    void countStats();    

    
public:
    CREATE_FUNC(StatsDetailsLayer);
};

#endif /* defined(__ReversiGL__StatsDetailsLayer__) */
