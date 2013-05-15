//
//  Room_Manager.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 17..
//
//

#include "Room_Manager.h"
#include "Facebook_Manager.h"
#include "WebCommunication.h"

Room_Manager* Room_Manager::sharedInstance()
{
    static Room_Manager instance;
    
    return &instance;
}

void Room_Manager::Init_RoomList(Json::Value &root)
{
    room_List.clear();
    
    Json::Value array = root["array"];
    for(int i=0; i<array.size(); ++i)
    {
        Json::Value item = array[i];
        Room_List* room = Room_List::create();
        room->SetData_RoomList( Facebook_Manager::sharedInstance()->getMyAccount()->fbID->m_sString, item["user_id"].asString(),
                                Facebook_Manager::sharedInstance()->getMyAccount()->name->m_sString, item["user_name"].asString(),
                                item["turn"].asString(), item["room_index"].asInt());
        room_List.push_back(room);
    }
    
    CCLOG("room_List");
    
    for(int i=0; i<room_List.size(); ++i)
    {
        room_List[i]->Log();
    }
    //void WebRequest_RoomInfo(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* other_fbID, int roomIndex)
    WebRequest_RoomInfo(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_RoomInfo),
                        "Post RoomInfo", room_List[0]->user_ID->getCString(), room_List[0]->other_user_ID->getCString(), room_List[0]->room_Index);
    
    CCLOG("WebRequest_RoomInfo");
}

void Room_Manager::onHttpRequestCompleted_RoomInfo(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_RoomInfo!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_RoomInfo = false!!");
        return;
    }
    
    CCLOG(root.toStyledString().c_str());
                    
    int roomIndex = root["room_index"].asInt();
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            room_List[i]->Log();
            
            std::string winner = "";
            if(root["winner"].isNull() == false) winner = root["winner"].asString();
            
            room_List[i]->SetData_RoomInfo(root["white"].asString(), root["black"].asString(), root["turn"].asString(), root["finish_flag"].asInt(), winner, root["room_data"]);
            break;
        }
    }
 
    //void WebRequest_Turn(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, int roomIndex, int x, int y)
    WebRequest_Turn(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_Turn),
                    "Post Turn", room_List[0]->user_ID->getCString(), room_List[0]->other_user_ID->getCString(), room_List[0]->room_Index, 4, 2);
}

void Room_Manager::onHttpRequestCompleted_Turn(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_Turn!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_Turn = false!!");
        return;
    }
    
    CCLOG(root.toStyledString().c_str());
    
    int roomIndex = root["room_index"].asInt();
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            room_List[i]->Log();
        }
    }
}