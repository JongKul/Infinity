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

class Room_Manager:public CCNode
{
public:
    static Room_Manager* sharedInstance();
private:
    std::vector<Room_List*> room_List;
    
private:
    void onHttpRequestCompleted_RoomInfo(cocos2d::CCNode *sender, void *data);
    void onHttpRequestCompleted_Turn(cocos2d::CCNode *sender, void *data);
    
public:
    void Init_RoomList(Json::Value& root);
};

#endif /* defined(__Infinity__Room_Manager__) */
