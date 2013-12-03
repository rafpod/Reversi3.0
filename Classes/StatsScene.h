//
//  StatsScene.h
//  ReversiGL
//
//  Created by RafalP on 21.11.2013.
//
//

#ifndef __ReversiGL__StatsScene__
#define __ReversiGL__StatsScene__

#include "cocos2d.h"

using namespace cocos2d;

class StatsScene: public cocos2d::CCScene{
    
private:
    // StatsScene(){}
    // ~StatsScene(){}
    
    /*
    void createHeader();
    void setHeaderPosition();
    
    void backBtnCallback(CCObject* pSender);
    void keyBackClicked();*/
    
    bool init(CCLayer* layer);
    
public:
    virtual bool init();
    CREATE_FUNC(StatsScene);
    
    static StatsScene* create(CCLayer* layer);

    
};


#endif /* defined(__ReversiGL__StatsScene__) */
