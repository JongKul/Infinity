//
//  Facebook_Binder_IOS.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 21..
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Facebook_Binder_IOS.h"
#include "IOS_Facebook_Manager.h"

void Facebook_Binder_IOS::Login()
{
    IOS_Facebook_Manager::sharedInstance()->Login();
}

void Facebook_Binder_IOS::GetPicture(cocos2d::CCString *fbID)
{
    IOS_Facebook_Manager::sharedInstance()->GetPicture(fbID);
}

void Facebook_Binder_IOS::Post()
{
    IOS_Facebook_Manager::sharedInstance()->Post();
}

#endif