//
//  Unit_Queen.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Queen.h"
#include "Match_Map.h"

Unit_Queen::Unit_Queen():Unit_Base()
{
    
}

Unit_Queen::~Unit_Queen()
{
   
}

bool Unit_Queen::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_qdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(scal_X);
    sprite->setScaleY(scal_Y);
    
    return true;
}

void Unit_Queen::SetSelected(Match_Map* curMap)
{
    Unit_Base::SetSelected(curMap);
    
    int width = curMap->GetTileCount_Width();
    
    //상하좌우.
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 0, 1+i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 1+i, 0);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 0, -1-i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, -1-i, 0);
    
    //대각선.
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, -1-i, 1+i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 1+i, 1+i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, 1+i, -1-i);
    for(int i=0; i<width; ++i) curMap->SetEnable_MoveTile(curMapIndex, -1-i, -1-i);

}

void Unit_Queen::Real_TouchMove(const CCPoint& movePos)
{
    CCFiniteTimeAction* move = CCMoveTo::create(1.0f, movePos);
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(Unit_Queen::Delegate_FinishMove));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    sprite->runAction(action);
}