//
//  GameScene_Intro.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 5. 21..
//
//

#include "GameScene_Intro.h"
#include "Scene_Manager.h"
#include "Input_Manager.h"
#include "Facebook_Manager.h"
#include "UILayer_WaitBlack.h"

#pragma region Scene

bool GameScene_Intro::init()
{
    CCScene::init();
    
    CCLayer* layer = GameLayer_Intro::create();
    this->addChild(layer);
    
    return true;
}

void GameScene_Intro::ChangeScene()
{
    Scene_Manager::ChangeScene_MainTitle();
}

#pragma endregion

#pragma region Layer

bool GameLayer_Intro::init()
{
    CCLayer::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* tile = CCSprite::create("loading.png");
    tile->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(tile);
    
    CCMenuItemImage* button_login = CCMenuItemImage::create("f_login2.png", "f_login2.png",
                                                            this,menu_selector(GameLayer_Intro::ButtonDelegate_Login));
    //button_login->setScale(2.5f);
    CCMenu* menu = CCMenu::create(button_login, NULL);
    menu->setPosition(ccp(winSize.width/2, winSize.height * 0.2f));
    
    this->addChild(menu);
    
    return true;
}

void GameLayer_Intro::ButtonDelegate_Login(cocos2d::CCObject *sender)
{
    ReturnInput();
    
    UILayer_WaitBlack::AddLayer();
    Facebook_Manager::sharedInstance()->Login(this);
}

void GameLayer_Intro::fb_Callback_Login (bool ret)
{
    UILayer_WaitBlack::RemoveLayer();
    
    if(ret == true)
    {
        GameScene_Intro::ChangeScene();
    }
}


#pragma endregion