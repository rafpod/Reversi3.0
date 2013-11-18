//
//  ImageOptionButton.h
//  ReversiGL
//
//  Created by RafalP on 18.11.2013.
//
//

#ifndef __ReversiGL__ImageOptionButton__
#define __ReversiGL__ImageOptionButton__

#include "cocos2d.h"

using namespace cocos2d;

class ImageOptionButton: public cocos2d::CCMenuItemImage{
private:
    
    const char* firstImage;
    const char* secondImage;
    
    bool selectedBtn;
    
    CCArray *tabSprite;    
    
    CCLabelTTF *label;
    
    bool init (const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize, const char* firstImg, const char* secondImg);
    
    bool init (const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites);
    
    void createSpritesOnButton(int numberOfSpr);
    
public:
    static ImageOptionButton* create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize, const char* firstImg, const char* secondImg);
    
    static ImageOptionButton* create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites);
    
    bool isBtnSelected();
    void setSelectedBtn(bool isSelected);
    
};


#endif /* defined(__ReversiGL__ImageOptionButton__) */
