//
//  GameLayer_Match_UI.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#ifndef __Infinity__GameLayer_Match_UI__
#define __Infinity__GameLayer_Match_UI__

#include "cocos2d.h"
using namespace cocos2d;

class GameLayer_Match_UI : public CCLayer
{
public:
    CREATE_FUNC(GameLayer_Match_UI);
    virtual bool init();
private:
    void ButtonDelegate_ChangeScene(CCObject* sender);
};

#endif /* defined(__Infinity__GameLayer_Match_UI__) */
