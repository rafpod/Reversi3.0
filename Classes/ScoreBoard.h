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
    
    bool init(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int btnType);
    
    bool init(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int btnType, const char* frameFiles);
    
public:
    static ScoreBoard* create(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int btnType);
    
    static ScoreBoard* create(const char* normalBoardFileName, const char* selectedBoardFilename, const char* normalMarkFileName, const char* selectedMarkFile, float fontSize, int btnType, const char* frameFiles);
    
    
    void setSelectedBoard(bool isSelected, bool isHuman=true);
    void setSelectedBoard(int isSelected, int isHuman=1);
    
    void setSelectedBoardForFrame(bool isSelected, bool isHuman=true);
    void setSelectedBoardForFrame(int isSelected, int isHuman=1);
    
    void setScore(int currentScore);
    int getResult();
    void setVisibleScore(bool isVisible);
};

#endif /* defined(__ReversiGL__ScoreBoard__) */
