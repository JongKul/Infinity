//
//  Native_Helper.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 3. 29..
//
//

#include "Native_Helper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IOS_Helper.h"
#endif

void Native_ShowAlert(const char* str)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOS_Helper::sharedInstance()->ShowAlert(str);
#endif
}