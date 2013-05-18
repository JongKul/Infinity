//
//  GameUI_MainTitle_RoomList.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 5. 18..
//
//

#include "GameUI_MainTitle_RoomList.h"
#include "GameScene_MainTitle.h"
#include "UILayer_WaitBlack.h"
#include "Input_Manager.h"
#include "Room_Manager.h"

bool GameUI_MainTitle_RoomList::init()
{
    gameLayer = NULL;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    tableView = CCTableView::create(this, CCSizeMake(344, 144*3));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(350,winSize.height/2-120));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView);
    tableView->reloadData();
    
    return true;
}

void GameUI_MainTitle_RoomList::ButtonDelegate_Picture(cocos2d::CCObject *sender)
{
    ReturnInput();
    CCNode* node = (CCNode*)sender;
    CCLOG("ButtonDelegate_Picture : %d", node->getTag());
}

void GameUI_MainTitle_RoomList::fb_Callback_Picture(cocos2d::CCString *fbID, cocos2d::CCSprite *picture)
{
    if(picture == NULL || tableView == NULL)
    {
        CCLOG("NULL");
        return;
    }
    
    int index = Facebook_Manager::sharedInstance()->Get_FriendListIndex(fbID, true);
    if(index == -1)return;
    
    AddPicture(tableView->cellAtIndex(index), picture, ccp(0,0), ccp(0,0), 10, 144.0f, 144.0f);
}


void GameUI_MainTitle_RoomList::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i, child : %d", cell->getIdx(), cell->getChildrenCount());
}

CCSize GameUI_MainTitle_RoomList::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(344,144);
}
CCTableViewCell* GameUI_MainTitle_RoomList::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    Room_List* room = (Room_List*)Room_Manager::sharedInstance()->room_List[idx];
    CCTableViewCell *cell = table->cellAtIndex(idx);//table->dequeueCell();
    
    tableView = table;
    
    if (cell == NULL)
    {
        //CCLog("tableCellAtIndex NULL idx : %d, name : %s", idx, fri->name->getCString());
        
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSprite* item = CCSprite::create("Icon-144.png");
        item->setPosition(CCPointZero);
		item->setAnchorPoint(CCPointZero);
        cell->addChild(item);
        
        CCString* str = CCString::createWithFormat("%s", room->other_user_Name->getCString());
        CCLabelTTF *label = CCLabelTTF::create(str->getCString(), "Helvetica", 30.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label, 10);
        
        CCMenuItemImage* button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,menu_selector(GameUI_MainTitle_RoomList::ButtonDelegate_Picture));
        button->setTag(room->room_Index);
        CCMenu* menu = CCMenu::create(button, NULL);
        menu->setPosition(ccp(170,75));
		menu->setAnchorPoint(CCPointZero);
        cell->addChild(menu);
        
        //CCSprite* picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(fri->fbID);
        //AddPicture(cell, picture, ccp(0,0), ccp(0,0), 10, 144.0f, 144.0f);
    }
    else
    {
        //CCLog("tableCellAtIndex Not NULL idx : %i, name : %s", idx, fri->name->getCString());
        CCNode *picture = cell->getChildByTag(10);
        if(picture == NULL)
        {
            //picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(fri->fbID);
            //AddPicture(cell, (CCSprite*)picture, ccp(0,0), ccp(0,0), 10, 144.0f, 144.0f);
        }
    }
    
    return cell;
}

void GameUI_MainTitle_RoomList::AddPicture(cocos2d::CCNode *parent, cocos2d::CCSprite *picture, cocos2d::CCPoint anchor, cocos2d::CCPoint pos, int tag, float width, float height)
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

unsigned int GameUI_MainTitle_RoomList::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return Room_Manager::sharedInstance()->room_List.size();
}