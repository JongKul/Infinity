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
#include "Scene_Manager.h"

bool GameScene_Match::init()
{
    CCScene::init();
    
    CCLayer* main = GameLayer_Match_Main::create();
    this->addChild(main);
    
    CCLayer* ui = GameLayer_Match_UI::create();
    this->addChild(ui);
    
    
    return true;
}

void GameScene_Match::ChangeScene()
{
    Scene_Manager::ChangeScene_MainTitle();
}