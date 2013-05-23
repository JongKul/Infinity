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
#include "Facebook_Manager.h"
using namespace cocos2d;

class GameScene_Match;

class GameLayer_Match_UI : public CCLayer, public Facebook_Callback
{
public:
    CREATE_FUNC(GameLayer_Match_UI);
    virtual bool init();
private:
    void ButtonDelegate_ChangeScene(CCObject* sender);
    CCSprite* AddSprite(const cocos2d::CCPoint &pos);
    void AddPicture(CCNode *parent, cocos2d::CCSprite *picture, cocos2d::CCPoint anchor, cocos2d::CCPoint pos, int tag, float width, float height);
private:
    CCSprite *bCount1, *bCount2;
    CCSprite *wCount1, *wCount2;
    
public:
    void UpdateUnitCount();
    virtual void fb_Callback_Picture (CCString* fbID, CCSprite* picture);
public:
    GameScene_Match* matchScene;
};

#endif /* defined(__Infinity__GameLayer_Match_UI__) */
