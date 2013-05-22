//
//  GameLayer_Match_UI.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "GameLayer_Match_UI.h"
#include "GameScene_Match.h"
#include "Input_Manager.h"
#include "Match_Map.h"
#include "Room_Manager.h"
#include "Facebook_Manager.h"

bool GameLayer_Match_UI::init()
{
    CCLayer::init();
    
    bCount1 = AddSprite(ccp(600, 1280 - 1145));
    bCount2 = AddSprite(ccp(660, 1280 - 1145));
    
    wCount1 = AddSprite(ccp(600, 1280 - 155));
    wCount2 = AddSprite(ccp(660, 1280 - 155));
    
    Room_List* room = Room_Manager::sharedInstance()->curMatchRoom;
    CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
    if(room->white->isEqual(myAccount) == false)
    {
        CCLabelTTF *white = CCLabelTTF::create(room->other_user_Name->getCString(), "Helvetica", 30.0);
        white->setPosition(ccp(250.0f, 1280.0f - 150.0f));
        white->setAnchorPoint(ccp(0.0f,0.5f));
        white->setColor(ccBLACK);
        this->addChild(white);
        
        CCLabelTTF *black = CCLabelTTF::create(Facebook_Manager::sharedInstance()->getMyAccount()->name->getCString(), "Helvetica", 30.0);
        black->setPosition(ccp(250.0f, 200.0f));
        black->setAnchorPoint(ccp(0.0f,0.5f));
        black->setColor(ccBLACK);
        this->addChild(black);
    }
    else
    {
        CCLabelTTF *white = CCLabelTTF::create(Facebook_Manager::sharedInstance()->getMyAccount()->name->getCString(), "Helvetica", 30.0);
        white->setPosition(ccp(250.0f, 1280.0f - 150.0f));
        white->setAnchorPoint(ccp(0.0f,0.5f));
        white->setColor(ccBLACK);
        this->addChild(white);
        
        CCLabelTTF *black = CCLabelTTF::create(room->other_user_Name->getCString(), "Helvetica", 30.0);
        black->setPosition(ccp(250.0f, 150.0f));
        black->setAnchorPoint(ccp(0.0f,0.5f));
        black->setColor(ccBLACK);
        this->addChild(black);
    }
    
    
    
    /*
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage* changeScene_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,menu_selector(GameLayer_Match_UI::ButtonDelegate_ChangeScene));
    changeScene_Button->setPosition(ccp(0,0));
    CCMenu* menu = CCMenu::create(changeScene_Button, NULL);
    menu->setPosition(ccp(winSize.width * 0.8f, winSize.height * 0.9f));
    this->addChild(menu);
    */
    
    return true;
}

CCSprite* GameLayer_Match_UI::AddSprite(const cocos2d::CCPoint &pos)
{
    CCSprite* sprite = CCSprite::create();
    sprite->setPosition(pos);
    this->addChild(sprite);
    
    return sprite;
}

void GameLayer_Match_UI::ButtonDelegate_ChangeScene(cocos2d::CCObject *sender)
{
    ReturnInput();
    
    GameScene_Match::ChangeScene();
}

void GameLayer_Match_UI::UpdateUnitCount()
{
    Match_Map* map = matchScene->GetMatchMap();
    if(map == NULL) return;
    
    int whiteCount = map->GetUnitCount_White();
    int blackCount = map->GetUnitCount_Black();
    
    //CCLOG("white : %d, black : %d", whiteCount, blackCount);

    char fileName[256];
    
    if(whiteCount >= 10)
    {
        int count1 = whiteCount / 10;
        int count2 = whiteCount % (count1 * 10);
        
        sprintf(fileName, "w%d.png", count1);
        wCount1->initWithFile(fileName);
        
        sprintf(fileName, "w%d.png", count2);
        wCount2->initWithFile(fileName);
    }
    else
    {
        sprintf(fileName, "w%d.png", whiteCount);
        wCount1->initWithFile(fileName);
        
        wCount2->init();
    }
    
    if(blackCount >= 10)
    {
        int count1 = blackCount / 10;
        int count2 = blackCount % (count1 * 10);
        
        sprintf(fileName, "b%d.png", count1);
        bCount1->initWithFile(fileName);
        
        sprintf(fileName, "b%d.png", count2);
        bCount2->initWithFile(fileName);
    }
    else
    {
        sprintf(fileName, "b%d.png", blackCount);
        bCount1->initWithFile(fileName);
        
        bCount2->init();
    }
}