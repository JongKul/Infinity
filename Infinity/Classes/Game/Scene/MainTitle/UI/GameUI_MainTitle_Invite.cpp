//
//  GameUI_MainTitle_Invite.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 6. 4..
//
//

#include "GameUI_MainTitle_Invite.h"
#include "Input_Manager.h"
#include "UI_Utility.h"
#include "UILayer_WaitBlack.h"

bool GameUI_MainTitle_Invite::init()
{
    CCNode::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("back_invite.png");
    back->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(back);
    
    Input_Manager::SharedInstance()->SetInputEnable(false);
    
    picture_Width = 100;
    picture_Height = 120;
    picture_Pos = 65;
    cell_Width = 594.0f;
    cell_Height = 144.0f;
    
    tableView = NULL;
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    
    tableView = CCTableView::create(this, CCSizeMake(594, 740));//344
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(64,1280 - 360 - (740)));//100
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView);
    tableView->reloadData();
    
    for(int i=0; i<friList->count(); ++i)
    {
        Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(i);
        Facebook_Manager::sharedInstance()->GetPicture(fri->fbID, this);
    }
    
    CCMenuItem* setting = CCMenuItemImage::create("b_back2.png", "b_back2.png",
                                                  this,menu_selector(GameUI_MainTitle_Invite::ButtonDelegate_Back));
    setting->setPosition(ccp(605, 1280-310));
    //setting->setScale(1.5f);
    CCMenu* menu = CCMenu::create(setting, NULL);
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
    
    return true;
}

void GameUI_MainTitle_Invite::ButtonDelegate_Invite(CCObject* sender)
{
    CCNode* node = (CCNode*)sender;
    CCLOG("ButtonDelegate_Picture : %d", node->getTag());
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(node->getTag());
    Facebook_Manager::sharedInstance()->Invtie(fri->fbID);
}

void GameUI_MainTitle_Invite::fb_Callback_Picture (CCString* fbID, CCSprite* picture)
{
    CCLOG("fb_Callback_Picture");
    
    if(picture == NULL || tableView == NULL)
    {
        CCLOG("NULL");
        return;
    }
    
    int index = Facebook_Manager::sharedInstance()->Get_FriendListIndex(fbID, false);
    CCLOG("Index : %d", index);
    if(index == -1)return;
    
    AddPicture(tableView->cellAtIndex(index), picture, ccp(0,0), ccp(picture_Pos,(cell_Height - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
}

void GameUI_MainTitle_Invite::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    
}
CCSize GameUI_MainTitle_Invite::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(594,144);
}
CCTableViewCell* GameUI_MainTitle_Invite::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(idx);
    CCTableViewCell *cell = table->cellAtIndex(idx);//table->dequeueCell();
    
    tableView = table;
    float x = picture_Pos;
    
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
        item->setPosition(ccp(x, 24.0f));
        item->setScale(0.6944f);
		item->setAnchorPoint(CCPointZero);
        cell->addChild(item, 5);
        
        UI_Utility::Util_AddLabel(cell, ccp(x + picture_Width + 10.0f, 60.0f + 21.0f), CCPointZero, fri->name->getCString(), 30, ccBLACK);

        CCMenuItemImage* button = CCMenuItemImage::create("b_invite.png", "b_invite.png",this,menu_selector(GameUI_MainTitle_Invite::ButtonDelegate_Invite));
        
        button->setAnchorPoint(ccp(0.0f, 0.5f));
        button->setPosition(ccp(0,0));
        button->setTag(idx);
        button->setScale(1.0f);
        CCMenu* menu = CCMenu::create(button, NULL);
        menu->setPosition(ccp(594.0f - (255 * 1.0f),72.0f));
        cell->addChild(menu);
        
        CCSprite* picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(fri->fbID);
        AddPicture(cell, picture, ccp(0,0), ccp(x,(cell_Height - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
    }
    else
    {
        //CCLog("tableCellAtIndex Not NULL idx : %i, name : %s", idx, fri->name->getCString());
        CCNode *picture = cell->getChildByTag(10);
        if(picture == NULL)
        {
            picture = Facebook_Manager::sharedInstance()->GetPicture_FromCache(fri->fbID);
            AddPicture(cell, (CCSprite*)picture, ccp(0,0), ccp(x,(cell_Height - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
        }
    }
    
    return cell;
}
unsigned int GameUI_MainTitle_Invite::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return Facebook_Manager::sharedInstance()->getFriendList()->count();
}

void GameUI_MainTitle_Invite::ButtonDelegate_Back(CCObject* sender)
{
    Input_Manager::SharedInstance()->SetInputEnable(true);
    Facebook_Manager::sharedInstance()->SetNullDelegate();
    this->getParent()->removeChild(this);
}

void GameUI_MainTitle_Invite::AddPicture(cocos2d::CCNode *parent, cocos2d::CCSprite *picture, cocos2d::CCPoint anchor, cocos2d::CCPoint pos, int tag, float width, float height)
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
    parent->addChild(picture, 10);
}