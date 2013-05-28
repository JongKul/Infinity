//
//  Room_Manager.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 17..
//
//

#ifndef __Infinity__Room_Manager__
#define __Infinity__Room_Manager__

#include "cocos2d.h"
#include "HttpClient.h"
#include "json.h"
#include "Room_List.h"
#include <vector>


using namespace cocos2d;
using namespace cocos2d::extension;
using std::vector;

class Room_Callback
{
public:
    virtual void Callback_RoomInfo(int roomIndex) {}
    virtual void Callback_RoomMake(int roomIndex) {}
    virtual void Callback_RoomTurn(bool ret){}
    virtual void Callback_RoomUpdate() {}
    virtual void Callback_RoomEnd(bool ret){}
};

class Room_Manager:public CCNode
{
private:
    Room_Callback* callBack;
public:
    Room_Manager();
    static Room_Manager* sharedInstance();
    std::vector<Room_List*> room_List;
    Room_List* curMatchRoom;
    
private:
    void onHttpRequestCompleted_RoomInfo(cocos2d::CCNode *sender, void *data);
    void onHttpRequestCompleted_RoomMake(cocos2d::CCNode *sender, void *data);
    void onHttpRequestCompleted_Turn(cocos2d::CCNode *sender, void *data);
    void onHttpRequestCompleted_RoomUpdate(cocos2d::CCNode *sender, void *data);
    void onHttpRequestCompleted_RoomEnd(cocos2d::CCNode *sender, void *data);
    
public:
    void Init_RoomList(Json::Value& root);
    
    void SetDelegate(Room_Callback* del) { callBack = del; }
    bool SetMatchRoom(int roomIndex);
    
    void RemoveRoom(int roomIndex);
    
public:
    void Request_RoomInfo(int roomIndex, Room_Callback* del);
    void Request_RoomMake(CCString* myID, CCString* otherID, Room_Callback* del);
    void Request_RoomTurn(int roomIndex, int x, int y, Room_Callback* del);
    void Request_RoomUpdate(Room_Callback* del);
    void Request_RoomEnd(CCString* myId, int roomIndex, Room_Callback* del);
};

#endif /* defined(__Infinity__Room_Manager__) */
