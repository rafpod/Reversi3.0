//
//  StatsHeaderLayer.h
//  ReversiGL
//
//  Created by RafalP on 27.11.2013.
//
//

#ifndef __ReversiGL__StatsHeaderLayer__
#define __ReversiGL__StatsHeaderLayer__

#include "cocos2d.h"
#include "LanguageManager.h"

using namespace cocos2d;

class StatsHeaderLayer: public cocos2d::CCLayer{
private:
    
    CCSize designSize;
    CCSize visibleSize;
    
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
    
public:
    
    CREATE_FUNC(StatsHeaderLayer);
    
};

#endif /* defined(__ReversiGL__StatsHeaderLayer__) */
