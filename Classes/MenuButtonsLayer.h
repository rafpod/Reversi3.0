//
//  MenuButtonsLayer.h
//  ReversiGL
//
//  Created by RafalP on 08.11.2013.
//
//

#ifndef __ReversiGL__MenuButtonsLayer__
#define __ReversiGL__MenuButtonsLayer__

#include "cocos2d.h"
#include "LanguageManager.h"
#include "MenuButton.h"

using namespace cocos2d;

class MenuButtonsLayer:public cocos2d::CCLayer{

private:
    CCSprite *mainLogo;
    
    MenuButton *playButton;
    MenuButton *optionsButton;
    MenuButton *rulesButton;
    MenuButton *statsButton;
    MenuButton *moreGamesButton;
    
    CCMenu *mainMenu;
    
    CCSize visibleSize;
    CCPoint origin;
    
    LanguageManager* langManager;
        
    int designHeight;
    
    bool init();
    
    void createItems();
    void setItemPositions();
    void addItemsToLayer();
    void setBtnTag();
    
    void menuBtnCallback(CCObject* pSender);
    
    void keyBackClicked();
    
public:
    CREATE_FUNC(MenuButtonsLayer);
    
   
};

#endif /* defined(__ReversiGL__MenuButtonsLayer__) */
