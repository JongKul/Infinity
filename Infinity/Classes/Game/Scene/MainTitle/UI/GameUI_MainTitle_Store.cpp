//
//  GameUI_MainTitle_Store.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 6. 4..
//
//

#include "GameUI_MainTitle_Store.h"
#include "UILayer_WaitBlack.h"
#include "Input_Manager.h"
#include "Native_Helper.h"

bool GameUI_MainTitle_Store::init()
{
    CCNode::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("store.png");
    back->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(back);
    
    Init_Button();
    
    return true;
}

void GameUI_MainTitle_Store::Init_Button()
{
    CCMenuItem* eraser = CCMenuItemImage::create("b_buy.png", "b_buy.png",
                                                  this,menu_selector(GameUI_MainTitle_Store::ButtonDelegate_Eraser));
    CCMenuItem* undo = CCMenuItemImage::create("b_buy.png", "b_buy.png",
                                                 this,menu_selector(GameUI_MainTitle_Store::ButtonDelegate_Undo));
    
    eraser->setPosition(ccp(533, 1280-413));
    undo->setPosition(ccp(533, 1280-652));
    
    CCMenu* menu = CCMenu::create(eraser, undo, NULL);
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
}

void GameUI_MainTitle_Store::ButtonDelegate_Eraser(CCObject* sender)
{
    ReturnInput();
    
    CCLOG("ButtonDelegate_Eraser");
    
    Native_ShowAlert("Buy Eraser");
}
void GameUI_MainTitle_Store::ButtonDelegate_Undo(CCObject* sender)
{
    ReturnInput();
    
    CCLOG("ButtonDelegate_Undo");
    
    Native_ShowAlert("Buy Undo");
}