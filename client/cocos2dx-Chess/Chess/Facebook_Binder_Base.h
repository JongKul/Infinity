//
//  Facebook_Binder_Base.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 21..
//
//

#ifndef __Chess__Facebook_Binder_Base__
#define __Chess__Facebook_Binder_Base__

#include "cocos2d.h"

class Facebook_Binder_Base
{
public:
    Facebook_Binder_Base(){}
    virtual ~Facebook_Binder_Base(){}
    virtual void Login() = 0;
    virtual void GetPicture(cocos2d::CCString *fbID) = 0;
    virtual void Post() = 0;
};

#endif /* defined(__Chess__Facebook_Binder_Base__) */
