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
#include "WebCommunication.h"

bool GameUI_MainTitle_RoomList::init()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("playing2.png");
    back->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(back);
    
    picture_Width = 100;
    picture_Height = 120;
    picture_Pos = 30;
    
    return true;
}
                                
void GameUI_MainTitle_RoomList::AddTableView_MyTurn()
{
    if(tableView_MyTurn != NULL) return;
    
    curMakeTable = 0;
    
    CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
    
    for(int i=0; i<Room_Manager::sharedInstance()->room_List.size(); ++i)
    {
        Room_List* room = (Room_List*)Room_Manager::sharedInstance()->room_List[i];
        if(room->cutTurnID->isEqual(myAccount) == true)
        {
            list_MyTurn.push_back(room);
        }
    }
    
    if(list_MyTurn.size() <= 0)
    {
        CCLOG("list_MyTurn size : 0");
        tableView_MyTurn = NULL;
        return;
    }
    else CCLOG("list_MyTurn size : %d", list_MyTurn.size());
    
    tableView_MyTurn = CCTableView::create(this, CCSizeMake(594, 295)); //295
    tableView_MyTurn->setDirection(kCCScrollViewDirectionVertical);
    tableView_MyTurn->setPosition(ccp(62,1280 - 300 - (295))); //300
    tableView_MyTurn->setDelegate(this);
    tableView_MyTurn->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView_MyTurn);
    tableView_MyTurn->reloadData();
    tableView_MyTurn->retain();
}

void GameUI_MainTitle_RoomList::AddTableView_Waiting()
{
    if(tableView_Waiting != NULL) return;
    
    curMakeTable = 1;
    
    CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
    
    for(int i=0; i<Room_Manager::sharedInstance()->room_List.size(); ++i)
    {
        Room_List* room = (Room_List*)Room_Manager::sharedInstance()->room_List[i];
        if(room->cutTurnID->isEqual(myAccount) == false)
        {
            list_Waiting.push_back(room);
        }
    }
    
    if(list_Waiting.size() <= 0)
    {
        CCLOG("list_Waiting size : 0");
        tableView_Waiting = NULL;
        return;
    }
    else CCLOG("list_Waiting size : %d", list_Waiting.size());
    
    tableView_Waiting = CCTableView::create(this, CCSizeMake(594, 320)); //320
    tableView_Waiting->setDirection(kCCScrollViewDirectionVertical);
    tableView_Waiting->setPosition(ccp(62,1280 - 700 - (320))); // 700
    tableView_Waiting->setDelegate(this);
    tableView_Waiting->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView_Waiting);
    tableView_Waiting->reloadData();
    tableView_Waiting->retain();
}

void GameUI_MainTitle_RoomList::ButtonDelegate_Picture(cocos2d::CCObject *sender)
{
    ReturnInput();
    CCNode* node = (CCNode*)sender;
    CCLOG("ButtonDelegate_Picture : %d", node->getTag());
    Room_Manager::sharedInstance()->Request_RoomInfo(node->getTag(), this);
    UILayer_WaitBlack::AddLayer();
}

void GameUI_MainTitle_RoomList::Callback_RoomInfo(int roomIndex)
{
    CCLOG("Callback_RoomInfo : %d", roomIndex);
    UILayer_WaitBlack::RemoveLayer();
    
    if(roomIndex < 0)return;
    
    if(Room_Manager::sharedInstance()->SetMatchRoom(roomIndex) == true)
    {
        GameScene_MainTitle::ChangeScene();
    }
}

void GameUI_MainTitle_RoomList::fb_Callback_Picture(cocos2d::CCString *fbID, cocos2d::CCSprite *picture)
{
    if(picture == NULL || tableView_MyTurn == NULL || tableView_Waiting == NULL)
    {
        CCLOG("NULL");
        return;
    }
    
    for(int i = 0; i < list_MyTurn.size(); ++i)
    {
        if(list_MyTurn[i] != NULL)
        {
           CCString* frID = list_MyTurn[i]->other_user_ID;
            if(frID != NULL && frID->isEqual(fbID) == true)
            {
                AddPicture(tableView_MyTurn->cellAtIndex(i), picture, ccp(0,0), ccp(picture_Pos, (144.0f - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
                return;
            }
        }
    }
    
    for(int i = 0; i < list_Waiting.size(); ++i)
    {
        if(list_Waiting[i] != NULL)
        {
            CCString* frID = list_Waiting[i]->other_user_ID;
            if(frID != NULL && frID->isEqual(fbID) == true)
            {
                AddPicture(tableView_Waiting->cellAtIndex(i), picture, ccp(0,0), ccp(picture_Pos, (144.0f - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
                return;
            }
        }
    }
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
    Room_List* room = NULL;
    if(tableView_MyTurn == table || curMakeTable == 0)
    {
        room = list_MyTurn[idx];
    }
    else if(tableView_Waiting == table || curMakeTable == 1)
    {
        room = list_Waiting[idx];
    }
    else CCLOG("table = NULL");
    
    if(room == NULL)
    {
        CCLOG("room = NULL!!");
        return NULL;
    }

    CCTableViewCell *cell = table->cellAtIndex(idx);//table->dequeueCell();
    
    if (cell == NULL)
    {
        //CCLog("tableCellAtIndex NULL idx : %d, name : %s", idx, fri->name->getCString());
        
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSprite* back;
        if(idx % 2 == 0) back = CCSprite::create("row.png");
        else back = CCSprite::create("myrank.png");
        
        back->setPosition(CCPointZero);
		back->setAnchorPoint(CCPointZero);
        cell->addChild(back);
        
        CCSprite* item = CCSprite::create("Icon-144.png");
        item->setPosition(ccp(picture_Pos, 24.0f));
        item->setScale(0.6944f);
		item->setAnchorPoint(CCPointZero);
        cell->addChild(item);
        
        CCString* str = CCString::createWithFormat("%s", room->other_user_Name->getCString());
        CCLabelTTF *label = CCLabelTTF::create(str->getCString(), "Helvetica", 30.0);
        label->setPosition(ccp(picture_Pos + picture_Width + 5.0f, 52.0f));
		label->setAnchorPoint(CCPointZero);
        label->setColor(ccBLACK);
        cell->addChild(label);
        
        CCMenuItemImage* button = CCMenuItemImage::create("b_enter.png", "b_enter.png", this,menu_selector(GameUI_MainTitle_RoomList::ButtonDelegate_Picture));
        button->setTag(room->room_Index);
        CCMenu* menu = CCMenu::create(button, NULL);
        menu->setPosition(ccp(594.0f - (255.0f * 0.5f),75));
		menu->setAnchorPoint(CCPointZero);
        cell->addChild(menu);
        
        CCSprite* picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(room->other_user_ID);
        if(picture == NULL)
        {
            Facebook_Manager::sharedInstance()->GetPicture(room->other_user_ID, this);
        }
        else AddPicture(cell, picture, ccp(0,0), ccp(picture_Pos, (144.0f - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
    }
    else
    {
        //CCLog("tableCellAtIndex Not NULL idx : %i, name : %s", idx, fri->name->getCString());
        CCNode *picture = cell->getChildByTag(10);
        if(picture == NULL)
        {
            CCSprite* picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(room->other_user_ID);
            AddPicture(cell, picture, ccp(0,0), ccp(picture_Pos, (144.0f - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
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


void GameUI_MainTitle_RoomList::setVisible(bool visible)
{ 
    if(visible == true)
    {
        UILayer_WaitBlack::AddLayer();
        Facebook_Account* myAccount = Facebook_Manager::sharedInstance()->getMyAccount();
        WebRequest_RoomList(this, callfuncND_selector(GameUI_MainTitle_RoomList::onHttpRequestCompleted_RoomList), "Post RoomList", myAccount->fbID->getCString());
    }
    else
    {
        list_MyTurn.clear();
        list_Waiting.clear();
        
        if(tableView_MyTurn != NULL)
        {
            this->removeChild(tableView_MyTurn);
            tableView_MyTurn = NULL;
        }
        if(tableView_Waiting != NULL)
        {
            this->removeChild(tableView_Waiting);
            tableView_Waiting = NULL;
        }
    }
    
    CCNode::setVisible(visible);
}

void GameUI_MainTitle_RoomList::onHttpRequestCompleted_RoomList(cocos2d::CCNode *sender, void *data)
{
    CCLOG("onHttpRequestCompleted_RoomList!!");
    
    Json::Value root;
    if(WebResponse_Common(sender, data, root) == false)
    {
        CCLOG("onHttpRequestCompleted_RoomList = false!!");
        return;
    }
    
    CCLOG(root.toStyledString().c_str());
    
    Room_Manager::sharedInstance()->Init_RoomList(root);
    
    curMakeTable = 0;
    AddTableView_MyTurn();
    AddTableView_Waiting();
    curMakeTable = -1;
    
    UILayer_WaitBlack::RemoveLayer();
}

unsigned int GameUI_MainTitle_RoomList::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    if(tableView_MyTurn == table || curMakeTable == 0)
    {
        return list_MyTurn.size();
    }
    else if(tableView_Waiting == table || curMakeTable == 1)
    {
        return list_Waiting.size();
    }
    else return 0;
}