//
//  GameScene_MainTitle.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#ifndef __Infinity__GameScene_Match_
#define __Infinity__GameScene_Match__

#include "cocos2d.h"

using namespace cocos2d;

class GameLayer_Match_UI;
class GameLayer_Match_Main;
class Match_Map;

class GameScene_Match : public CCScene
{
public:
    CREATE_FUNC(GameScene_Match);
    virtual bool init();
public:
    static void ChangeScene();
public:
    void UpdateUI_GameInfo();
    Match_Map* GetMatchMap();
    virtual void onEnterTransitionDidFinish();
private:
    GameLayer_Match_UI* uiLayer;
    GameLayer_Match_Main* mainLayer;
};

#endif /* defined(__Infinity__GameScene_MainTitle__) */
