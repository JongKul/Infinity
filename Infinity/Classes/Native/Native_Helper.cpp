//
//  Native_Helper.cpp
//  Infinity
//
//  Created by ��湲고샇 on 13. 3. 29..
//
//

#include "Native_Helper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOS_Helper.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "hellocpp/main.h"
#endif

void Native_ShowAlert(const char* str)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOS_Helper::sharedInstance()->ShowAlert(str);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JNI_ShowAlert(str);
#endif
}

char buf[1024];
const char*  Native_GetApnsDeviceKey()
{
    const char* defaultKey = "abc123";
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return IOS_Helper::sharedInstance()->GetApnsDeviceKey();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    memset(buf,0,1024);
    JNI_GetToken(buf);
    return buf;
#endif
    return defaultKey;
}
