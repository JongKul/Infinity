//
//  IOS_Facebook_Manager.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 21..
//
//

#ifndef __Chess__IOS_Facebook_Manager__
#define __Chess__IOS_Facebook_Manager__

#include "cocos2d.h"
using namespace cocos2d;

class IOS_Facebook_Manager
{
public:
    static IOS_Facebook_Manager* sharedInstance();
    
public:
    void Login();
    void SetMyAccount(const char* name, const char* fbID);
    void AddFriend(const char* name, const char* fbID);
    void Callback_Login(bool ret);
    
public:
    void GetPicture(CCString* fbID);
    void Callback_Picture(const char* fbID, void* picture);
    
public:
    void Post();
};


#endif /* defined(__Chess__IOS_Facebook_Manager__) */
