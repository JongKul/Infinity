//
//  GameUI_MainTitle.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#ifndef __Chess__GameUI_MainTitle__
#define __Chess__GameUI_MainTitle__

#include "cocos2d.h"
#include "CCTableView.h"
#include "Facebook_Manager.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GameUI_MainTitle_RoomList;
class GameUI_MainTitle_Rank;

class GameUI_MainTitle : public CCNode
{
private:
    GameUI_MainTitle_Rank* uiLayer_Rank;
    GameUI_MainTitle_RoomList* uiLayer_RoomList;
    CCMenuItemImage *button_Home, *button_Playing, *button_NewGame;
private:
    void Init_UISet();
    void Init_Button();
    void Add_UINode(CCNode* ui);
    void ButtonDelegate_Home(CCObject* sender);
    void ButtonDelegate_Playing(CCObject* sender);
    void ButtonDelegate_NewGame(CCObject* sender);
    void ButtonDelegate_Setting(CCObject* sender);
public:
    virtual bool init();
    CREATE_FUNC(GameUI_MainTitle);
};

#endif /* defined(__Chess__GameUI_MainTitle__) */
