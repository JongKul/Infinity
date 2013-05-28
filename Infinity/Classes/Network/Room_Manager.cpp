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

Room_Manager::Room_Manager()
{
    callBack = NULL;
    curMatchRoom = NULL;
}

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
        //room_List[i]->Log();
    }
    //void WebRequest_RoomInfo(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* other_fbID, int roomIndex)
    if(room_List.size() > 0)
    {
        //WebRequest_RoomInfo(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_RoomInfo), "Post RoomInfo",
        //                    room_List[0]->user_ID->getCString(), room_List[0]->other_user_ID->getCString(), room_List[0]->room_Index);
    }
}

void Room_Manager::Request_RoomInfo(int roomIndex, Room_Callback *del)
{
    callBack = del;
    
    Room_List* room = NULL;
    
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            room = room_List[i];
            break;
        }
    }
    
    if(room == NULL)
    {
        CCLOG("Room = NULL");
        if(callBack != NULL) callBack->Callback_RoomInfo(-1);
        return;
    }
    
    //void WebRequest_RoomInfo(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* other_fbID, int roomIndex)
    WebRequest_RoomInfo(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_RoomInfo), "Post RoomInfo",
                        room->user_ID->getCString(), room->other_user_ID->getCString(), room->room_Index);
}

void Room_Manager::Request_RoomMake(cocos2d::CCString *myID, cocos2d::CCString *otherID, Room_Callback* del)
{
    callBack = del;
    
    WebRequest_RoomInfo(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_RoomMake), "Post RoomMake",
                        myID->getCString(), otherID->getCString(), -1);
}

void Room_Manager::onHttpRequestCompleted_RoomMake(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_RoomMake!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_RoomMake = false!!");
        if(callBack != NULL) callBack->Callback_RoomMake(-1);
        return;
    }
    
    int roomIndex = root["room_index"].asInt();
    std::string otherID = root["white"].asString();
    if(otherID.compare(Facebook_Manager::sharedInstance()->getMyAccount()->fbID->m_sString) == 0) otherID = root["black"].asString();
    std::string otherName = Facebook_Manager::sharedInstance()->Get_FriendName(CCString::create(otherID))->m_sString;
    
    Room_List* room = Room_List::create();
    room->SetData_RoomList( Facebook_Manager::sharedInstance()->getMyAccount()->fbID->m_sString, otherID,
                            Facebook_Manager::sharedInstance()->getMyAccount()->name->m_sString, otherName,
                            root["turn"].asString(), roomIndex);
    room_List.push_back(room);
    
    std::string winner = "";
    if(root["winner"].isNull() == false) winner = root["winner"].asString();
    
    room->SetData_RoomInfo(root["white"].asString(), root["black"].asString(), root["turn"].asString(),
                           root["finish_flag"].asInt(), winner,root["room_data"]);
    
    
    if(callBack != NULL) callBack->Callback_RoomMake(roomIndex);
}

void Room_Manager::onHttpRequestCompleted_RoomInfo(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_RoomInfo!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_RoomInfo = false!!");
        if(callBack != NULL) callBack->Callback_RoomInfo(-1);
        return;
    }
    
    CCLOG(root.toStyledString().c_str());
                    
    int roomIndex = root["room_index"].asInt();
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            //room_List[i]->Log();
            
            std::string winner = "";
            if(root["winner"].isNull() == false) winner = root["winner"].asString();
            
            room_List[i]->SetData_RoomInfo(root["white"].asString(), root["black"].asString(), root["turn"].asString(), root["finish_flag"].asInt(), winner, root["room_data"]);
            
            if(callBack != NULL) callBack->Callback_RoomInfo(roomIndex);
            
            break;
        }
    }
}

bool Room_Manager::SetMatchRoom(int roomIndex)
{
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            curMatchRoom = room_List[i];
            return true;
        }
    }
    
    return false;
}

void Room_Manager::RemoveRoom(int roomIndex)
{
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            //Room_List* room = room_List[i];
            room_List.erase(room_List.begin() + i);
            //room->release();
            return;
        }
    }
}

void Room_Manager::Request_RoomTurn(int roomIndex, int x, int y, Room_Callback* del)
{
    callBack = del;
    
    Room_List* room = NULL;
    
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            room = room_List[i];
            break;
        }
    }
    
    if(room == NULL)
    {
        CCLOG("Room = NULL");
        if(callBack != NULL) callBack->Callback_RoomTurn(false);
        return;
    }
    
    CCLOG("Room turn x : %d, y : %d", x , y);
    
    //void WebRequest_Turn(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, int roomIndex, int x, int y)
    WebRequest_Turn(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_Turn),
                    "Post Turn", room->user_ID->getCString(), room->other_user_ID->getCString(), room->room_Index, x, y);
}

void Room_Manager::onHttpRequestCompleted_Turn(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_Turn!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_Turn = false!!");
        if(callBack != NULL) callBack->Callback_RoomTurn(false);
        return;
    }
    
    CCLOG(root.toStyledString().c_str());
    
    int roomIndex = root["room_index"].asInt();
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            std::string winner = "";
            if(root["winner"].isNull() == false) winner = root["winner"].asString();
            
            room_List[i]->SetData_RoomTurn(root["turn"].asString(), root["finish_flag"].asInt(), winner, root["room_data"]);
            if(callBack != NULL) callBack->Callback_RoomTurn(true);
        }
    }
}

void Room_Manager::Request_RoomUpdate(Room_Callback *del)
{
    if(curMatchRoom == NULL)
    {
        CCLOG("CurRoom = NULL");
        if(callBack != NULL) callBack->Callback_RoomUpdate();
    }
    
    callBack = del;
    
    WebRequest_RoomInfo(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_RoomUpdate), "Post RoomUpdate",
                        curMatchRoom->user_ID->getCString(), curMatchRoom->other_user_ID->getCString(), curMatchRoom->room_Index);
}

void Room_Manager::onHttpRequestCompleted_RoomUpdate(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_RoomUpdate!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_RoomUpdate = false!!");
        if(callBack != NULL) callBack->Callback_RoomUpdate();
        return;
    }
    
    //CCLOG(root.toStyledString().c_str());
    
    int roomIndex = root["room_index"].asInt();
    CCLOG("roomIndex : %d", roomIndex);
    for(int i=0; i<room_List.size(); ++i)
    {
        if(room_List[i]->room_Index == roomIndex)
        {
            //room_List[i]->Log();
            
            std::string winner = "";
            if(root["winner"].isNull() == false) winner = root["winner"].asString();
            
            room_List[i]->SetData_RoomTurn(root["turn"].asString(), root["finish_flag"].asInt(), winner, root["room_data"]);

            break;
        }
    }
    
    if(callBack != NULL) callBack->Callback_RoomUpdate();
}

void Room_Manager::Request_RoomEnd(CCString* myId, int roomIndex, Room_Callback* del)
{
    callBack = del;
    
    WebRequest_RoomEnd(this, callfuncND_selector(Room_Manager::onHttpRequestCompleted_RoomEnd), "Post RoomEnd", myId->getCString(), roomIndex);
}

void Room_Manager::onHttpRequestCompleted_RoomEnd(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_RoomEnd!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_RoomEnd = false!!");
        if(callBack != NULL) callBack->Callback_RoomEnd(false);
        return;
    }
    
    if(callBack != NULL) callBack->Callback_RoomEnd(true);
}