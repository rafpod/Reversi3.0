//
//  ScoreBoard.h
//  ReversiGL
//
//  Created by RafalP on 12.11.2013.
//
//

#ifndef __ReversiGL__ScoreBoard__
#define __ReversiGL__ScoreBoard__

#include "cocos2d.h"

using namespace cocos2d;

class ScoreBoard: public cocos2d::CCSprite{
private:
    CCSprite *mark;
    CCLabelTTF *resultLabel;
    int btnType;
    
    const char* normalBoard;
    const char* selectedBoard;
    
    const char* normalMark;
    const char* selectedMark;
    
    const char* normalMarkAI;
    const char* selectedMarkAI;
    
    int score;
    
    int whoseMove;
    
    
    bool init(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int btnType);
    
public:
    static ScoreBoard* create(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int btnType);
    
    void setSelectedBoard(bool isSelected, bool isHuman=true);
    void setSelectedBoard(int isSelected, int isHuman=1);
    void setScore(int currentScore);
    int getResult();
};

#endif /* defined(__ReversiGL__ScoreBoard__) */
