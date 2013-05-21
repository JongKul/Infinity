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

class GameScene_Match;

class GameLayer_Match_UI : public CCLayer
{
public:
    CREATE_FUNC(GameLayer_Match_UI);
    virtual bool init();
private:
    void ButtonDelegate_ChangeScene(CCObject* sender);
    CCSprite* AddSprite(const cocos2d::CCPoint &pos);
private:
    CCSprite *bCount1, *bCount2;
    CCSprite *wCount1, *wCount2;
    
public:
    void UpdateUnitCount();
public:
    GameScene_Match* matchScene;
};

#endif /* defined(__Infinity__GameLayer_Match_UI__) */
