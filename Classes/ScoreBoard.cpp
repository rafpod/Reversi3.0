//
//  ScoreBoard.cpp
//  ReversiGL
//
//  Created by RafalP on 12.11.2013.
//
//

#include "ScoreBoard.h"

using namespace cocos2d;

#define BTN_LEFT    1
#define BTN_RIGHT   2

bool ScoreBoard::init(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int type){
    
    if(!ScoreBoard::initWithFile(normalBoardFileName)){
        return false;
    }
    else
    {
        normalBoard = normalBoardFileName;
        selectedBoard = selectedBoardFilename;
        
        normalMark = normalMarkFileName;
        selectedMark = selectedMarkFile;
        
        this->normalMarkAI = "pmark_AI_0.png";
        this->selectedMarkAI = "pmark_AI_1.png";        
        
    
        this->mark = CCSprite::create(normalMarkFileName);
        
        score = 0;
        this->resultLabel = CCLabelTTF::create("0", "Arial", fontSize);
        this->resultLabel->setColor(ccc3(0, 0, 0));
        
        this->btnType = type;
    
        switch (btnType) {
            case BTN_LEFT:           
               // this->mark->setPosition(ccp(this->getPositionX() + this->mark->getContentSize().width + 20, this->getPositionY() + this->mark->getContentSize().height));
                this->mark->setPosition(ccp(this->getPositionX() + this->mark->getContentSize().width + 20, this->getContentSize().height/2));
                break;
            
            case BTN_RIGHT:
                //this->mark->setPosition(ccp(this->getPositionX() + this->getContentSize().width - this->mark->getContentSize().width - 20, this->getPositionY() + this->mark->getContentSize().height));
                
                this->mark->setPosition(ccp(this->getPositionX() + this->getContentSize().width - this->mark->getContentSize().width - 20, this->getContentSize().height/2));
            
            default:
                break;
        }
        
        this->resultLabel->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
    
        this->addChild(mark,1);
        this->addChild(resultLabel,1);
    
        return true;
    }
}


ScoreBoard* ScoreBoard::create(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int type){
    
    ScoreBoard * scoreBoard = new ScoreBoard();
    if (scoreBoard && scoreBoard->init(normalBoardFileName, selectedBoardFilename, normalMarkFileName, selectedMarkFile, fontSize, type)) {
        scoreBoard->autorelease();
        return scoreBoard;
    }
    CC_SAFE_DELETE(scoreBoard);
    return NULL;
    
}

bool ScoreBoard::init(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int type, const char* frameFiles){
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(frameFiles);
    
    if(!ScoreBoard::initWithFile(normalBoardFileName)){
        return false;
    }
    else
    {
        
        
        normalBoard = normalBoardFileName;
        selectedBoard = selectedBoardFilename;
        
        normalMark = normalMarkFileName;
        selectedMark = selectedMarkFile;
        
        this->normalMarkAI = "gui/pmark_AI_0.png";
        this->selectedMarkAI = "gui/pmark_AI_1.png";
        
        
        this->mark = CCSprite::createWithSpriteFrameName(normalMarkFileName);
        
        score = 0;
        this->resultLabel = CCLabelTTF::create("0", "Arial", fontSize);
        this->resultLabel->setColor(ccc3(0, 0, 0));
        
        this->btnType = type;
        
        switch (btnType) {
            case BTN_LEFT:
                // this->mark->setPosition(ccp(this->getPositionX() + this->mark->getContentSize().width + 20, this->getPositionY() + this->mark->getContentSize().height));
                this->mark->setPosition(ccp(this->getPositionX() + this->mark->getContentSize().width + 20, this->getContentSize().height/2));
                break;
                
            case BTN_RIGHT:
                //this->mark->setPosition(ccp(this->getPositionX() + this->getContentSize().width - this->mark->getContentSize().width - 20, this->getPositionY() + this->mark->getContentSize().height));
                
                this->mark->setPosition(ccp(this->getPositionX() + this->getContentSize().width - this->mark->getContentSize().width - 20, this->getContentSize().height/2));
                
            default:
                break;
        }
        
        this->resultLabel->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
        
        this->addChild(mark,1);
        this->addChild(resultLabel,1);
        
        return true;
    }
}



ScoreBoard* ScoreBoard::create(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int type, const char* frameFiles){
    
    ScoreBoard * scoreBoard = new ScoreBoard();
    if (scoreBoard && scoreBoard->init(normalBoardFileName, selectedBoardFilename, normalMarkFileName, selectedMarkFile, fontSize, type, frameFiles)) {
        scoreBoard->autorelease();
        return scoreBoard;
    }
    CC_SAFE_DELETE(scoreBoard);
    return NULL;
    
}


/**
 
 */
void ScoreBoard::setSelectedBoard(bool isSelected, bool isHuman){
    if(isHuman)
    {
        if (isSelected) {
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedMark));
        }else{
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalMark));
        }
        
    }else{
        if (isSelected) {
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedMarkAI));
        }else{
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalMarkAI));
        }

    }
}


void ScoreBoard::setSelectedBoard(int isSelected, int isHuman){
    if(isHuman)
    {
        if (isSelected) {
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedMark));
        }else{
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalMark));
        }
        
    }else{
        if (isSelected) {
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(selectedMarkAI));
        }else{
            //human move
            this->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalBoard));
            this->mark->setTexture(CCTextureCache::sharedTextureCache()->addImage(normalMarkAI));
            
        }
        
    }
}

void ScoreBoard::setSelectedBoardForFrame(bool isSelected, bool isHuman){
    if(isHuman)
    {
        if (isSelected) {
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedMark));
        }else{
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalMark));
        }
        
    }else{
        if (isSelected) {
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedMarkAI));
        }else{
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalMarkAI));
        }
        
    }
}


void ScoreBoard::setSelectedBoardForFrame(int isSelected, int isHuman){
    if(isHuman)
    {
        if (isSelected) {
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedMark));
        }else{
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalMark));
        }
        
    }else{
        if (isSelected) {
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedMarkAI));
        }else{
            //human move
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalBoard));
            this->mark->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalMarkAI));
        }
        
    }
}



void ScoreBoard::setScore(int currentScore){
    score = currentScore;
    CCString *scoreString = CCString::createWithFormat("%i",currentScore);    
    this->resultLabel->setString(scoreString->getCString());
    
}

int ScoreBoard::getResult(){
    return score;
}

void ScoreBoard::setVisibleScore(bool isVisible){
    this->resultLabel->setVisible(isVisible);
}

