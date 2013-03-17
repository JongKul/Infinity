//
//  Unit_Pawn.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Pawn.h"
#include "Match_Map.h"

Unit_Pawn::Unit_Pawn():Unit_Base()
{
    isFirstMove = true;
}

Unit_Pawn::~Unit_Pawn()
{
    
}

bool Unit_Pawn::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_plt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(scal_X);
    sprite->setScaleY(scal_Y);
    
    return true;
}

void Unit_Pawn::SetSelected(Match_Map* curMap)
{
    Unit_Base::SetSelected(curMap);
    
    curMap->SetEnable_MoveTile(curMapIndex, 0, 1);
    if(isFirstMove == true)curMap->SetEnable_MoveTile(curMapIndex, 0, 2);
}

void Unit_Pawn::Real_TouchMove(const CCPoint& movePos)
{
    isFirstMove = false;
    
    CCFiniteTimeAction* move = CCMoveTo::create(1.0f, movePos);
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(Unit_Pawn::Delegate_FinishMove));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    sprite->runAction(action);
}