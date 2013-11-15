//
//  LanguageManager.h
//  ReversiGL
//
//  Created by RafalP on 05.11.2013.
//
//

#ifndef __ReversiGL__LanguageManager__
#define __ReversiGL__LanguageManager__

#include "cocos2d.h"
#include "LangDefinitions.h"

using namespace cocos2d;

class LanguageManager: public CCObject{

private:
    int lang;
    //bool init();
    LanguageManager();
public:
   static LanguageManager* create();
    void setLang(int language);
    int getLang();    
    CCString* Translate(int stringID);
    
};


#endif /* defined(__ReversiGL__LanguageManager__) */
