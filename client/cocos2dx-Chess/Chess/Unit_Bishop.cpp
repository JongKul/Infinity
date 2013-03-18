//
//  Unit_Bishop.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Bishop.h"
#include "Match_Map.h"

Unit_Bishop::Unit_Bishop():Unit_Base()
{
    
}

Unit_Bishop::~Unit_Bishop()
{
   
}

bool Unit_Bishop::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_bdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(scal_X);
    sprite->setScaleY(scal_Y);
    
    return true;
}

void Unit_Bishop::SetSelected(Match_Map* curMap)
{
    Unit_Base::SetSelected(curMap);
    
    int width = curMap->GetTileCount_Width();
    
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, -1-i, 1+i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 1+i, 1+i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 1+i, -1-i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, -1-i, -1-i);
}

void Unit_Bishop::Real_TouchMove(const CCPoint& movePos)
{
    CCFiniteTimeAction* move = CCMoveTo::create(1.0f, movePos);
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(Unit_Bishop::Delegate_FinishMove));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    sprite->runAction(action);
}