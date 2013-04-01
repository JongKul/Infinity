//
//  GameUI_MainTitle.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#include "GameUI_MainTitle.h"
#include "GameScene_MainTitle.h"
#include "Native_Helper.h"

bool GameUI_MainTitle::init()
{
    gameLayer = NULL;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("bg.png");
    bg->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(bg);
    
    CCMenuItemImage* start_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,menu_selector(GameUI_MainTitle::ButtonDelegate_Start));
    CCMenuItemImage* post_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,menu_selector(GameUI_MainTitle::ButtonDelegate_Post));
    post_Button->setPosition(ccp(0,100));
    CCMenu* menu = CCMenu::create(start_Button, post_Button, NULL);
    menu->setPosition(ccp(winSize.width * 0.8f, winSize.height * 0.2f));
    this->addChild(menu);
    
    if(Facebook_Manager::sharedInstance()->IsLogin() == true)
    {
        CCLog("IS Login");
        fb_Callback_Login(true);
    }
    
    return true;
}


void GameUI_MainTitle::ButtonDelegate_Start(cocos2d::CCObject *sender)
{
    //IOS_Helper::sharedInstance()->ShowAlert();
    //IOS_Helper::sharedInstance()->FacebookLogin();
    //gameLayer->ChangeScene();
    if(Facebook_Manager::sharedInstance()->IsLogin() == true)
    {
        CCLog("IS Login");
        return;
    }
    Facebook_Manager::sharedInstance()->Login(this);
}

void GameUI_MainTitle::ButtonDelegate_Post(cocos2d::CCObject *sender)
{
    //Facebook_Manager::sharedInstance()->Post();
    GameScene_MainTitle::ChangeScene();
}


void GameUI_MainTitle::fb_Callback_Login(bool ret)
{
    CCLog("fb_Callback_Login");
    
    if(ret == true)
    {
        CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        tableView = CCTableView::create(this, CCSizeMake(344, 144*3));
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setPosition(ccp(50,winSize.height/2-120));
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView);
        tableView->reloadData();
        
        
        for(int i=0; i<friList->count(); ++i)
        {
            Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(i);
            Facebook_Manager::sharedInstance()->GetPicture(fri->fbID, this);
        }
        //CCString* id = CCString::create("100001756203467");
        //Facebook_Manager::sharedInstance()->Invtie(id);
    }
    else
    {
        
    }
}

void GameUI_MainTitle::fb_Callback_Picture(cocos2d::CCString *fbID, cocos2d::CCSprite *picture)
{
    if(picture == NULL || tableView == NULL)
    {
        CCLOG("NULL");
        return;
    }
    
    int index = Facebook_Manager::sharedInstance()->Get_FriendListIndex(fbID);
    if(index == -1)return;
    
    AddPicture(tableView->cellAtIndex(index), picture, ccp(0,0), ccp(0,0), 10, 144.0f, 144.0f);
}


void GameUI_MainTitle::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i, child : %d", cell->getIdx(), cell->getChildrenCount());
}

CCSize GameUI_MainTitle::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(344,144);
}
CCTableViewCell* GameUI_MainTitle::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(idx);
    CCTableViewCell *cell = table->cellAtIndex(idx);//table->dequeueCell();

    tableView = table;
    
    if (!cell)
    {
        //CCLog("tableCellAtIndex NULL idx : %d, name : %s", idx, fri->name->getCString());
        
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSprite* item = CCSprite::create("Icon-144.png");
        item->setPosition(CCPointZero);
		item->setAnchorPoint(CCPointZero);
        cell->addChild(item);

        CCLabelTTF *label = CCLabelTTF::create(fri->name->getCString(), "Helvetica", 30.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label, 10);
        
        CCSprite* picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(fri->fbID);
        AddPicture(cell, picture, ccp(0,0), ccp(0,0), 10, 144.0f, 144.0f);
    }
    else
    {
        //CCLog("tableCellAtIndex Not NULL idx : %i, name : %s", idx, fri->name->getCString());
        CCNode *picture = cell->getChildByTag(10);
        if(picture == NULL)
        {
            picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(fri->fbID);
            AddPicture(cell, (CCSprite*)picture, ccp(0,0), ccp(0,0), 10, 144.0f, 144.0f);
        }
    }
    
    return cell;
}

void GameUI_MainTitle::AddPicture(cocos2d::CCNode *parent, cocos2d::CCSprite *picture, cocos2d::CCPoint anchor, cocos2d::CCPoint pos, int tag, float width, float height)
{
    if(parent == NULL || picture == NULL)
    {
        //CCLog("AddPicture NULL");
        return;
    }
    
    CCSize size = picture->getContentSize();
    float scale_X = width/ size.width;
    float scale_Y = height/ size.height;
    picture->setAnchorPoint(anchor);
    picture->setPosition(pos);
    picture->setScaleX(scale_X); picture->setScaleY(scale_Y);
    picture->setTag(tag);
    parent->addChild(picture);
}

unsigned int GameUI_MainTitle::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return Facebook_Manager::sharedInstance()->getFriendList()->count();
}