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
    fri->fbID = fbID;
    friendList->addObject(fri);
}
void Facebook_Manager::Callback_Login(bool ret)
{
    CCLog("Facebook_Manager Callback_Login");
    CCLog("SetMyAccount name : %s, id : %s", myAccount->name->getCString(), myAccount->fbID->getCString());
    if(delegate_Login != NULL)delegate_Login->fb_Callback_Login(ret);
    delegate_Login = NULL;
}

void Facebook_Manager::GetPicture(cocos2d::CCString *fbID, Facebook_Callback* del)
{
    delegate_Picture = del;
    fbBinder->GetPicture(fbID);
}
void Facebook_Manager::Callback_Picture(cocos2d::CCString *fbID, cocos2d::CCSprite *picture)
{
    if(delegate_Picture != NULL) delegate_Picture->fb_Callback_Picture(fbID, picture);
}

void Facebook_Manager::Post()
{
    fbBinder->Post();
}