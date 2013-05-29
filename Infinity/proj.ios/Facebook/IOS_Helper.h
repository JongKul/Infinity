//
//  IOS_Helper.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

#ifndef __Chess__IOS_Helper__
#define __Chess__IOS_Helper__

#define CharToNs(ch) [[NSString alloc] initWithUTF8String:(ch)]
#define NsToChar(ns) [(ns) UTF8String]

#include "cocos2d.h"


using namespace cocos2d;
class GameUI_MainTitle;

class IOS_Helper
{
public:
    static IOS_Helper* sharedInstance();
public:
    void ShowAlert(const char* str);
    const char* GetApnsDeviceKey();
};

#endif /* defined(__Chess__IOS_Helper__) */
