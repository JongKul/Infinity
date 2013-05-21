//
//  GameScene_Intro.h
//  Infinity
//
//  Created by 정 기호 on 13. 5. 21..
//
//

#ifndef __Infinity__GameScene_Intro__
#define __Infinity__GameScene_Intro__

#include "cocos2d.h"
#include "Facebook_Manager.h"

using namespace cocos2d;

class GameScene_Intro : public CCScene
{
public:
    virtual bool init();
    CREATE_FUNC(GameScene_Intro);
public:
    static void ChangeScene();
};

class GameLayer_Intro : public CCLayer, public Facebook_Callback

{
    
public:
    virtual bool init();
    CREATE_FUNC(GameLayer_Intro);
public:
    virtual void fb_Callback_Login (bool);
    virtual void fb_Callback_Picture (CCString* fbID, CCSprite* picture){}
private:
    void ButtonDelegate_Login(cocos2d::CCObject *sender);
};

#endif /* defined(__Infinity__GameScene_Intro__) */
