//
//  GameLayer_Match_Main.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "GameLayer_Match_Main.h"
#include "Match_Map.h"
#include "Unit_Black.h"
#include "Unit_White.h"
#include "Othello_Logic.h"

bool GameLayer_Match_Main::init()
{
    CCLayer::init();
    
    cur_Map = Match_Map::create();
    this->addChild(cur_Map);
    
    setTouchEnabled(true);
    
    Unit_Base* black1 = Unit_Black::create();
    Unit_Base* black2 = Unit_Black::create();
    Unit_Base* white1 = Unit_White::create();
    Unit_Base* white2 = Unit_White::create();
    
    cur_Map->SetUnit_ToMap(black1, 3, 4);
    cur_Map->SetUnit_ToMap(black2, 4, 3);
    cur_Map->SetUnit_ToMap(white1, 4, 4);
    cur_Map->SetUnit_ToMap(white2, 3, 3);
    
    curTurn = 0;
    
    return  true;
}

void GameLayer_Match_Main::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint touch_Pos = touch->getLocation();
    
    //CCLOG("Touch Pos x : %f, y : %f", touch_Pos.x, touch_Pos.y);
    
    if(Othello_Logic::Logic_AddUnit(cur_Map, touch_Pos, curTurn) == true)
    {
        //CCLOG("Success Logic_AddUnit");
        
        if(curTurn == 0) curTurn = 1;
        else curTurn = 0;
    }
    //else CCLOG("Fail Logic_AddUnit");
    
    //CCLOG("curTurn : %d", curTurn);
}