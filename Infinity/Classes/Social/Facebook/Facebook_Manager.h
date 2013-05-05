//
//  Facebook_Manager.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 21..
//
//

#ifndef __Chess__Facebook_Manager__
#define __Chess__Facebook_Manager__

#include "Facebook_Account.h"
#include "Facebook_Binder_Base.h"
#include "cocos2d.h"
using namespace cocos2d;

class Facebook_Callback
{
public:
    virtual void fb_Callback_Login (bool) = 0;
    virtual void fb_Callback_Picture (CCString* fbID, CCSprite* picture) = 0;
};

class Facebook_Manager:public CCNode
{
public:
    static Facebook_Manager* sharedInstance();
    Facebook_Manager();
    ~Facebook_Manager();
    
private:
    Facebook_Binder_Base* fbBinder;
    CCDictionary* cache_Picture;
    CC_PROPERTY_READONLY(Facebook_Account*, myAccount, MyAccount);
    CC_PROPERTY_READONLY(CCArray*, friendList, FriendList);
    CC_PROPERTY_READONLY(CCArray*, gameFriendList, GameFriendList);
private:
    Facebook_Callback* delegate_Login;
public:
    void Login(Facebook_Callback* del); //내정보, 친구리스트 받는거 까지 포함.
    void SetMyAccount(CCString* name, CCString* fbID);
    void AddFriend(CCString* name, CCString* fbID);
    void Callback_Login(bool ret);
    
private:
    Facebook_Callback* delegate_Picture;
public:
    void GetPicture(CCString* fbID, Facebook_Callback* del);
    CCSprite* GetPicture_FromCache(CCString* fbID);
    void Callback_Picture(CCString* fbID, CCSprite* picture);
    
public:
    void Post();
    
public:
    void Invtie(CCString* fbID);
    
private:
    void onHttpRequestCompleted_Login(cocos2d::CCNode *sender, void *data);
    void onHttpRequestCompleted_SyncFriends(cocos2d::CCNode *sender, void *data);
    void onHttpRequestCompleted_RoomList(cocos2d::CCNode *sender, void *data);
public:
    int Get_FriendListIndex(CCString* fbID, bool isGameFriend);
    bool IsLogin();
    void SetNullDelegate();
};

#endif /* defined(__Chess__Facebook_Manager__) */
