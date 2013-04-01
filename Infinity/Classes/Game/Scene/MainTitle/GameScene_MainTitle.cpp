//
//  GameScene_MainTitle.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#include "GameScene_MainTitle.h"
#include "GameUI_MainTitle.h"
#include "Scene_Manager.h"

#pragma region Scene

bool GameScene_MainTitle::init()
{
    CCScene::init();
    
    CCLayer* layer = GameLayer_MainTitle::create();
    this->addChild(layer);
    
    return true;
}

void GameScene_MainTitle::ChangeScene()
{
    Scene_Manager::ChangeScene_Match();
}

#pragma endregion

#pragma region Layer

bool GameLayer_MainTitle::init()
{
    CCLayer::init();
    
    this->setTouchEnabled(true);
    
    GameUI_MainTitle* ui = GameUI_MainTitle::create();
    ui->SetGameLayer(this);
    this->addChild(ui);
    
    return true;
}

#pragma endregion