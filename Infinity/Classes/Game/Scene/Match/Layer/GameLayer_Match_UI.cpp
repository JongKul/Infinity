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
    
    bCount1 = AddSprite(ccp(600, 1280 - 1180));
    bCount2 = AddSprite(ccp(660, 1280 - 1180));
    
    wCount1 = AddSprite(ccp(600, 1280 - 203));
    wCount2 = AddSprite(ccp(660, 1280 - 203));
    
    Room_List* room = Room_Manager::sharedInstance()->curMatchRoom;
    CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
    if(room->white->isEqual(myAccount) == false)
    {
        CCLabelTTF *white = CCLabelTTF::create(room->other_user_Name->getCString(), "Helvetica", 30.0);
        white->setPosition(ccp(220.0f, 1280.0f - 183.0f));
        white->setAnchorPoint(ccp(0.0f,0.5f));
        white->setColor(ccBLACK);
        this->addChild(white);
        
        CCLabelTTF *black = CCLabelTTF::create(Facebook_Manager::sharedInstance()->getMyAccount()->name->getCString(), "Helvetica", 30.0);
        black->setPosition(ccp(220.0f, 1280.0f - 1165.0f));
        black->setAnchorPoint(ccp(0.0f,0.5f));
        black->setColor(ccBLACK);
        this->addChild(black);
    }
    else
    {
        CCLabelTTF *white = CCLabelTTF::create(Facebook_Manager::sharedInstance()->getMyAccount()->name->getCString(), "Helvetica", 30.0);
        white->setPosition(ccp(220.0f, 1280.0f - 183.0f));
        white->setAnchorPoint(ccp(0.0f,0.5f));
        white->setColor(ccBLACK);
        this->addChild(white);
        
        CCLabelTTF *black = CCLabelTTF::create(room->other_user_Name->getCString(), "Helvetica", 30.0);
        black->setPosition(ccp(220.0f, 1280.0f - 1165.0f));
        black->setAnchorPoint(ccp(0.0f,0.5f));
        black->setColor(ccBLACK);
        this->addChild(black);
    }
    
    Facebook_Manager::sharedInstance()->GetPicture(room->white, this);
    Facebook_Manager::sharedInstance()->GetPicture(room->black, this);
    
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

void GameLayer_Match_UI::UpdateTurnNoti()
{
    if(whiteTurnNoti == NULL)
    {
        whiteTurnNoti = CCSprite::create();
        this->addChild(whiteTurnNoti);
    }
    if(blackTurnNoti == NULL)
    {
        blackTurnNoti = CCSprite::create();
        this->addChild(blackTurnNoti);
    }
    
    Room_List* room = Room_Manager::sharedInstance()->curMatchRoom;
    if(room->cutTurnID->isEqual(room->white) == true)
    {
        whiteTurnNoti->initWithFile("turn.png");
        blackTurnNoti->initWithFile("wait.png");
    }
    else
    {
        whiteTurnNoti->initWithFile("wait.png");
        blackTurnNoti->initWithFile("turn.png");
    }
    
    whiteTurnNoti->setPosition(ccp(360, 1280 - 65));
    blackTurnNoti->setPosition(ccp(360, 1280 - 1045));
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

void GameLayer_Match_UI::fb_Callback_Picture (CCString* fbID, CCSprite* picture)
{
    if(fbID == NULL || picture == NULL)
    {
        CCLOG("fb_Callback_Picture NULL!!!");
        return;
    }
    
    Room_List* room = Room_Manager::sharedInstance()->curMatchRoom;
    CCPoint pos;
    if(room->white->isEqual(fbID) == true) pos = ccp(131, 1280-185);
    else pos = ccp(130, 1280 - 1165);
    
    AddPicture(this, picture, ccp(0.5, 0.5), pos, 10, 160, 160);
}

void GameLayer_Match_UI::AddPicture(CCNode *parent, CCSprite *picture, CCPoint anchor, CCPoint pos, int tag, float width, float height)
{
    if(parent == NULL || picture == NULL)
    {
        //CCLog("AddPicture NULL");
        return;
    }
    
    //CCLOG("Picture tag : %d", tag);
    
    CCSize size = picture->getContentSize();
    float scale_X = width/ size.width;
    float scale_Y = height/ size.height;
    picture->setAnchorPoint(anchor);
    picture->setPosition(pos);
    picture->setScaleX(scale_X); picture->setScaleY(scale_Y);
    picture->setTag(tag);
    parent->addChild(picture);
}