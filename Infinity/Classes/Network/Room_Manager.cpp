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
        room->SetData(item["id"].asString(), item["nick"].asString(), item["room_index"].asInt(), item["turn"].asInt());
        room_List.push_back(room);
    }
    
    for(int i=0; i<room_List.size(); ++i)
    {
        room_List[i]->Log();
    }
    
    WebRequest_RoomInfo(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_RoomInfo), "Post RoomInfo", Facebook_Manager::sharedInstance()->getMyAccount()->fbID->getCString(), "568652209", 1);
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
    for(int i=0; i<room_List.size(); ++i)
    {
        room_List[i]->Log();
    }
    WebRequest_Turn(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_Turn), "Post Turn", Facebook_Manager::sharedInstance()->getMyAccount()->fbID->getCString(),1, 1, 1);
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
    for(int i=0; i<room_List.size(); ++i)
    {
        room_List[i]->Log();
    }
}