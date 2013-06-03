//
//  GameUI_MainTitle.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#include "GameUI_MainTitle.h"
#include "GameScene_MainTitle.h"
#include "Native_Helper.h"
#include "UILayer_WaitBlack.h"
#include "Input_Manager.h"
#include "GameUI_MainTitle_RoomList.h"
#include "GameUI_MainTitle_Rank.h"

bool GameUI_MainTitle::init()
{
    CCNode::init();
    
    Init_UISet();
    Init_Button();
    
    ButtonDelegate_Home(NULL);
    
    return true;
}

void GameUI_MainTitle::Init_UISet()
{
    uiLayer_Rank = GameUI_MainTitle_Rank::create(); uiLayer_Rank->SetGameLayer(this);
    uiLayer_RoomList = GameUI_MainTitle_RoomList::create(); uiLayer_RoomList->SetGameLayer(this);
    
    Add_UINode(uiLayer_Rank);
    Add_UINode(uiLayer_RoomList);
}

void GameUI_MainTitle::Init_Button()
{
    button_Home = CCMenuItemImage::create("b_home.png", "b_bhome.png",
                                                           this,menu_selector(GameUI_MainTitle::ButtonDelegate_Home));
    button_Playing = CCMenuItemImage::create("b_play.png", "b_bplay.png",
                                                              this,menu_selector(GameUI_MainTitle::ButtonDelegate_Playing));
    button_Store = CCMenuItemImage::create("b_store.png", "b_bstore.png",
                                                              this,menu_selector(GameUI_MainTitle::ButtonDelegate_Store));
    button_Home->setPosition(ccp(135,1280 - 1155)); button_Home->setRotation(17);
    button_Playing->setPosition(ccp(360,1280 - 1155)); button_Playing->setRotation(17);
    button_Store->setPosition(ccp(585,1280 - 1155)); button_Store->setRotation(17);
    CCMenu* menu = CCMenu::create(button_Home, button_Playing, button_Store, NULL);
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
  
    CCMenuItem* setting = CCMenuItemImage::create("setting.png", "setting.png",
                                                      this,menu_selector(GameUI_MainTitle::ButtonDelegate_Setting));
    setting->setPosition(ccp(605, 1280-120));
    menu = CCMenu::create(setting, NULL);
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
}

void GameUI_MainTitle::Add_UINode(cocos2d::CCNode *child)
{
    child->setVisible(false);
    this->addChild(child, 0);
}
void GameUI_MainTitle::ButtonDelegate_Setting(CCObject* sender)
{
    ReturnInput();
    
    CCLOG("ButtonDelegate_Setting");
}

void GameUI_MainTitle::ButtonDelegate_Home(cocos2d::CCObject *sender)
{
    ReturnInput();
    
    if(uiLayer_Rank->isVisible() == true)
    {
        CCLOG("Home visible");
        return;
    }
    
    button_Home->setNormalImage(CCSprite::create("b_home.png"));
    button_Playing->setNormalImage(CCSprite::create("b_bplay.png"));
    button_Store->setNormalImage(CCSprite::create("b_bstore.png"));
    
    uiLayer_Rank->setVisible(true);
    uiLayer_RoomList->setVisible(false);
}

void GameUI_MainTitle::ButtonDelegate_Playing(cocos2d::CCObject *sender)
{
    ReturnInput();
    
    if(uiLayer_RoomList->isVisible() == true)
    {
        CCLOG("Playing visible");
        return;
    }
    
    button_Home->setNormalImage(CCSprite::create("b_bhome.png"));
    button_Playing->setNormalImage(CCSprite::create("b_play.png"));
    button_Store->setNormalImage(CCSprite::create("b_bstore.png"));
    
    uiLayer_Rank->setVisible(false);
    uiLayer_RoomList->setVisible(true);
}

void GameUI_MainTitle::ButtonDelegate_Store(cocos2d::CCObject *sender)
{
    ReturnInput();
}