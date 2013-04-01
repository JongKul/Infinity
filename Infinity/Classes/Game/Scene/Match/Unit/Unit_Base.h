//
//  Unit_Base.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Unit_Base__
#define __Chess__Unit_Base__

#include "cocos2d.h"

using namespace cocos2d;

class Match_Map;
class Match_User;

class Unit_Base : public CCNode
{
public:
    Unit_Base();
    virtual ~Unit_Base();
    CREATE_FUNC(Unit_Base);
    virtual bool init();
public:
    void SetParent(CCNode* parent);
    virtual void setPosition(const cocos2d::CCPoint &var);
    void SetMapScale(float width, float height);
    CCRect boundingBox(void);
protected:
    CCSprite* sprite;
};

#endif /* defined(__Chess__Unit_Base__) */
