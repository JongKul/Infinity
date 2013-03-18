//
//  Unit_Knight.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Knight.h"
#include "Match_Map.h"

Unit_Knight::Unit_Knight():Unit_Base()
{
    
}

Unit_Knight::~Unit_Knight()
{
   
}

bool Unit_Knight::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_ndt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(scal_X);
    sprite->setScaleY(scal_Y);
    
    return true;
}

void Unit_Knight::SetSelected(Match_Map* curMap)
{
    Unit_Base::SetSelected(curMap);
    
    curMap->SetEnable_MoveTile(curMapIndex, -2, 1);
    curMap->SetEnable_MoveTile(curMapIndex, -1, 2);
    curMap->SetEnable_MoveTile(curMapIndex, 1, 2);
    curMap->SetEnable_MoveTile(curMapIndex, 2, 1);
    curMap->SetEnable_MoveTile(curMapIndex, 2, -1);
    curMap->SetEnable_MoveTile(curMapIndex, 1, -2);
    curMap->SetEnable_MoveTile(curMapIndex, -1, -2);
    curMap->SetEnable_MoveTile(curMapIndex, -2, -1);
}

void Unit_Knight::Real_TouchMove(const CCPoint& movePos)
{
    CCFiniteTimeAction* move = CCMoveTo::create(1.0f, movePos);
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(Unit_Knight::Delegate_FinishMove));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    sprite->runAction(action);
}