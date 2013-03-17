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
    scal_X = 0.3f;
    scal_Y = 0.2f;
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
    int index;
    
    sprite->setColor(ccc3(255, 255, 255));
    
    if(curMap->GetMovePosition_FromTouch(touchPos, &pos, &index) == true)
    {
        curMap->MoveToUnit(curMapIndex, index);
        Real_TouchMove(pos);
        curMap->SetDisable_MoveTileAll();
        return true;
    }
    else
    {
        curMap->SetDisable_MoveTileAll();
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

void Unit_Base::SetSelected(Match_Map* curMap)
{
    if(sprite == NULL) return;
    
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