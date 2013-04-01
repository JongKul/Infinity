//
//  GameLayer_Match_Main.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#ifndef __Infinity__GameLayer_Match_Main__
#define __Infinity__GameLayer_Match_Main__

#include "cocos2d.h"
using namespace cocos2d;

class Match_Map;

class GameLayer_Match_Main : public CCLayer
{
public:
    CREATE_FUNC(GameLayer_Match_Main);
    virtual bool init();
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
private:
    Match_Map* cur_Map;
    int curTurn;
};

#endif /* defined(__Infinity__GameLayer_Match_Main__) */
