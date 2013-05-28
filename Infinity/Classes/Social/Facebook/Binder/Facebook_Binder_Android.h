//
//  Facebook_Binder_Android.h
//  Chess
//
//  Created by �좎룞�숂뼨轅명�占쏙옙on 13. 3. 21..
//
//

#ifndef __Chess__Facebook_Binder_Android__
#define __Chess__Facebook_Binder_Android__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "Facebook_Binder_Base.h"

class Facebook_Binder_Android : public Facebook_Binder_Base
{
public:
    virtual void Login();
    virtual void GetPicture(cocos2d::CCString *fbID);
    virtual void Invtie(cocos2d::CCString *fbID);
    virtual void Post();
};

#endif

#endif /* defined(__Chess__Facebook_Binder_IOS__) */
