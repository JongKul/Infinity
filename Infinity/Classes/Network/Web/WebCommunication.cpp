//
//  WebCommunication.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 3. 29..
//
//

#include "WebCommunication.h"
using namespace cocos2d::extension;

void WebRequest_Login(CCObject* pTarget, SEL_CallFuncND pSelector, const char* tag, const char* fbID, const char* nick)
{
    Json::Value root;
    root["id"] = fbID;
    root["nick"] = nick;
    
    WebRequest_Common(pTarget, pSelector, root, tag, "http://leejk86-JKInfinity.rhcloud.com/login");
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
    CCLOG("Json : %s", str.c_str());
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
    Json::Reader reader;
    std::string str;
    str = &((*buffer)[0]);
    
    bool parsingSuccessful = reader.parse( str, root );
    if(parsingSuccessful == false) CCLog("parsingSuccessful : false");
    
    return parsingSuccessful;
}