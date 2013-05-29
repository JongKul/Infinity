//
//  WebCommunication.h
//  Infinity
//
//  Created by 정 기호 on 13. 3. 29..
//
//

#ifndef __Infinity__WebCommunication__
#define __Infinity__WebCommunication__

#include "HttpClient.h"
#include "json.h"
#include "cocos2d.h"
using namespace cocos2d;

void WebRequest_Login(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* nick, const char* deviceToken, int os);
void WebRequest_SyncFriends(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, CCArray* friend_List);
void WebRequest_RoomList(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID);
void WebRequest_RoomInfo(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* other_fbID, int roomIndex);
void WebRequest_Turn(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* other_fbID, int roomIndex, int x, int y);
void WebRequest_RoomEnd(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, int roomIndex);
void WebRequest_Common(CCObject* pTarget, SEL_CallFuncND pSelector, const Json::Value& root, const char* tag, const char* url);

bool WebResponse_Common(cocos2d::CCNode *sender, void *data, Json::Value& root);

#endif /* defined(__Infinity__WebCommunication__) */
