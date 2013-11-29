//
//  BackgroundLayer.h
//  ReversiGL
//
//  Created by RafalP on 18.10.2013.
//
//

#ifndef __ReversiGL__BackgroundLayer__
#define __ReversiGL__BackgroundLayer__

#include "cocos2d.h"

using namespace cocos2d;

class BackgroundLayer:public cocos2d::CCLayer{
private:
    CCSpriteBatchNode * batchNode;
    
    CCSprite *bgSprite;
    
    bool init();
    
public:
    CREATE_FUNC(BackgroundLayer);
    CCSprite* getBgSprite();
};

#endif /* defined(__ReversiGL__BackgroundLayer__) */
