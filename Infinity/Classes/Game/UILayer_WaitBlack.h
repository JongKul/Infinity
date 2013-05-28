//
//  UILayer_WaitBlack.h
//  Infinity
//
//  Created by 정 기호 on 13. 5. 18..
//
//

#ifndef __Infinity__UILayer_WaitBlack__
#define __Infinity__UILayer_WaitBlack__

#include "cocos2d.h"

using namespace cocos2d;

class UILayer_WaitBlack : public CCLayer
{
    
public:
    virtual bool init();
    CREATE_FUNC(UILayer_WaitBlack);
public:
    static void AddLayer(bool loading = true);
    static void RemoveLayer();
private:
    static UILayer_WaitBlack* GetLayer();
    void LoadingRotate();
    CCSprite* loading;
};


#endif /* defined(__Infinity__UILayer_WaitBlack__) */
