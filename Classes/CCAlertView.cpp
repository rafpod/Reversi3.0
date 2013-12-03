#include "CCAlertView.h"
#include "VisibleRect.h"

//==============================
//CREATE METHODS
//==============================
/**
 Create AlertView with 2 buttons.
 */
CCAlertView *CCAlertView::create(const char *_title, const char *_message, const char *_cancel, const char *_ok, CCObject *_object, SEL_CallFuncO _selector1, SEL_CallFuncO _selector2, CCSize designSize) {
    CCAlertView *pRet = new CCAlertView();
    if(pRet && pRet->init(_title, _message, _cancel, _ok, _object, _selector1, _selector2, designSize)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);

	return NULL;
}
/**
 Create AlertView with 1 button.
 */
CCAlertView *CCAlertView::create(const char *_title, const char *_message,const char *_ok, CCObject *_object, SEL_CallFuncO _selector1) {
    CCAlertView *pRet = new CCAlertView();
    if(pRet && pRet->init(_title, _message, _ok, _object, _selector1)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
    
	return NULL;
}
//============================
//END CREATE METHODS
//============================

//===========================
//INIT METHODS
//===========================
/**
 Constructor for AlertView with 2 buttons
 */
bool CCAlertView::init(const char *_title, const char *_message, const char *_cancel, const char *_ok, CCObject *_object, SEL_CallFuncO _selector1, SEL_CallFuncO _selector2, CCSize designSize) {
    object    = _object;
    selector1 = _selector1;
    selector2 = _selector2;
    
    

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize visSize = VisibleRect::getVisibleRect().size;
    
    /*
    CCSize resourceSize = CCSizeMake(320, 480);
    
    CCDirector::sharedDirector()->setContentScaleFactor(resourceSize.width/designSize.width);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);
    */
    
    this->setTouchEnabled(true);
    //this->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
    this->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));

    CCSprite *bgSprite = CCSprite::create("blank.png");
    //bgSprite->setTextureRect(CCRect(0, 0, size.width, size.height));
    bgSprite->setTextureRect(CCRect(0, 0, visSize.width, visSize.height));
    bgSprite->setColor(ccc3(0, 0, 0));
	bgSprite->setOpacity(0);
    this->addChild(bgSprite, 1000);

    CCSprite *alertViewSprite = CCSprite::create("alert_body.png");
    this->addChild(alertViewSprite, 1001);


    CCMenuItemImage *button1 = CCMenuItemImage::create("alert_button1.png", "alert_button1_down.png", this, menu_selector(CCAlertView::button1Callback));
    CCMenuItemImage *button2 = CCMenuItemImage::create("alert_button2.png", "alert_button2_down.png", this, menu_selector(CCAlertView::button2Callback));
	button1->setOpacity(180);
	button2->setOpacity(180);

    CCMenu *alertMenu = CCMenu::create(button1, button2, NULL);
    alertMenu->alignItemsHorizontallyWithPadding(7);
    alertMenu->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, 16 + (button1->getContentSize().height / 2.0f)));
    alertViewSprite->addChild(alertMenu);

    CCLabelTTF *titleLabel = CCLabelTTF::create(_title, "HelveticaNeue-Bold", 18);
    titleLabel->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, alertViewSprite->getContentSize().height - 25.0f));
    alertViewSprite->addChild(titleLabel);

    CCLabelTTF *messageLabel = CCLabelTTF::create(_message, "HelveticaNeue", 16, CCSizeMake(alertViewSprite->getContentSize().width - 20.0f, 0), kCCTextAlignmentCenter);
    messageLabel->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, alertViewSprite->getContentSize().height - 55.0f));
    alertViewSprite->addChild(messageLabel);

    CCLabelTTF *cancelLabel = CCLabelTTF::create(_cancel, "HelveticaNeue-Bold", 18);
    cancelLabel->setPosition(ccp(button2->getContentSize().width / 2.0f, button2->getContentSize().height / 2.0f));
    button1->addChild(cancelLabel);

    CCLabelTTF *OKlabel = CCLabelTTF::create(_ok, "HelveticaNeue-Bold", 18);
    OKlabel->setPosition(ccp(button1->getContentSize().width / 2.0f, button1->getContentSize().height / 2.0f));
    button2->addChild(OKlabel);

    bgSprite->runAction(CCFadeTo::create(0.1f, 150));

    CCFiniteTimeAction *scale1 = CCScaleTo::create(0.15f, 1.1f);
    CCFiniteTimeAction *scale2 = CCScaleTo::create(0.1f, 0.9f);
    CCFiniteTimeAction *scale3 = CCScaleTo::create(0.05f, 1.0f);
    alertViewSprite->runAction(CCSequence::create(scale1, scale2, scale3, NULL));

	return true;
}
/**
 Constructor for AlertView with 1 button.
 */
bool CCAlertView::init(const char *_title, const char *_message, const char *_ok, CCObject *_object, SEL_CallFuncO _selector1) {
    object    = _object;
    selector1 = _selector1;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setTouchEnabled(true);
    this->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
    
    CCSprite *bgSprite = CCSprite::create("blank.png");
    bgSprite->setTextureRect(CCRect(0, 0, size.width, size.height));
    bgSprite->setColor(ccc3(0, 0, 0));
	bgSprite->setOpacity(0);
    this->addChild(bgSprite, 1000);
    
    CCSprite *alertViewSprite = CCSprite::create("alert_body.png");
    this->addChild(alertViewSprite, 1001);
    
    
    CCMenuItemImage *button1 = CCMenuItemImage::create("alert_button1.png", "alert_button1_down.png", this, menu_selector(CCAlertView::button1Callback));
	button1->setOpacity(180);
    
    CCMenu *alertMenu = CCMenu::create(button1, NULL);
    alertMenu->alignItemsHorizontallyWithPadding(7);
    alertMenu->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, 16 + (button1->getContentSize().height / 2.0f)));
    alertViewSprite->addChild(alertMenu);
    
    CCLabelTTF *titleLabel = CCLabelTTF::create(_title, "HelveticaNeue-Bold", 18);
    titleLabel->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, alertViewSprite->getContentSize().height - 25.0f));
    alertViewSprite->addChild(titleLabel);
    
    CCLabelTTF *messageLabel = CCLabelTTF::create(_message, "HelveticaNeue", 16, CCSizeMake(alertViewSprite->getContentSize().width - 20.0f, 0), kCCTextAlignmentCenter);
    messageLabel->setPosition(ccp(alertViewSprite->getContentSize().width / 2.0f, alertViewSprite->getContentSize().height - 55.0f));
    alertViewSprite->addChild(messageLabel);
    
    CCLabelTTF *okLabel = CCLabelTTF::create(_ok, "HelveticaNeue-Bold", 18);
    okLabel->setPosition(ccp(button1->getContentSize().width / 2.0f, button1->getContentSize().height / 2.0f));
    button1->addChild(okLabel);
    
    
    bgSprite->runAction(CCFadeTo::create(0.1f, 150));
    
    CCFiniteTimeAction *scale1 = CCScaleTo::create(0.15f, 1.1f);
    CCFiniteTimeAction *scale2 = CCScaleTo::create(0.1f, 0.9f);
    CCFiniteTimeAction *scale3 = CCScaleTo::create(0.05f, 1.0f);
    alertViewSprite->runAction(CCSequence::create(scale1, scale2, scale3, NULL));
    
	return true;
}
//=============================
//END INIT METHODS
//=============================

void CCAlertView::cleanUpCallback() {
    this->removeFromParentAndCleanup(true);
}

void CCAlertView::button1Callback(CCObject *pSender) {
    CCCallFuncO *first  = CCCallFuncO::create(object, selector1, object);
    CCCallFunc *second = CCCallFunc::create(this, callfunc_selector(CCAlertView::cleanUpCallback));
    this->runAction(CCSequence::create(first, second, NULL));
}

void CCAlertView::button2Callback(CCObject *pSender) {
    CCCallFuncO *first  = CCCallFuncO::create(object, selector2, object);
    CCCallFunc *second = CCCallFunc::create(this, callfunc_selector(CCAlertView::cleanUpCallback));
    this->runAction(CCSequence::create(first, second, NULL));
}
