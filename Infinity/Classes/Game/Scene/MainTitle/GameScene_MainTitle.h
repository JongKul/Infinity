//
//  GameScene_MainTitle.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#ifndef __Chess__GameScene_MainTitle__
#define __Chess__GameScene_MainTitle__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene_MainTitle : public CCScene
{
public:
    virtual bool init();
    CREATE_FUNC(GameScene_MainTitle);
public:
    static void ChangeScene();
};

class GameLayer_MainTitle : public CCLayer
{
  
public:
    virtual bool init();
    CREATE_FUNC(GameLayer_MainTitle);
};

#endif /* defined(__Chess__GameScene_MainTitle__) */
