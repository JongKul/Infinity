//
//  GameUI_MainTitle_Rank.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 5. 21..
//
//

#include "GameUI_MainTitle_Rank.h"
#include "GameScene_MainTitle.h"
#include "Native_Helper.h"
#include "UILayer_WaitBlack.h"
#include "Input_Manager.h"
#include "GameUI_MainTitle_RoomList.h"

bool GameUI_MainTitle_Rank::init()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("home.png");
    bg->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(bg);
    
    /*
    CCMenuItemImage* start_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                                            this,menu_selector(GameUI_MainTitle_Rank::ButtonDelegate_Start));
    start_Button->setNormalImage(CCSprite::create("b_home.png"));
    CCMenuItemImage* change_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                                             this,menu_selector(GameUI_MainTitle_Rank::ButtonDelegate_ChangeScene));
    CCMenuItemImage* post_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                                           this,menu_selector(GameUI_MainTitle_Rank::ButtonDelegate_Post));
    change_Button->setPosition(ccp(0,100));
    post_Button->setPosition(ccp(0,200));
    CCMenu* menu = CCMenu::create(start_Button, change_Button, post_Button, NULL);
    menu->setPosition(ccp(winSize.width * 0.8f, winSize.height * 0.2f));
    this->addChild(menu);
    */
     
    if(Facebook_Manager::sharedInstance()->IsLogin() == true)
    {
        CCLog("IS Login");
        fb_Callback_Login(true);
    }
    
    return true;
}


void GameUI_MainTitle_Rank::ButtonDelegate_Start(cocos2d::CCObject *sender)
{
    ReturnInput();
    //IOS_Helper::sharedInstance()->ShowAlert();
    //IOS_Helper::sharedInstance()->FacebookLogin();
    //gameLayer->ChangeScene();
    if(Facebook_Manager::sharedInstance()->IsLogin() == true)
    {
        CCLog("IS Login");
        return;
    }
    UILayer_WaitBlack::AddLayer();
    Facebook_Manager::sharedInstance()->Login(this);
}

void GameUI_MainTitle_Rank::ButtonDelegate_Post(cocos2d::CCObject *sender)
{
    ReturnInput();
    //Facebook_Manager::sharedInstance()->Post();
    //UILayer_WaitBlack::RemoveLayer();
}

void GameUI_MainTitle_Rank::ButtonDelegate_ChangeScene(cocos2d::CCObject *sender)
{
    ReturnInput();
    GameScene_MainTitle::ChangeScene();
    //UILayer_WaitBlack::AddLayer();
}

void GameUI_MainTitle_Rank::ButtonDelegate_Picture(cocos2d::CCObject *sender)
{
    ReturnInput();
    CCNode* node = (CCNode*)sender;
    CCLOG("ButtonDelegate_Picture : %d", node->getTag());
    CCArray* friList = Facebook_Manager::sharedInstance()->getGameFriendList();
    Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(node->getTag());
    Room_Manager::sharedInstance()->Request_RoomMake(Facebook_Manager::sharedInstance()->getMyAccount()->fbID, fri->fbID, this);
    UILayer_WaitBlack::AddLayer();
    //Facebook_Manager::sharedInstance()->Invtie(fri->fbID);
}

void GameUI_MainTitle_Rank::Callback_RoomMake(int roomIndex)
{
    UILayer_WaitBlack::RemoveLayer();
    
    if(roomIndex < 0)return;
    
    if(Room_Manager::sharedInstance()->SetMatchRoom(roomIndex) == true)
    {
        GameScene_MainTitle::ChangeScene();
    }
}

void GameUI_MainTitle_Rank::fb_Callback_Login(bool ret)
{
    CCLog("fb_Callback_Login");
    
    if(ret == true)
    {
        CCArray* friList = Facebook_Manager::sharedInstance()->getGameFriendList();
        
        //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        tableView = CCTableView::create(this, CCSizeMake(344, 144*3));
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setPosition(ccp(100,1280 - 540 - (144 * 3)));
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView);
        tableView->reloadData();
        
        for(int i=0; i<friList->count(); ++i)
        {
            Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(i);
            Facebook_Manager::sharedInstance()->GetPicture(fri->fbID, this);
        }
    }
    else
    {
        
    }
    
    UILayer_WaitBlack::RemoveLayer();
}

void GameUI_MainTitle_Rank::fb_Callback_Picture(cocos2d::CCString *fbID, cocos2d::CCSprite *picture)
{
    CCLOG("fb_Callback_Picture");
    
    if(picture == NULL || tableView == NULL)
    {
        CCLOG("NULL");
        return;
    }
    
    int index = Facebook_Manager::sharedInstance()->Get_FriendListIndex(fbID, true);
    CCLOG("Index : %d", index);
    if(index == -1)return;
    
    AddPicture(tableView->cellAtIndex(index), picture, ccp(0,0), ccp(0,0), 10, 144.0f, 144.0f);
}


void GameUI_MainTitle_Rank::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i, child : %d", cell->getIdx(), cell->getChildrenCount());
}

CCSize GameUI_MainTitle_Rank::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(344,144);
}
CCTableViewCell* GameUI_MainTitle_Rank::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCArray* friList = Facebook_Manager::sharedInstance()->getGameFriendList();
    Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(idx);
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
        
        CCString* str = CCString::createWithFormat("%s w:%d l:%d", fri->name->getCString(), fri->win, fri->lose);
        CCLabelTTF *label = CCLabelTTF::create(str->getCString(), "Helvetica", 30.0);
        label->setPosition(ccp(144.0f,0.0f));
		label->setAnchorPoint(CCPointZero);
        label->setColor(ccBLACK);
        label->setTag(123);
        cell->addChild(label, 10);
        
        CCMenuItemImage* button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                                          this,menu_selector(GameUI_MainTitle_Rank::ButtonDelegate_Picture));
        button->setTag(idx);
        CCMenu* menu = CCMenu::create(button, NULL);
        menu->setPosition(ccp(170,75));
		menu->setAnchorPoint(CCPointZero);
        cell->addChild(menu);
        
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

void GameUI_MainTitle_Rank::AddPicture(cocos2d::CCNode *parent, cocos2d::CCSprite *picture, cocos2d::CCPoint anchor, cocos2d::CCPoint pos, int tag, float width, float height)
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

unsigned int GameUI_MainTitle_Rank::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return Facebook_Manager::sharedInstance()->getGameFriendList()->count();
}