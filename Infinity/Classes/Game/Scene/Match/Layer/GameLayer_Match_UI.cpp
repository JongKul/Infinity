//
//  GameLayer_Match_UI.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "GameLayer_Match_UI.h"
#include "GameScene_Match.h"

bool GameLayer_Match_UI::init()
{
    CCLayer::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage* changeScene_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,menu_selector(GameLayer_Match_UI::ButtonDelegate_ChangeScene));
    changeScene_Button->setPosition(ccp(0,0));
    CCMenu* menu = CCMenu::create(changeScene_Button, NULL);
    menu->setPosition(ccp(winSize.width * 0.8f, winSize.height * 0.9f));
    this->addChild(menu);
    
    return true;
}

void GameLayer_Match_UI::ButtonDelegate_ChangeScene(cocos2d::CCObject *sender)
{
    GameScene_Match::ChangeScene();
}