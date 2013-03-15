 //
//  Unit_Base.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Base.h"
#include "Match_Map.h"
#include "Match_User.h"

Unit_Base::Unit_Base()
{

}

Unit_Base::~Unit_Base()
{

}

bool Unit_Base::init()
{
    sprite = NULL;
    return true;
}

bool Unit_Base::Process_TouchMove(Match_Map *curMap, const cocos2d::CCPoint &touchPos)
{
    CCPoint pos;
    if(curMap->GetPosition_FromTouch(touchPos, &pos) == true)
    {
        sprite->setColor(ccc3(255, 255, 255));
        
        CCFiniteTimeAction* move = CCMoveTo::create(3.0f, pos);
        CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(Unit_Base::Delegate_FinishMove));
        CCAction* action = CCSequence::create(move, callBack, NULL);
        sprite->runAction(action);
        
        return true;
    }
    
    return false;
}

void Unit_Base::Delegate_FinishMove(cocos2d::CCNode *node)
{
    user->UnitMiveFinish(this);
}

void Unit_Base::SetUser(Match_User *user)
{
    this->user = user;
}

void Unit_Base::SetParent(CCNode* parent)
{
    if(parent != NULL && sprite != NULL)
    {
        parent->addChild(this);
        this->addChild(sprite);
    }
}

void Unit_Base::SetSelected()
{
    if(sprite == NULL) return;
    
    CCLog("SetSElected");
    sprite->setColor(ccc3(0, 255, 0));
}

void Unit_Base::setPosition(const cocos2d::CCPoint &var)
{
    if(sprite != NULL)
    {
        sprite->setPosition(var);
    }
}

CCRect Unit_Base::boundingBox()
{
    return sprite->boundingBox();
}