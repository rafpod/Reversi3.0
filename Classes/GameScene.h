//
//  GameScene.h
//  ReversiGL
//
//  Created by RafalP on 18.10.2013.
//
//

#ifndef __ReversiGL__GameScene__
#define __ReversiGL__GameScene__

#include "cocos2d.h"

class GameScene: public cocos2d::CCScene{

private:   
   // GameScene(){}
    ~GameScene();
    
public:
    virtual bool init();
    CREATE_FUNC(GameScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
};

#endif /* defined(__ReversiGL__GameScene__) */
