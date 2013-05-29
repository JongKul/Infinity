//
//  WebCommunication.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 3. 29..
//
//

#include "WebCommunication.h"
#include "Facebook_Account.h"
using namespace cocos2d::extension;

void WebRequest_Login(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* nick, const char* deviceToken, int os)
{
    Json::Value root;
    root["user_id"] = fbID;
    root["user_name"] = nick;
    root["token"] = deviceToken;
    root["os"] = os;
    
    WebRequest_Common(pTarget, pSelector, root, tag, "http://infinityserver-JKInfinity.rhcloud.com/game/login");
}

void WebRequest_SyncFriends(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, CCArray* friend_List)
{
    Json::Value root, array;
    //root["id"] = fbID;
    
    for(int i=0; i<friend_List->count(); ++i)
    {
        Facebook_Account* fri = (Facebook_Account*)friend_List->objectAtIndex(i);
        //Json::Value item;
        //item["user_id"]  = fri->fbID->getCString();
        //item["user_nick"] = fri->name->getCString();
        //array.append(item);
        array.append(fri->fbID->getCString());
    }
    
    root["array"] = array;
    
    //CCLOG(root.toStyledString().c_str());
    
    WebRequest_Common(pTarget, pSelector, root, tag, "http://infinityserver-JKInfinity.rhcloud.com/game/sync_friend_list");
}

void WebRequest_RoomList(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID)
{
    Json::Value root;
    root["user_id"] = fbID;
    
    WebRequest_Common(pTarget, pSelector, root, tag, "http://infinityserver-JKInfinity.rhcloud.com/game/room_list");
}

void WebRequest_RoomInfo(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* other_fbID, int roomIndex)
{
    Json::Value root;
    root["user_id"] = fbID;
    root["other_user_id"] = other_fbID;
    root["room_index"] = roomIndex;
    
    WebRequest_Common(pTarget, pSelector, root, tag, "http://infinityserver-JKInfinity.rhcloud.com/game/room_info");
}

void WebRequest_Turn(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* other_fbID, int roomIndex, int x, int y)
{
    Json::Value root;
    root["user_id"] = fbID;
    root["other_user_id"] = other_fbID;
    root["room_index"] = roomIndex;
    root["x"] = x;
    root["y"] = y;
    
    WebRequest_Common(pTarget, pSelector, root, tag, "http://infinityserver-JKInfinity.rhcloud.com/game/room_turn");
}

void WebRequest_RoomEnd(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, int roomIndex)
{
    Json::Value root;
    root["user_id"] = fbID;
    root["room_index"] = roomIndex;
    
    WebRequest_Common(pTarget, pSelector, root, tag, "http://infinityserver-JKInfinity.rhcloud.com/game/room_end");
}

void WebRequest_Common(CCObject* pTarget, SEL_CallFuncND pSelector, const Json::Value& root, const char* tag, const char* url)
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(url);
    request->setRequestType(CCHttpRequest::kHttpPost);
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    request->setHeaders(headers);
    request->setResponseCallback(pTarget, pSelector);
    
    Json::StyledWriter writer;
    std::string str =  writer.write(root);
    //CCLOG("Json : %s", str.c_str());
    request->setRequestData(str.c_str(), strlen(str.c_str()));
    
    request->setTag(tag);
    CCHttpClient::getInstance()->send(request);
    request->release();
}

bool WebResponse_Common(cocos2d::CCNode *sender, void *data, Json::Value& root)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    
    if (!response) return false;
    
    // You can get original request type from: response->request->reqType
    //if (0 != strlen(response->getHttpRequest()->getTag())) CCLog("%s completed", response->getHttpRequest()->getTag());
    
    int statusCode = response->getResponseCode();
    char statusString[128] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return false;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    if((*buffer).size() <= 0) return true;
    
    Json::Reader reader;
    std::string str;
    str = &((*buffer)[0]);
    
    bool parsingSuccessful = reader.parse( str, root );
    if(parsingSuccessful == false) CCLog("parsingSuccessful : false");
    
    return parsingSuccessful;
}