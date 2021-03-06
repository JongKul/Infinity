#include "AppDelegate.h"
#include "GameScene_MainTitle.h"
#include "GameScene_Match.h"
#include "GameScene_Intro.h"
#include "Input_Manager.h"
#include "Scene_Manager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    pEGLView->setDesignResolutionSize(720, 1280, kResolutionExactFit);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    Input_Manager::SetInputEnable(true);
   
    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene_Intro::create();
    Scene_Manager::SetCurScene(pScene);
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
   CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
