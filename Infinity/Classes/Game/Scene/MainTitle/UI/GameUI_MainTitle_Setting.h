//
//  GameUI_MainTitle_Setting.h
//  Infinity
//
//  Created by 정 기호 on 13. 6. 9..
//
//

#ifndef __Infinity__GameUI_MainTitle_Setting__
#define __Infinity__GameUI_MainTitle_Setting__

#include "cocos2d.h"
#include "GameUI_MainTitle.h"

using namespace cocos2d;

class GameUI_MainTitle_Setting : public CCNode
{
private:
    GameUI_MainTitle* uiMain;
    bool sig_Sound;
    bool sig_Push;
    CCMenuItemImage *button_Sound, *button_Push;
public:
    virtual bool init();
    CREATE_FUNC(GameUI_MainTitle_Setting);
public:
    void SetGameLayer(GameUI_MainTitle* main){ uiMain = main; }
    
private:
    void Init_Button();
private:
    void ButtonDelegate_Sound(CCObject* sender);
    void ButtonDelegate_Push(CCObject* sender);
    void ButtonDelegate_Back(CCObject* sender);
};

#endif /* defined(__Infinity__GameUI_MainTitle_Setting__) */
