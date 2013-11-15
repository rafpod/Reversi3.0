//
//  BgLayer.h
//  ReversiGL
//
//  Created by RafalP on 08.11.2013.
//
//

#ifndef __ReversiGL__BgLayer__
#define __ReversiGL__BgLayer__

#include "cocos2d.h"

using namespace cocos2d;

class BgLayer:public cocos2d::CCLayer{
    
private:
    CCSprite *bgSprite;
    
    bool init();
    bool init(const char *fileName);
    
public:
    CREATE_FUNC(BgLayer);
    static BgLayer *createLayer(const char *fileName);
};


#endif /* defined(__ReversiGL__BgLayer__) */
