//
//  MenuButton.h
//  ReversiGL
//
//  Created by RafalP on 08.11.2013.
//
//

#ifndef __ReversiGL__MenuButton__
#define __ReversiGL__MenuButton__

#include "cocos2d.h"

using namespace cocos2d;

class MenuButton: public cocos2d::CCMenuItemImage{
private:
    
    bool selectedBtn;
    
    CCLabelTTF *label;
    
    bool init (const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize);    
    
public:
    static MenuButton* create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize);
    
    bool isBtnSelected();
    void setSelectedBtn(bool isSelected);
    
};


#endif /* defined(__ReversiGL__MenuButton__) */
