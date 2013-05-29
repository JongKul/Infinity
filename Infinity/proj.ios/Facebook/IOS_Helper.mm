//
//  IOS_Helper.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

#import <Foundation/Foundation.h>
#import "IOS_Helper.h"
#import "IOS_Native.h"
#import "GameUI_MainTitle.h"

IOS_Helper* IOS_Helper::sharedInstance()
{
    static IOS_Helper instance;
    return &instance;
}

void IOS_Helper::ShowAlert(const char* str)
{   
    [IOS_Native ShowAlert:CharToNs(str)];
}

const char* IOS_Helper::GetApnsDeviceKey()
{
    return NsToChar([IOS_Native GetApnsDeviceKey]);
}
