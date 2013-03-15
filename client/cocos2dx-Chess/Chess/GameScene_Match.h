//
//  GameScene_Match.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 13..
//
//

#ifndef __Chess__GameScene_Match__
#define __Chess__GameScene_Match__

#include "cocos2d.h"

using namespace cocos2d;
class Unit_Base;
class Match_User;

class GameScene_Match : public CCScene
{
public:
    CREATE_FUNC(GameScene_Match);
    virtual bool init();
};

class GameLayer_Match : public CCLayer
{
public:
    CREATE_FUNC(GameLayer_Match);
    virtual bool init();
    virtual void update(float delta);
public:
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
public:
    GameLayer_Match();
    ~GameLayer_Match();
private:
    Match_User* user;
};

#endif /* defined(__Chess__GameScene_Match__) */
