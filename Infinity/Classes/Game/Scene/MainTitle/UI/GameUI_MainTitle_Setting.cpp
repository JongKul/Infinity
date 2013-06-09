//
//  GameUI_MainTitle_Setting.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 6. 9..
//
//

#include "GameUI_MainTitle_Setting.h"
#include "Input_Manager.h"

bool GameUI_MainTitle_Setting::init()
{
    CCNode::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("back_setting.png");
    back->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(back);
    
    sig_Push = CCUserDefault::sharedUserDefault()->getBoolForKey("setting_push", true);
    sig_Sound = CCUserDefault::sharedUserDefault()->getBoolForKey("setting_sound", true);
    
    Init_Button();
    Input_Manager::SetInputEnable(false);
    
    return true;
}

void GameUI_MainTitle_Setting::Init_Button()
{
    if(sig_Sound == true)
    {
        button_Sound = CCMenuItemImage::create("b_on.png", "b_on.png",
                                               this,menu_selector(GameUI_MainTitle_Setting::ButtonDelegate_Sound));
    }
    else
    {
        button_Sound = CCMenuItemImage::create("b_off.png", "b_off.png",
                                               this,menu_selector(GameUI_MainTitle_Setting::ButtonDelegate_Sound));
    }
    
    if(sig_Push == true)
    {
        button_Push = CCMenuItemImage::create("b_on.png", "b_on.png",
                                              this,menu_selector(GameUI_MainTitle_Setting::ButtonDelegate_Push));
    }
    else
    {
        button_Push = CCMenuItemImage::create("b_off.png", "b_off.png",
                                              this,menu_selector(GameUI_MainTitle_Setting::ButtonDelegate_Push));
    }
   
    button_Sound->setPosition(ccp(540, 1280-510));
    button_Push->setPosition(ccp(540, 1280-790));
    
    CCMenu* menu = CCMenu::create(button_Sound, button_Push, NULL);
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
    
    CCMenuItem* setting = CCMenuItemImage::create("b_back2.png", "b_back2.png",
                                                  this,menu_selector(GameUI_MainTitle_Setting::ButtonDelegate_Back));
    setting->setPosition(ccp(605, 1280-300));
    //setting->setScale(1.5f);
    menu = CCMenu::create(setting, NULL);
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
}

void GameUI_MainTitle_Setting::ButtonDelegate_Back(CCObject* sender)
{
    Input_Manager::SharedInstance()->SetInputEnable(true);
    this->getParent()->removeChild(this);
}

void GameUI_MainTitle_Setting::ButtonDelegate_Sound(CCObject* sender)
{
    sig_Sound = !sig_Sound;
    
    if(sig_Sound == true)
    {
        button_Sound->setNormalImage(CCSprite::create("b_on.png"));
        button_Sound->setSelectedImage(CCSprite::create("b_on.png"));
    }
    else
    {
        button_Sound->setNormalImage(CCSprite::create("b_off.png"));
        button_Sound->setSelectedImage(CCSprite::create("b_off.png"));
    }
  
    CCUserDefault::sharedUserDefault()->setBoolForKey("setting_sound", sig_Sound);
}
void GameUI_MainTitle_Setting::ButtonDelegate_Push(CCObject* sender)
{
    sig_Push = !sig_Push;
    
    if(sig_Push == true)
    {
        button_Push->setNormalImage(CCSprite::create("b_on.png"));
        button_Push->setSelectedImage(CCSprite::create("b_on.png"));
    }
    else
    {
        button_Push->setNormalImage(CCSprite::create("b_off.png"));
        button_Push->setSelectedImage(CCSprite::create("b_off.png"));
    }
    
    CCUserDefault::sharedUserDefault()->setBoolForKey("setting_push", sig_Push);
}