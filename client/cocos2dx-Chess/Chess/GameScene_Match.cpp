//
//  GameScene_Match.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 13..
//
//

#include "GameScene_Match.h"
#include "Match_Map.h"
#include "Match_User.h"

bool GameScene_Match::init()
{
    CCScene::init();
    
    CCLayer* layer = GameLayer_Match::create();
    this->addChild(layer);
    
    return true;
}

GameLayer_Match::GameLayer_Match()
{
    
}
GameLayer_Match::~GameLayer_Match()
{

}

bool GameLayer_Match::init()
{
    CCLayer::init();

    this->setTouchEnabled(true);
    
    Match_Map* map = Match_Map::create();
    this->addChild(map);
    
    user = Match_User::create();
    this->addChild(user);
    user->Start(map);
    
    this->scheduleUpdate();
    
    return true;
}
void GameLayer_Match::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    //CCDirector::sharedDirector()->end();
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    user->TouchProcess(touch->getLocation());
}
void GameLayer_Match::update(float delta)
{
    //CCDirector::sharedDirector()->replaceScene(GameScene_Match::create());
}