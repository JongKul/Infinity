//
//  Match_User.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 15..
//
//

#include "Match_User.h"
#include "Match_Map.h"
#include "Unit_Bishop.h"
#include "Unit_Pawn.h"
#include "Unit_Knight.h"
#include "Unit_Rook.h"
#include "Unit_Queen.h"
#include "Unit_King.h"

bool Match_User::init()
{
    curMap = NULL;
    TouchDelegate = NULL;
    curSelectedUnit = NULL;
    
    return true;
}

Match_User::~Match_User()
{
    list_Unit.clear();
}

void Match_User::Start(Match_Map *map)
{
    curMap = map;
    
    //rook, knight, bishop, queen, king, bishop, knight, rook
    list_Unit.push_back(Unit_Rook::create());
    list_Unit.push_back(Unit_Knight::create());
    list_Unit.push_back(Unit_Bishop::create());
    list_Unit.push_back(Unit_Queen::create());
    list_Unit.push_back(Unit_King::create());
    list_Unit.push_back(Unit_Bishop::create());
    list_Unit.push_back(Unit_Knight::create());
    list_Unit.push_back(Unit_Rook::create());
    
    for(int i=0; i<list_Unit.size(); ++i)
    {
        list_Unit[i]->SetParent(this);
        list_Unit[i]->setPosition(curMap->GetPosition_FromIndex(i, 0));
        list_Unit[i]->SetUser(this);
    }
    
    for(int i=0; i<8; ++i)
    {
        Unit_Base* unit_Pawn = Unit_Pawn::create();
        unit_Pawn->SetParent(this);
        unit_Pawn->setPosition(curMap->GetPosition_FromIndex(i, 1));
        unit_Pawn->SetUser(this);
        list_Unit.push_back(unit_Pawn);
    }
    
    TouchDelegate = &Match_User::TouchDelegate_WaitUnitSelect;
}

void Match_User::TouchProcess(cocos2d::CCPoint touchPos)
{
    if(TouchDelegate != NULL)(this->*TouchDelegate)(touchPos);
}

void Match_User::TouchDelegate_WaitUnitSelect(const cocos2d::CCPoint &touchPos)
{
    for(int i=0; i<list_Unit.size(); ++i)
    {
        if(list_Unit[i]->boundingBox().containsPoint(touchPos) == true)
        {
            CCLog("TouchProcess");
            curSelectedUnit = list_Unit[i];
            curSelectedUnit->SetSelected();
            TouchDelegate = &Match_User::TouchDelegate_WaitMoveSelect;
            break;
        }
    }
}

void Match_User::TouchDelegate_WaitMoveSelect(const cocos2d::CCPoint &touchPos)
{
    CCLog("TouchDelegate_WaitMoveSelect");
    if(curSelectedUnit->Process_TouchMove(curMap, touchPos) == true)
    {
        TouchDelegate = NULL;
        curSelectedUnit = NULL;
    }
}

void Match_User::UnitMiveFinish(Unit_Base *unit)
{
    TouchDelegate = &Match_User::TouchDelegate_WaitUnitSelect;
}