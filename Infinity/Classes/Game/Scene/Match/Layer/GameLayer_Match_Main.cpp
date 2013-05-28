//
//  GameLayer_Match_Main.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "GameLayer_Match_Main.h"
#include "GameScene_Match.h"
#include "Match_Map.h"
#include "Unit_Black.h"
#include "Unit_White.h"
#include "Othello_Logic.h"
#include "Input_Manager.h"
#include "Facebook_Manager.h"
#include "Room_Manager.h"
#include "UILayer_WaitBlack.h"

bool GameLayer_Match_Main::init()
{
    CCLayer::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* bg = CCSprite::create("back_4.png");
    
    bg->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(bg);
    
    cur_Map = Match_Map::create();
    this->addChild(cur_Map);
    
    setTouchEnabled(true);
  
    CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
    if(Room_Manager::sharedInstance()->curMatchRoom->white->isEqual(myAccount) == true)
    {
        myTurnTag = 1;
    }
    else
    {
        myTurnTag = 0;
    }
    
    isRequestRoomUpdate = false;
    this->schedule(schedule_selector(GameLayer_Match_Main::Schedule_RoomUpdate), 3.0f);
    
    return  true;
}

void GameLayer_Match_Main::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    ReturnInput();
    if(Room_Manager::sharedInstance()->curMatchRoom->finishFlag == 1) return;
    if(isRequestRoomUpdate == true) return;
    
    CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
    if(Room_Manager::sharedInstance()->curMatchRoom->cutTurnID->isEqual(myAccount) == false)
    {
        CCLOG("No My Turn");
        return;
    }
    
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint touch_Pos = touch->getLocation();
    
    //CCLOG("Touch Pos x : %f, y : %f", touch_Pos.x, touch_Pos.y);
    
    int x,y;
    if(Othello_Logic::Logic_AddUnit(cur_Map, touch_Pos, x, y, myTurnTag) == true)
    {
        //matchScene->UpdateUI_GameInfo();
        
        y = (cur_Map->GetTileCount_Height()-1) - y;
        
        Room_Manager::sharedInstance()->Request_RoomTurn(Room_Manager::sharedInstance()->curMatchRoom->room_Index, x, y, this);
        UILayer_WaitBlack::AddLayer();
        
        //if(myTurnTag == 0) myTurnTag = 1;
        //else myTurnTag = 0;
    }
}

void GameLayer_Match_Main::Schedule_RoomUpdate(float time)
{
    CCLOG("Schedule_RoomUpdate");
    if(Room_Manager::sharedInstance()->curMatchRoom->finishFlag == 1) return;
    
    if(isRequestRoomUpdate == true)
    {
        CCLOG("isRequestRoomUpdate = true");
        return;
    }
    
    CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
    if(Room_Manager::sharedInstance()->curMatchRoom->cutTurnID->isEqual(myAccount) == true)
    {
        CCLOG("Cur My Turn");
        return;
    }
    
    isRequestRoomUpdate = true;
    
    prevCurnID = CCString::create(Room_Manager::sharedInstance()->curMatchRoom->cutTurnID->m_sString);
    prevCurnID->retain();
    
    Room_Manager::sharedInstance()->Request_RoomUpdate(this);
    
    //UILayer_WaitBlack::AddLayer();
}

void GameLayer_Match_Main::Callback_RoomTurn(bool ret)
{
    UILayer_WaitBlack::RemoveLayer();
    matchScene->UpdateUI_GameInfo();
}

void GameLayer_Match_Main::Callback_RoomUpdate()
{
    isRequestRoomUpdate = false;
    
    //UILayer_WaitBlack::RemoveLayer();
    
    if(prevCurnID->isEqual(Room_Manager::sharedInstance()->curMatchRoom->cutTurnID) == false)
    {
        CCLOG("Update");
        
        cur_Map->Update_MapData();
        matchScene->UpdateUI_GameInfo();
    }
    else
    {
        CCLOG("No Update");
    }
}

Match_Map* GameLayer_Match_Main::GetMatchMap()
{
    return cur_Map;
}