//
//  Facebook_Binder_Android.cpp
//  Chess
//
//  Created by �좎룞�숂뼨轅명�占쏙옙on 13. 3. 21..
//
//

#include "Facebook_Binder_Android.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "hellocpp/main.h"

void Facebook_Binder_Android::Login()
{
	JNI_Login();
}

void Facebook_Binder_Android::GetPicture(cocos2d::CCString *fbID)
{

	JNI_Picture(fbID->getCString());
}

void Facebook_Binder_Android::Invtie(cocos2d::CCString *fbID)
{
	JNI_Picture(fbID->getCString());
}

void Facebook_Binder_Android::Post()
{

}

#endif
