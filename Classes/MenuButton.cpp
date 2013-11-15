//
//  MenuButton.cpp
//  ReversiGL
//
//  Created by RafalP on 08.11.2013.
//
//

#include "MenuButton.h"

#define MAIN_MENU_FONT_SIZE2  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 40)


bool MenuButton::init(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize){
    
    if(!MenuButton::initWithNormalImage(normalImage, selectedImage, normalImage, target, selector))
    {
        return false;
    }
    else
    {
    
        // this->label=CCLabelTTF::create(textOnButton, "Arial", fontSize, CCSizeMake(this->getContentSize().width - 80, 0), kCCTextAlignmentCenter);
        
        this->label=CCLabelTTF::create(textOnButton, "Georgia", fontSize);
    
        this->label->setColor(ccc3(0, 0, 0));
    
        this->label->setPosition(ccp(this->boundingBox().origin.x + this->getContentSize().width, this->boundingBox().origin.y + this->getContentSize().height));
        
        float percentLabelOnBtn = label->getContentSize().width/this->getContentSize().width * 100;
        //float scale = label->getContentSize().width/this->getContentSize().width;
        
        CCLOG("Button width: %f Label width: %f percent: %f", this->getContentSize().width, label->getContentSize().width, percentLabelOnBtn);
        //70
        while(percentLabelOnBtn > 68){
            fontSize-=1;
            this->label->setFontSize(fontSize);
                //this->setScale(1.25);
            percentLabelOnBtn = label->getContentSize().width/this->getContentSize().width * 100;
            CCLOG("Button width2: %f Label width2: %f percent2: %f", this->getContentSize().width, label->getContentSize().width, percentLabelOnBtn);
            
        }        
        this->addChild(label,1);
        return true;
    }
    
}

MenuButton* MenuButton::create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize){
    
    MenuButton * button = new MenuButton();
    if (button && button->init(normalImage,selectedImage,target,selector,textOnButton, fontSize)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
    
}