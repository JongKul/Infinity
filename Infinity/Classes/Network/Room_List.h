//
//  Room_List.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 17..
//
//

#ifndef __Infinity__Room_List__
#define __Infinity__Room_List__

#include "cocos2d.h"
using namespace cocos2d;

class Room_List : public CCNode
{
public:
    CREATE_FUNC(Room_List);
    bool init()
    {
        nick = fbID = NULL;
        this->retain();
        return true;
    }
    void SetData(std::string fbID, std::string nick, int room_Index, int turn)
    {
        this->fbID = CCString::create(fbID);
        this->fbID->retain();
        this->nick = CCString::create(nick);
        this->nick->retain();
        this->room_Index = room_Index;
        this->turn = turn;
    }
    void Log()
    {
        if(nick == NULL || fbID == NULL) return;
        
        CCLOG("id : %s, nick : %s, index : %d, turn : %d", fbID->getCString(), nick->getCString(), room_Index, turn);
    }
public:
    CCString* fbID;
    CCString* nick;
    int room_Index;
    int turn;
};
#endif /* defined(__Infinity__Room_List__) */
