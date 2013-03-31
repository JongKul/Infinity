//
//  Facebook_Manager.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 21..
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Facebook_Binder_IOS.h"
#endif

#include "Facebook_Manager.h"
#include "HttpClient.h"
#include "json.h"
#include "WebCommunication.h"
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
    
    cache_Picture = CCDictionary::create();
    cache_Picture->retain();
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        fbBinder = new Facebook_Binder_IOS();
    #endif  
    
    if(fbBinder == NULL)CCLog("fbBinder = NULL!!!!");
}

Facebook_Manager::~Facebook_Manager()
{
    CC_SAFE_DELETE(fbBinder);
}

Facebook_Account* Facebook_Manager::getMyAccount(){ return myAccount; }
CCArray* Facebook_Manager::getFriendList(){ return friendList; }

void Facebook_Manager::Login(Facebook_Callback* del)
{
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
    CCLog("Facebook_Manager Callback_Login");
    CCLog("SetMyAccount name : %s, id : %s", myAccount->name->getCString(), myAccount->fbID->getCString());
    
    WebRequest_Login(this, callfuncND_selector(Facebook_Manager::onHttpRequestCompleted), "POST Login", myAccount->fbID->getCString(), myAccount->name->getCString());
    
    if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(ret);
    delegate_Login = NULL;
}

void Facebook_Manager::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted = false!!");
        return;
    }
    
    CCLog("index : %d", root["user_index"].asInt());
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
    
    if(delegate_Picture != NULL) delegate_Picture->fb_Callback_Picture(fbID, picture);
}

void Facebook_Manager::Post()
{
    fbBinder->Post();
}

void Facebook_Manager::Invtie(cocos2d::CCString *fbID)
{
    fbBinder->Invtie(fbID);
}

int Facebook_Manager::Get_FriendListIndex(CCString* fbID)
{
    int index = 0;
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    for(index=0; index<friList->count(); ++index)
    {
        Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(index);
        if(fri != NULL && fri->fbID->isEqual(fbID) == true)break;
    }
    
    if(index >= friList->count())return -1;
    else return index;
}