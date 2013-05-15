//
//  Room_List.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 17..
//
//

#ifndef __Infinity__Room_List__
#define __Infinity__Room_List__

#include <vector>
#include "cocos2d.h"
#include "json.h"

using std::vector;
using namespace cocos2d;

class Room_List : public CCNode
{
public:
    CREATE_FUNC(Room_List);
    bool init()
    {
        user_ID = other_user_ID = NULL;
        user_Name = other_user_Name = NULL;
        cutTurnID = NULL;
        
        this->retain();
        
        return true;
    }
    void SetData_RoomList(std::string user_ID, std::string other_user_ID, std::string user_Name, std::string other_user_Name, std::string turn, int room_Index)
    {
        white = black = winnderID = NULL;
        finishFlag = 0;
        
        this->user_ID = CCString::create(user_ID);
        this->user_ID->retain();
        
        this->other_user_ID = CCString::create(other_user_ID);
        this->other_user_ID->retain();
        
        this->user_Name = CCString::create(user_Name);
        this->user_Name->retain();
        
        this->other_user_Name = CCString::create(other_user_Name);
        this->other_user_Name->retain();
        
        this->cutTurnID = CCString::create(turn);
        this->cutTurnID->retain();
        
        this->room_Index = room_Index;
    }
    void SetData_RoomInfo(std::string white, std::string black, std::string turn, int finish_flag, std::string winnner, Json::Value& roomData)
    {
        this->white = CCString::create(white);
        this->white->retain();
        
        this->black = CCString::create(black);
        this->black->retain();
        
        this->cutTurnID = CCString::create(turn);
        this->cutTurnID->retain();
        
        this->finishFlag = finish_flag;
        
        this->winnderID = CCString::create(winnner);
        this->winnderID->retain();
        
        room_data.clear();
        for(int i=0; i<roomData.size(); ++i) //서버는 좌상단이 0,0 이다.
        {
            room_data.push_back(roomData[i].asInt());
            CCLOG("data : %d", room_data[i]);
        }
    }
    void Log()
    {
        if(user_ID == NULL || other_user_ID == NULL) return;
        
        CCLOG("id : %s, nick : %s, index : %d, turn : %s", user_ID->getCString(), other_user_ID->getCString(), room_Index, cutTurnID->getCString());
    }
public:
    //room_list
    CCString *user_ID, *other_user_ID;
    CCString *user_Name, *other_user_Name;
    CCString *cutTurnID;
    int room_Index;
    
    //room_info
    CCString *white, *black;
    int finishFlag;
    CCString *winnderID;
    vector<int> room_data;
};
#endif /* defined(__Infinity__Room_List__) */
