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
    
public:
    virtual bool init();
    CREATE_FUNC(StatsScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
};


#endif /* defined(__ReversiGL__StatsScene__) */
