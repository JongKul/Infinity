//
//  GameScene_MainTitle.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "GameScene_Match.h"
#include "GameLayer_Match_Main.h"
#include "GameLayer_Match_UI.h"
#include "Match_Map.h"
#include "Scene_Manager.h"

bool GameScene_Match::init()
{
    CCScene::init();
    
    mainLayer = GameLayer_Match_Main::create();
    this->addChild(mainLayer);
    
    uiLayer = GameLayer_Match_UI::create();
    this->addChild(uiLayer);
    
    mainLayer->matchScene = uiLayer->matchScene = this;
    
    UpdateUI_GameInfo();
    
    return true;
}

void GameScene_Match::ChangeScene()
{
    Scene_Manager::ChangeScene_MainTitle();
}

void GameScene_Match::UpdateUI_GameInfo()
{
    uiLayer->UpdateUnitCount();
    uiLayer->UpdateTurnNoti();
}

Match_Map* GameScene_Match::GetMatchMap()
{
    return mainLayer->GetMatchMap();
}