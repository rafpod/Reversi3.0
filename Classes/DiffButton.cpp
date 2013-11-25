//
//  DiffButton.cpp
//  ReversiGL
//
//  Created by RafalP on 25.11.2013.
//
//

#include "DiffButton.h"
#include "cocos2d.h"

using namespace cocos2d;


bool DiffButton::init(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites){
    
    
    if(!DiffButton::initWithNormalImage(normalImage, selectedImage, normalImage, target, selector))
    {
        return false;
    }
    else
    {
        this->setOpacityModifyRGB(true);
        this->selectedBtn = true;
        
        firstImage = ccs("stone_black.png");
        secondImage = ccs("stone_white.png");
        
        if (numberOfSprites > 0 && numberOfSprites <6)
        {
            numbers = numberOfSprites;
        }else
        {
            numbers = 5;
        }
        
        
        for (int i = 0; i<numberOfSprites; i++) {
            if(i%2==0){
                tab[i] = CCSprite::create(firstImage->getCString());
            }else{
                tab[i] = CCSprite::create(secondImage->getCString());
            }
        }
        
        sprite1 =CCSprite::create(firstImage->getCString());
        sprite1->setPosition(ccp(0 + sprite1->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
        sprite1->setScale(0.52f);
        //this->addChild(sprite1,3);
        
        sprite2 =CCSprite::create(secondImage->getCString());
        sprite2->setPosition(ccp(this->getContentSize().width/2 - sprite2->getContentSize().width/4, this->boundingBox().origin.y + this->getContentSize().height));
        sprite2->setScale(0.52f);
        //this->addChild(sprite2,3);
        
        sprite3 =CCSprite::create(firstImage->getCString());
        sprite3->setPosition(ccp(this->getContentSize().width/2, this->boundingBox().origin.y + this->getContentSize().height));
        sprite3->setScale(0.52f);
        //this->addChild(sprite3,3);

        
        createImages(numberOfSprites);

        
        return true;
    }
    
}


void DiffButton::createImages(int numberOfSpr){
    
    
        int positionX = 0;
        for(int i=0; i<numberOfSpr;i++){
            
            switch (i) {
                case 0:
                    positionX = 0 + tab[i]->getContentSize().width/2;
                    
                    break;
                case 1:
                    positionX =  this->getContentSize().width/2 - tab[i]->getContentSize().width/4;
                    
                    break;
                
                case 2:
                    positionX = this->getContentSize().width/2;
                    break;
                    
                case 3:
                    positionX = this->getContentSize().width/2 + tab[i]->getContentSize().width/5;
                    break;
                    
                case 4:
                    positionX = this->getContentSize().width - tab[i]->getContentSize().width/2;
                    break;
                    
                default:
                    positionX = 0 + tab[i]->getContentSize().width/2;
                    break;
                
            }

            
            tab[i]->setPosition(ccp(positionX, this->boundingBox().origin.y + this->getContentSize().height));
            tab[i]->setScale(0.52f);
        
    }
    
    
    for(int i=0; i<numberOfSpr;i++){
        this->addChild(tab[i],3);
    }
    

}


DiffButton* DiffButton::create(const char *normalImage, const char *selectedImage, cocos2d::CCObject *target, SEL_MenuHandler selector, const char* firstImg, const char* secondImg, int numberOfSprites){
    
    DiffButton * button = new DiffButton();
    if (button && button->init(normalImage,selectedImage,target,selector,firstImg, secondImg, numberOfSprites)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
    
}

bool DiffButton::isBtnSelected(){
    
    return selectedBtn;
}

void DiffButton::setSelectedBtn(bool isSelected){
    if(isSelected){
        selectedBtn = true;
        this->setOpacity(255);        
        
        for (int i=0; i<numbers; i++) {
            this->tab[i]->setOpacity(255);
        }
        
        
        
    }else{
        selectedBtn = false;
        this->setOpacity(125);
        
        for (int i=0; i<numbers; i++) {
            if (i%2!=0) {
                tab[i]->setOpacity(240);
            }
        }
        
    }
}

