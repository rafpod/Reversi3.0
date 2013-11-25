//
//  DiffButton.h
//  ReversiGL
//
//  Created by RafalP on 25.11.2013.
//
//

#ifndef __ReversiGL__DiffButton__
#define __ReversiGL__DiffButton__

#include "cocos2d.h"

using namespace cocos2d;

class DiffButton: public cocos2d::CCMenuItemImage{
private:
    
    CCString* firstImage;
    CCString* secondImage;
    
    CCSprite *sprite1;
    CCSprite *sprite2;
    CCSprite *sprite3;
    CCSprite *sprite4;
    CCSprite *sprite5;
    
    CCSprite* tab[5]={sprite1, sprite2, sprite3, sprite4, sprite5};
    
    int numbers;
    
    bool selectedBtn;
    
    bool init (const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites);
    
    void createImages(int numberOfSpr);
    
public:
    
    static DiffButton* create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites);
    
    bool isBtnSelected();
    void setSelectedBtn(bool isSelected);
    
};

#endif /* defined(__ReversiGL__DiffButton__) */
