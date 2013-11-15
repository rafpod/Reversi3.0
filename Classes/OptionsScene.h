//
//  OptionsScene.h
//  ReversiGL
//
//  Created by RafalP on 13.11.2013.
//
//

#ifndef __ReversiGL__OptionsScene__
#define __ReversiGL__OptionsScene__

#include "cocos2d.h"

using namespace cocos2d;

class OptionsScene: public cocos2d::CCScene{
    
private:
    // OptionsScene(){}
    // ~OptionsScene(){}
    
public:
    virtual bool init();
    CREATE_FUNC(OptionsScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
};


#endif /* defined(__ReversiGL__OptionsScene__) */
