//
//  IOS_Helper.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//


#import "IOS_Helper.h"
#import "IOS_Native.h"

IOS_Helper* IOS_Helper::sharedInstance()
{
    static IOS_Helper instance;
    return &instance;
}

void IOS_Helper::ShowAlert(const char* str)
{   
    [IOS_Native ShowAlert:CharToNs(str)];
}

void IOS_Helper::FacebookLogin()
{
    [IOS_Native FacebookLogin];
}