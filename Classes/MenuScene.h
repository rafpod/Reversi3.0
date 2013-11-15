//
//  MenuScene.h
//  ReversiGL
//
//  Created by RafalP on 07.11.2013.
//
//

#ifndef __ReversiGL__MenuScene__
#define __ReversiGL__MenuScene__

#include "cocos2d.h"

class MenuScene: public cocos2d::CCScene{
    
private:
    // MenuScene(){}
    // ~MenuScene(){}
    
public:
    virtual bool init();
    CREATE_FUNC(MenuScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
};


#endif /* defined(__ReversiGL__MenuScene__) */
