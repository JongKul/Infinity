//
//  Facebook_Manager.cpp
//  Chess
//
//  Created by ��湲고샇 on 13. 3. 21..
//
//



#include "Facebook_Manager.h"
#include <algorithm>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Facebook_Binder_IOS.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Facebook_Binder_Android.h"
#endif


#include "HttpClient.h"
#include "json.h"
#include "WebCommunication.h"
#include "Room_Manager.h"
#include "Native_Helper.h"


using namespace cocos2d::extension;

Facebook_Manager* Facebook_Manager::sharedInstance()
{
    static Facebook_Manager instance;
    
    return &instance;
}
Facebook_Manager::Facebook_Manager()
{
    myAccount = NULL;
    fbBinder = NULL;
    
    friendList = CCArray::createWithCapacity(100);
    friendList->retain();
    
    gameFriendList = CCArray::createWithCapacity(100);
    gameFriendList->retain();
    
    cache_Picture = CCDictionary::create();
    cache_Picture->retain();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        fbBinder = new Facebook_Binder_IOS();
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        fbBinder = new Facebook_Binder_Android();
    #endif  
    
    if(fbBinder == NULL)CCLog("fbBinder = NULL!!!!");
    if(fbBinder == NULL)CCLog("fbBinder = NULL!!!!");
    if(fbBinder == NULL)CCLog("fbBinder = NULL!!!!");
    if(fbBinder == NULL)CCLog("fbBinder = NULL!!!!");
}

Facebook_Manager::~Facebook_Manager()
{
    CC_SAFE_DELETE(fbBinder);
}

Facebook_Account* Facebook_Manager::getMyAccount(){ return myAccount; }
CCArray* Facebook_Manager::getFriendList(){ return friendList; }
CCArray* Facebook_Manager::getGameFriendList(){ return gameFriendList;}

void Facebook_Manager::Login(Facebook_Callback* del)
{
    CCLOG("Facebook_Manager::Login");
    
    if(delegate_Login != NULL) return;
    
    delegate_Login = del;
    fbBinder->Login();
}
void Facebook_Manager::SetMyAccount(cocos2d::CCString *name, cocos2d::CCString *fbID)
{
    if(myAccount == NULL)
    {
        myAccount = Facebook_Account::create();
        myAccount->retain();
    }
    myAccount->name = new CCString(*name);
    myAccount->fbID = new CCString(*fbID);
}
void Facebook_Manager::AddFriend(cocos2d::CCString *name, cocos2d::CCString *fbID)
{

    if(friendList == NULL)
    {
        CCLog("friendList = NULL");
        return;
    }

    for(int i=0; i<friendList->count(); ++i)
    {

        Facebook_Account* fri = (Facebook_Account*)friendList->objectAtIndex(i);


        if(fri->fbID->isEqual(fbID) == true)
        {
            CCLog("AddFriend already exist, id: %s", fbID->getCString());
            return;
        }

    }

  //  CCLog("%s %s" ,name->getCString() ,fbID->getCString() );
    Facebook_Account* fri = Facebook_Account::create();
    fri->name = name;
    fri->name->retain();
    fri->fbID = fbID;
    fri->fbID->retain();
    fri->retain();
    friendList->addObject(fri);
}
void Facebook_Manager::Callback_Login(bool ret)
{
    if(ret == true)
    {
        CCLog("Facebook_Manager Callback_Login");
        CCString* apnsKey = CCString::create(Native_GetApnsDeviceKey());
        CCLog("SetMyAccount name : %s, id : %s, key : %s", myAccount->name->getCString(), myAccount->fbID->getCString(), apnsKey->getCString());
        
        int osType = 0; //1 - ios, 2 - android.
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        osType = 1;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        osType = 2;
#endif
        WebRequest_Login(this, callfuncND_selector(Facebook_Manager::onHttpRequestCompleted_Login), "POST Login", myAccount->fbID->getCString(), myAccount->name->getCString(), apnsKey->getCString(), osType);
    }
    else
    {
        if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(false);
        delegate_Login = NULL;
    }
}

void Facebook_Manager::onHttpRequestCompleted_Login(cocos2d::CCNode *sender, void *data)
{
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(false);
        delegate_Login = NULL;
        CCLOG("onHttpRequestCompleted = false!!");
        return;
    }
    
    CCString* fbID = CCString::create(root["user_id"].asString());
    bool isExist = false;
    for(int i=0; i<friendList->count(); ++i)
    {
        Facebook_Account* fri = (Facebook_Account*)friendList->objectAtIndex(i);
        
        if(fri->fbID->isEqual(fbID) == true)
        {
            CCLog("onHttpRequestCompleted_Login already exist, id: %s", fbID->getCString());
            isExist = true;
            break;
        }
        
    }
    
    if(isExist == false)
    {
        Facebook_Account* fri = Facebook_Account::create();
        fri->name = CCString::create(root["user_name"].asString()) ;
        fri->name->retain();
        fri->fbID = CCString::create(root["user_id"].asString());
        fri->fbID->retain();
        fri->win = root["win"].asInt();
        fri->lose = root["lose"].asInt();
        fri->isPlayGame = true;
        fri->retain();
        gameFriendList->addObject(fri);
    }
    
    WebRequest_SyncFriends(this, callfuncND_selector(Facebook_Manager::onHttpRequestCompleted_SyncFriends), "Post SyncFriends", myAccount->fbID->getCString(), friendList);
    CCLOG(root.toStyledString().c_str());
    CCLog("win : %d, lose : %d", root["win"].asInt(), root["lose"].asInt());
}

void Facebook_Manager::onHttpRequestCompleted_SyncFriends(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_SyncFriends!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(false);
        delegate_Login = NULL;
        CCLOG("onHttpRequestCompleted_SyncFriends = false!!");
        return;
    }
    
    Json::Value array = root["array"];
    for(int i=0; i<array.size(); ++i)
    {
        Json::Value item = array[i];
        
        int index = 0;
        bool isExist = false;
        CCString* fbID = CCString::create(item["user_id"].asString());
        CCArray* friList = Facebook_Manager::sharedInstance()->getGameFriendList();
        
        for(index=0; index<friList->count(); ++index)
        {
            Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(index);
            if(fri != NULL && fri->fbID->isEqual(fbID) == true)
            {
                isExist = true;
                break;
            }
        }
        
        if(isExist == true) continue;
      
        Facebook_Account* fri = Facebook_Account::create();
        fri->name = CCString::create(item["user_name"].asString()) ;
        fri->name->retain();
        fri->fbID = CCString::create(item["user_id"].asString());
        fri->fbID->retain();
        fri->win = item["win"].asInt();
        fri->lose = item["lose"].asInt();
        fri->isPlayGame = true;
        fri->retain();
        gameFriendList->addObject(fri);
    }
    
    std::sort(gameFriendList->data->arr, gameFriendList->data->arr + gameFriendList->data->num, Sort_GameFriends);
    
    if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(true);
    delegate_Login = NULL;
    
    return;
    
    WebRequest_RoomList(this, callfuncND_selector(Facebook_Manager::onHttpRequestCompleted_RoomList), "Post RoomList", myAccount->fbID->getCString());
}

void Facebook_Manager::onHttpRequestCompleted_RoomList(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_RoomList!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(false);
        delegate_Login = NULL;
        CCLOG("onHttpRequestCompleted_RoomList = false!!");
        return;
    }
    
    CCLOG(root.toStyledString().c_str());

    Room_Manager::sharedInstance()->Init_RoomList(root);
    if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(true);
    delegate_Login = NULL;
}


void Facebook_Manager::GetPicture(cocos2d::CCString *fbID, Facebook_Callback* del)
{
    CCSprite* cachedPicture = (CCSprite*)cache_Picture->objectForKey(fbID->m_sString);
    if(cachedPicture != NULL)
    {
        if(del != NULL)
        {
            CCLOG("Picure Cached ID : %s", fbID->getCString());
            cachedPicture->setParent(NULL);
            del->fb_Callback_Picture(fbID, cachedPicture);
            return;
        }
    }
    
    delegate_Picture = del;
    fbBinder->GetPicture(fbID);
}

CCSprite* Facebook_Manager::GetPicture_FromCache(cocos2d::CCString *fbID)
{
    CCSprite* cachedPicture = (CCSprite*)cache_Picture->objectForKey(fbID->m_sString);
    if(cachedPicture != NULL)cachedPicture->setParent(NULL);
    
    return cachedPicture;
}

void Facebook_Manager::Callback_Picture(cocos2d::CCString *fbID, cocos2d::CCSprite *picture)
{
    picture->retain();
    cache_Picture->setObject(picture, fbID->m_sString);
    
    CCLOG("Picture id : %s", fbID->getCString());
    
    if(delegate_Picture != NULL) delegate_Picture->fb_Callback_Picture(fbID, picture);
    else CCLOG("delegate_Picture = NULL");
}

void Facebook_Manager::Post()
{
    fbBinder->Post();
}

void Facebook_Manager::Invtie(cocos2d::CCString *fbID)
{
    fbBinder->Invtie(fbID);
}

int Facebook_Manager::Get_FriendListIndex(CCString* fbID, bool isGameFriend)
{
    int index = 0;
    CCArray* friList;
    
    if(isGameFriend == false)
        friList= Facebook_Manager::sharedInstance()->getFriendList();
    else
        friList = Facebook_Manager::sharedInstance()->getGameFriendList();
    
    for(index=0; index<friList->count(); ++index)
    {
        Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(index);
        if(fri != NULL && fri->fbID->isEqual(fbID) == true)break;
    }
    
    if(index >= friList->count())return -1;
    else return index;
}

CCString* Facebook_Manager::Get_FriendName(CCString* fbID)
{
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    
    for(int i = 0; i < friList->count(); ++i)
    {
        Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(i);
        if(fri != NULL && fri->fbID->isEqual(fbID) == true) return fri->name;
    }
    
    return NULL;
}

bool  Facebook_Manager::IsLogin()
{
    return myAccount != NULL;
}

void Facebook_Manager::SetNullDelegate()
{
    delegate_Login = NULL;
    delegate_Picture = NULL;
    
    CCLOG("SetNullDelegate");
}
