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

class IOS_Helper
{
public:
    static IOS_Helper* sharedInstance();
public:
    void ShowAlert(const char* str);
    void FacebookLogin();
};

#endif /* defined(__Chess__IOS_Helper__) */
