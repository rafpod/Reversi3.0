//
//  AppMacros.h
//  ReversiGL
//
//  Created by RafalP on 21.10.2013.
//
//

#ifndef ReversiGL_AppMacros_h
#define ReversiGL_AppMacros_h

#include "cocos2d.h"

#define DESIGN_RESOLUTION_320X480    0
#define DESIGN_RESOLUTION_640X960   1
#define DESIGN_RESOLUTION_1280X1920  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_1280X1920

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(320, 480),   "320x480-iphone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(640, 960),  "640x960-iphonehd" };
static Resource largeResource  =  { cocos2d::CCSizeMake(1280, 1920), "1280x1920" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_320X480)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(320, 480);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_640X960)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(640, 960);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1280X1920)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1280, 1920);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)


#endif
