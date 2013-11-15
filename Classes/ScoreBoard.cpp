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
        
        this->whoseMove = 1;
        
    
        this->mark = CCSprite::create(normalMarkFileName);
        
        score = 0;
        this->resultLabel = CCLabelTTF::create("0", "Arial", fontSize);
        this->resultLabel->setColor(ccc3(0, 0, 0));
        
        this->btnType = type;
    
        switch (btnType) {
            case BTN_LEFT:           
                this->mark->setPosition(ccp(this->getPositionX() + this->mark->getContentSize().width + 20, this->getPositionY() + this->mark->getContentSize().height));
                break;
            
            case BTN_RIGHT:
                this->mark->setPosition(ccp(this->getPositionX() + this->getContentSize().width - this->mark->getContentSize().width - 20, this->getPositionY() + this->mark->getContentSize().height));
            
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


void ScoreBoard::setScore(int currentScore){
    score = currentScore;
    CCString *scoreString = CCString::createWithFormat("%i",currentScore);    
    this->resultLabel->setString(scoreString->getCString());
    
}

int ScoreBoard::getResult(){
    return score;
}

