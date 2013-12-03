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
#include "Othello.h"

using namespace cocos2d;

class StatsDetailsLayer: public cocos2d::CCLayer{
private:
    
    CCSize designSize;
    CCSize visibleSize;
    
    CCLabelTTF* wonLabel;
    CCLabelTTF* lostLabel;
    CCLabelTTF* tiedLabel;
    CCLabelTTF* allLabelH;
    
    CCLabelTTF* tabResult[6][4];
    CCLabelTTF* tabPercent[6][4];
    
    int tabResultValue[6][4];
    float tabPercentValue[6][4];
        
    
    CCLabelTTF* allLabelV;
    CCLabelTTF* hardestLabel;
    CCLabelTTF* veryHardLabel;
    CCLabelTTF* hardLabel;
    CCLabelTTF* mediumLabel;
    CCLabelTTF* easyLabel;
    
    CCLabelTTF* headerLabel;
    
    CCSprite *lineHeader;
    
    CCString *blackColor;
    CCString *whiteColor;    
    
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
    void getStats();
    void setStats();
    
    void createLabelStats();
    
    void createPawnsRow(int number);    
    void createPawnsImages();

    
public:
    CREATE_FUNC(StatsDetailsLayer);
};

#endif /* defined(__ReversiGL__StatsDetailsLayer__) */
