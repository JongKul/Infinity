//
//  UILayer_WaitBlack.cpp
//  Infinity
//
//  Created by ��湲고샇 on 13. 5. 18..
//
//

#include "UILayer_WaitBlack.h"
#include "Scene_Manager.h"
#include "Input_Manager.h"

bool UILayer_WaitBlack::init()
{
    CCLayer::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* black = CCSprite::create("Loading_Black.png");
    black->setPosition(ccp(winSize.width/2, winSize.height/2));
    black->setScale(winSize.height);
    black->setOpacity(170);
    
    loading = CCSprite::create("Loading_API.png");
    loading->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    LoadingRotate();
    
    this->addChild(black);
    this->addChild(loading);
    
    return true;
}

UILayer_WaitBlack* UILayer_WaitBlack::GetLayer()
{
    static UILayer_WaitBlack* layer = NULL;
    
    if(layer == NULL)
    {
        layer = UILayer_WaitBlack::create();
        layer->setTag(3010);
        layer->retain();
    }
    
    return layer;
}

void UILayer_WaitBlack::LoadingRotate()
{
    loading->stopAllActions();
    
    CCRotateBy* rotate = CCRotateBy::create(3, 720);
    CCRepeatForever* repeat = CCRepeatForever::create(rotate);
    loading->runAction(repeat);
}

void UILayer_WaitBlack::AddLayer()
{    
    CCScene* curScene = Scene_Manager::GetCurScene();
    
    if(curScene->getChildByTag(3010) == NULL)
    {
        curScene->addChild(GetLayer());
        GetLayer()->LoadingRotate();
    }
    else
    {
        CCLOG("UILayer_WaitBlack exist!!");
    }
    
    Input_Manager::SetInputEnable(false);
}

void UILayer_WaitBlack::RemoveLayer()
{
    GetLayer()->loading->stopAllActions();
    
    CCScene* curScene = Scene_Manager::GetCurScene();
    curScene->removeChild(GetLayer());
    
    Input_Manager::SetInputEnable(true);
}
