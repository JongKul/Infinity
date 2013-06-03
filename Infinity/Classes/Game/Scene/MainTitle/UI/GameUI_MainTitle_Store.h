//
//  GameUI_MainTitle_Store.h
//  Infinity
//
//  Created by 정 기호 on 13. 6. 4..
//
//

#ifndef __Infinity__GameUI_MainTitle_Store__
#define __Infinity__GameUI_MainTitle_Store__

#include "cocos2d.h"
#include "GameUI_MainTitle.h"

using namespace cocos2d;

class GameUI_MainTitle_Store : public CCNode
{
private:
    GameUI_MainTitle* uiMain;
public:
    virtual bool init();
    CREATE_FUNC(GameUI_MainTitle_Store);
public:
    void SetGameLayer(GameUI_MainTitle* main){ uiMain = main; }
};

#endif /* defined(__Infinity__GameUI_MainTitle_Store__) */
