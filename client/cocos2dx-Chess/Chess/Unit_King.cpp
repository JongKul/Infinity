//
//  Unit_King.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 15..
//
//

#include "Unit_King.h"
#include "Match_Map.h"

Unit_King::Unit_King():Unit_Base()
{
    
}

Unit_King::~Unit_King()
{
    
}

bool Unit_King::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_kdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(scal_X);
    sprite->setScaleY(scal_Y);
    
    return true;
}

void Unit_King::SetSelected(Match_Map* curMap)
{
    Unit_Base::SetSelected(curMap);
    
    curMap->SetEnable_MoveTile(curMapIndex, 0, 1);
    curMap->SetEnable_MoveTile(curMapIndex, 1, 1);
    curMap->SetEnable_MoveTile(curMapIndex, 1, 0);
    curMap->SetEnable_MoveTile(curMapIndex, 1, -1);
    curMap->SetEnable_MoveTile(curMapIndex, 0, -1);
    curMap->SetEnable_MoveTile(curMapIndex, -1, -1);
    curMap->SetEnable_MoveTile(curMapIndex, -1, 0);
    curMap->SetEnable_MoveTile(curMapIndex, -1, 1);
}

void Unit_King::Real_TouchMove(const CCPoint& movePos)
{
    CCFiniteTimeAction* move = CCMoveTo::create(1.0f, movePos);
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(Unit_King::Delegate_FinishMove));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    sprite->runAction(action);
}