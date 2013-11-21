//
//  ImageOptionButton.cpp
//  ReversiGL
//
//  Created by RafalP on 18.11.2013.
//
//

#include "ImageOptionButton.h"

#define MAIN_MENU_FONT_SIZE2  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / 640 * 40)
#define MAX_IMG_ON_BTN 5


bool ImageOptionButton::init(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize, const char* firstImg, const char* secondImg){
    
        
    if(!ImageOptionButton::initWithNormalImage(normalImage, selectedImage, normalImage, target, selector))
    {
        return false;
    }
    else
    {
        this->setOpacityModifyRGB(true);
        this->selectedBtn = true;
        
        tabSprite = CCArray::createWithCapacity(2);
        
        // this->label=CCLabelTTF::create(textOnButton, "Arial", fontSize, CCSizeMake(this->getContentSize().width - 80, 0), kCCTextAlignmentCenter);
        
        this->label=CCLabelTTF::create(textOnButton, "Georgia", fontSize);
        
        this->label->setColor(ccc3(0, 0, 0));
        //this->setAnchorPoint(ccp(0, 0));
        
        this->label->setPosition(ccp(this->boundingBox().origin.x + this->getContentSize().width, this->boundingBox().origin.y + this->getContentSize().height));
        
        
        float percentLabelOnBtn = label->getContentSize().width/this->getContentSize().width * 100;
        
        //float percentBtnOnBtn = this->getContentSize().height/CCEGLView::sharedOpenGLView()->getVisibleSize().height * 100;
        
        //CCLOG("Button width: %f Label width: %f percent: %f", this->getContentSize().width, label->getContentSize().width, percentLabelOnBtn);
        
        //CCLOG("Button Percent width: %f", percentBtnOnBtn);
        
        //70
        while(percentLabelOnBtn > 68){
            fontSize-=1;
            this->label->setFontSize(fontSize);
            //this->setScale(1.25);
            percentLabelOnBtn = label->getContentSize().width/this->getContentSize().width * 100;
            //CCLOG("Button width2: %f Label width2: %f percent2: %f", this->getContentSize().width, label->getContentSize().width, percentLabelOnBtn);
            
        }
        
        this->addChild(label,1);
        
        
        tabSprite->addObject(CCSprite::create(firstImg));
        tabSprite->addObject(CCSprite::create(secondImg));
        
        
        CCObject *obj = NULL;
        
        CCARRAY_FOREACH(tabSprite, obj){
            CCSprite *spriteImage = dynamic_cast<CCSprite*>(obj);
            
            switch (tabSprite->indexOfObject(obj)) {
                case 0:
                    spriteImage->setPosition(ccp(this->label->getPositionX() - spriteImage->getContentSize().width, this->label->getPositionY()));
                    this->addChild(spriteImage,2);
                    
                    break;
                case 1:
                    spriteImage->setPosition(ccp(this->label->getPositionX() + spriteImage->getContentSize().width, this->label->getPositionY()));
                    this->addChild(spriteImage,2);
                    
                    break;
                default:
                    break;
            }
            
           // spriteImage->setScale(0.52f);
            
        }
        
        return true;
    }
    
}

bool ImageOptionButton::init(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites){
    
    
    if(!ImageOptionButton::initWithNormalImage(normalImage, selectedImage, normalImage, target, selector))
    {
        return false;
    }
    else
    {
        this->setOpacityModifyRGB(true);
        this->selectedBtn = true;
        
        if (numberOfSprites > 0 && numberOfSprites <6)
        {
            tabSprite = CCArray::createWithCapacity(numberOfSprites);
        }else
        {
            tabSprite = CCArray::createWithCapacity(MAX_IMG_ON_BTN);
            numberOfSprites = MAX_IMG_ON_BTN;
        }
        
        
        for (int i = 0; i<numberOfSprites; i++) {
            if(i%2==0){
                tabSprite->addObject(CCSprite::create(firstImg));
            }else{
                tabSprite->addObject(CCSprite::create(secondImg));
            }
        }
        
        this->createSpritesOnButton(numberOfSprites);
        
        return true;
    }
    
}

void ImageOptionButton::createSpritesOnButton(int numberOfSpr){
    CCObject *obj = NULL;
    
    
    if(numberOfSpr == 1)
    {
        CCARRAY_FOREACH(tabSprite, obj){
            CCSprite *spriteImage = dynamic_cast<CCSprite*>(obj);
            
            spriteImage->setPosition(ccp(this->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
            
            this->addChild(spriteImage,1);
            
            spriteImage->setScale(0.52f);

        }
    }
    else if(numberOfSpr == 2)
    {
        CCARRAY_FOREACH(tabSprite, obj){
            CCSprite *spriteImage = dynamic_cast<CCSprite*>(obj);
            
            switch (tabSprite->indexOfObject(obj)) {
                case 0:
                    spriteImage->setPosition(ccp(0 + spriteImage->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    
                    this->addChild(spriteImage,1);
                    
                    break;
                case 1:
                    spriteImage->setPosition(ccp(this->getContentSize().width - spriteImage->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    
                    this->addChild(spriteImage,1);
                    
                    break;
                    
                default:
                    break;
            }
            
            spriteImage->setScale(0.52f);
            
        }

    }
    else if (numberOfSpr ==3)
    {
        CCARRAY_FOREACH(tabSprite, obj){
            CCSprite *spriteImage = dynamic_cast<CCSprite*>(obj);
            
            switch (tabSprite->indexOfObject(obj)) {
                case 0:
                    spriteImage->setPosition(ccp(0 + spriteImage->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    
                    this->addChild(spriteImage,1);
                    
                    break;
                case 1:
                    spriteImage->setPosition(ccp(this->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    
                    this->addChild(spriteImage,1);
                    
                    break;
                
                case 2:
                    spriteImage->setPosition(ccp(this->getContentSize().width - spriteImage->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    
                    
                    this->addChild(spriteImage,1);
                    
                    break;
                    
                default:
                    break;
            }
            
            spriteImage->setScale(0.52f);
            
        }

    }
    else if (numberOfSpr == 4)
    {
        CCARRAY_FOREACH(tabSprite, obj){
            CCSprite *spriteImage = dynamic_cast<CCSprite*>(obj);
            
            switch (tabSprite->indexOfObject(obj)) {
                case 0:
                    spriteImage->setPosition(ccp(0 + spriteImage->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,1);
                    
                    break;
                case 1:
                    spriteImage->setPosition(ccp(this->getContentSize().width/2 - spriteImage->getContentSize().width/8 , this->boundingBox().origin.y + this->getContentSize().height));
                    
                    this->addChild(spriteImage,2);
                    
                    break;
                case 2:
                    spriteImage->setPosition(ccp(this->getContentSize().width/2 + spriteImage->getContentSize().width/8, this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,3);
                    break;
                case 3:
                    spriteImage->setPosition(ccp(this->getContentSize().width - spriteImage->getContentSize().width/2 , this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,4);
                    break;
                    
                default:
                    break;
            }
            
            spriteImage->setScale(0.52f);
            
        }

    }
    else if (numberOfSpr == 5)
    {
        CCARRAY_FOREACH(tabSprite, obj){
            CCSprite *spriteImage = dynamic_cast<CCSprite*>(obj);
            
            switch (tabSprite->indexOfObject(obj)) {
                case 0:
                    spriteImage->setPosition(ccp(0 + spriteImage->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,1);
                    
                    break;
                case 1:
                    spriteImage->setPosition(ccp(this->getContentSize().width/2 - spriteImage->getContentSize().width/4 , this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,2);
                    
                    break;
                case 2:
                    spriteImage->setPosition(ccp(this->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,3);
                    break;
                case 3:
                    spriteImage->setPosition(ccp(this->getContentSize().width/2 + spriteImage->getContentSize().width/4 , this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,4);
                    
                    break;
                case 4:
                    spriteImage->setPosition(ccp(this->getContentSize().width - spriteImage->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
                    this->addChild(spriteImage,5);
                    
                    break;
                    
                default:
                    break;
            }
            
            spriteImage->setScale(0.52f);
            
        }

    }
    
}


ImageOptionButton* ImageOptionButton::create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* textOnButton, float fontSize, const char* firstImg, const char* secondImg){
    
    ImageOptionButton * button = new ImageOptionButton();
    if (button && button->init(normalImage,selectedImage,target,selector,textOnButton, fontSize, firstImg, secondImg)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
    
}

ImageOptionButton* ImageOptionButton::create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites){
    
    ImageOptionButton * button = new ImageOptionButton();
    if (button && button->init(normalImage,selectedImage,target,selector,firstImg, secondImg, numberOfSprites)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
    
}

void ImageOptionButton::setSelectedBtn(bool selected){
 
    if (!selected) {
        this->setOpacity(125);
        this->selectedBtn = false;
    }else{
        this->setOpacity(255);
        this->selectedBtn = true;
    }
    
}

bool ImageOptionButton::isBtnSelected(){
    return selectedBtn;
}



