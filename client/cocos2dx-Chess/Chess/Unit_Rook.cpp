//
//  Unit_Rook.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Rook.h"
#include "Match_Map.h"

Unit_Rook::Unit_Rook():Unit_Base()
{
    
}

Unit_Rook::~Unit_Rook()
{
    
}

bool Unit_Rook::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_rdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(scal_X);
    sprite->setScaleY(scal_Y);
    
    return true;
}

void Unit_Rook::SetSelected(Match_Map* curMap)
{
    Unit_Base::SetSelected(curMap);
    
    int width = curMap->GetTileCount_Width();
    
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 0, 1+i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 1+i, 0);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 0, -1-i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, -1-i, 0);
}

void Unit_Rook::Real_TouchMove(const CCPoint& movePos)
{
    CCFiniteTimeAction* move = CCMoveTo::create(1.0f, movePos);
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(Unit_Rook::Delegate_FinishMove));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    sprite->runAction(action);
}