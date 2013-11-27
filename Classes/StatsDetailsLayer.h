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
    CREATE_FUNC(StatsDetailsLayer);
};

#endif /* defined(__ReversiGL__StatsDetailsLayer__) */
