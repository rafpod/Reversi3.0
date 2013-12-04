#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{
    
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}
/*
void Java_com_geckolab_reversi_orientationChanged(JNIEnv*  env, jobject thiz, jint orientation)
{
//	CCRect rect = CCRectMake(x, y, w, h);
//		GameScene *gameScene = dynamic_cast<GameScene*>(cocos2d::CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1));
//		gameScene->notifyShowFramesForRect(rect);
	CCLOG("orientation change new method");
}
*/
void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();

        CCLOG("orientation changed1");

    	/*
    	//nowy kod
    	cocos2d::CCEGLView* view = cocos2d::CCDirector::sharedDirector()->getOpenGLView();
    	if (!view) {

    	} else {

    	 if (view->getFrameSize().width != w || view->getFrameSize().height != h) {
    	     view->setFrameSize(w, h);
    	     view->setDesignResolutionSize(w, h, kResolutionShowAll);
    	   }
    	}
    	//koniec nowego kodu
		*/
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 

        CCLOG("orientation changed2");

    }
}

}
