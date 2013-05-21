//
//  GameLayer_Match_Main.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#ifndef __Infinity__GameLayer_Match_Main__
#define __Infinity__GameLayer_Match_Main__

#include "cocos2d.h"
#include "Room_Manager.h"

using namespace cocos2d;

class Match_Map;
class GameScene_Match;

class GameLayer_Match_Main : public CCLayer, public Room_Callback
{
public:
    CREATE_FUNC(GameLayer_Match_Main);
    virtual bool init();
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
private:
    Match_Map* cur_Map;
    int myTurnTag;
    CCString* prevCurnID;
    bool isRequestRoomUpdate;
    void Schedule_RoomUpdate(float time);
public:
    GameScene_Match* matchScene;
    Match_Map* GetMatchMap();
public:
    virtual void Callback_RoomTurn(bool ret);
    virtual void Callback_RoomUpdate();
};

#endif /* defined(__Infinity__GameLayer_Match_Main__) */
