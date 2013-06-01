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
#include "UI_Utility.h"
#include "Room_Manager.h"

bool GameUI_MainTitle_Rank::init()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("home.png");
    bg->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(bg);
    
    CCMenuItem* randomMatch = CCMenuItemImage::create("random.png", "random.png",
                                                      this,menu_selector(GameUI_MainTitle_Rank::ButtonDelegate_RandomMatch));
    CCMenuItem* invite = CCMenuItemImage::create("invite.png", "invite.png",
                                                 this,menu_selector(GameUI_MainTitle_Rank::ButtonDelegate_Invite));
 
    randomMatch->setPosition(ccp(175, 1280-302));
    invite->setPosition(ccp(550, 1280-310));
  
    CCMenu* menu = CCMenu::create(randomMatch, invite, NULL);
    menu->setPosition(ccp(0,0));
    this->addChild(menu);
    
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
    
    picture_Width = 100;
    picture_Height = 120;
    picture_Pos = 65;
    cell_Width = 594.0f;
    cell_Height = 144.0f;
    
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

void GameUI_MainTitle_Rank::ButtonDelegate_RandomMatch(CCObject* sender)
{
    ReturnInput();
    
    CCLOG("ButtonDelegate_RandomMatch");
}
void GameUI_MainTitle_Rank::ButtonDelegate_Invite(CCObject* sender)
{
    ReturnInput();
    
    CCLOG("ButtonDelegate_Invite");
}

void GameUI_MainTitle_Rank::setVisible(bool visible)
{
    if(visible == true)
    {
        if(Facebook_Manager::sharedInstance()->IsLogin() == true)
        {
            CCLog("IS Login");
            fb_Callback_Login(true);
        }
    }
    else
    {
       if(tableView != NULL)
       {
           this->removeChild(tableView);
           tableView = NULL;
       }
    }
    
    CCNode::setVisible(visible);
}

void GameUI_MainTitle_Rank::fb_Callback_Login(bool ret)
{
    CCLog("fb_Callback_Login");
    
    if(ret == true)
    {
        CCArray* friList = Facebook_Manager::sharedInstance()->getGameFriendList();
        
        //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        tableView = CCTableView::create(this, CCSizeMake(594, 144*3 + 55));//344
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setPosition(ccp(62,1280 - 520 - (144 * 3 + 55)));//100
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
    
    AddPicture(tableView->cellAtIndex(index), picture, ccp(0,0), ccp(picture_Pos,(cell_Height - picture_Height) * 0.5f), 10, picture_Width, picture_Height);
}


void GameUI_MainTitle_Rank::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i, child : %d", cell->getIdx(), cell->getChildrenCount());
}

CCSize GameUI_MainTitle_Rank::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(594,144);
}
CCTableViewCell* GameUI_MainTitle_Rank::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCArray* friList = Facebook_Manager::sharedInstance()->getGameFriendList();
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
        CCString* myAccount = Facebook_Manager::sharedInstance()->getMyAccount()->fbID;
        bool isMe = myAccount->isEqual(fri->fbID);
        if(isMe == true) back = CCSprite::create("myrank2.png");
        else
        {
            if(idx % 2 == 0) back = CCSprite::create("row.png");
            else back = CCSprite::create("myrank.png");
        }
        
        back->setPosition(CCPointZero);
		back->setAnchorPoint(CCPointZero);
        cell->addChild(back);
        
        CCSprite* item = CCSprite::create("Icon-144.png");
        item->setPosition(ccp(x, 24.0f));
        item->setScale(0.6944f);
		item->setAnchorPoint(CCPointZero);
        cell->addChild(item);
        
        CCString* str_Win = CCString::createWithFormat("WIN %03d", fri->win);
        CCString* str_Lose = CCString::createWithFormat("LOSE %03d", fri->lose);

        UI_Utility::Util_AddLabel(cell, ccp(x + picture_Width + 10.0f, 60.0f + 21.0f), CCPointZero, fri->name->getCString(), 30, ccBLACK);
        UI_Utility::Util_AddLabel(cell, ccp(x + picture_Width + 10.0f, 30.0f + 21.0f), CCPointZero, str_Win->getCString(), 30, ccBLACK);
        UI_Utility::Util_AddLabel(cell, ccp(x + picture_Width + 10.0f, 0.0f  + 21.0f), CCPointZero, str_Lose->getCString(), 30, ccBLACK);
        
        char fileName[256];
        
        int rank = idx + 1;
        if(rank >= 10)
        {
            int count1 = rank / 10;
            int count2 = rank % (count1 * 10);
            
            sprintf(fileName, "b%d.png", count1);
            CCSprite* rank1 = CCSprite::create(fileName);
            rank1->setAnchorPoint(ccp(0.5f, 0.0f));
            rank1->setPosition(ccp(x * 0.5f - 65.0f * 0.5f, (144.0f - 80.0f) * 0.5f));
            cell->addChild(rank1);
            
            sprintf(fileName, "b%d.png", count2);
            CCSprite* rank2 = CCSprite::create(fileName);
            rank2->setAnchorPoint(ccp(0.5f, 0.0f));
            rank2->setPosition(ccp(x * 0.5f + 65.0f * 0.5f, (144.0f - 80.0f) * 0.5f));
            cell->addChild(rank2);
        }
        else
        {
            sprintf(fileName, "b%d.png", rank);
            CCSprite* rank1 = CCSprite::create(fileName);
            rank1->setAnchorPoint(ccp(0.5f, 0.0f));
            rank1->setPosition(ccp(x * 0.5f, (144.0f - 80.0f) * 0.5f));
            cell->addChild(rank1);
        }
        
        if(isMe == false)
        {
            bool isPlaying = false;
            for(int i = 0; i<Room_Manager::sharedInstance()->room_List.size(); ++i)
            {
                Room_List* room = Room_Manager::sharedInstance()->room_List[i];
                if(fri->name->isEqual(room->other_user_ID) == true)
                {
                    isPlaying = true;
                    break;
                }
            }
            
            if(isPlaying == true)
            {
                CCMenuItemImage* button = CCMenuItemImage::create("b_start.png", "b_start.png",this,menu_selector(GameUI_MainTitle_Rank::ButtonDelegate_Picture));
                
                button->setAnchorPoint(ccp(0.0f, 0.5f));
                button->setPosition(ccp(0,0));
                button->setTag(idx);
                button->setScale(1.0f);
                CCMenu* menu = CCMenu::create(button, NULL);
                menu->setPosition(ccp(594.0f - (255 * 1.0f),72.0f));
                cell->addChild(menu);
            }
            else
            {
                CCSprite* playing = CCSprite::create("b_playing.png");
                playing->setAnchorPoint(ccp(0.0f, 0.5f));
                playing->setPosition(ccp(594.0f - 255.0f, 72.0f));
                cell->addChild(playing);
            }
            
        }
        
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
    int count = Facebook_Manager::sharedInstance()->getGameFriendList()->count();
    if(count >= 10) count = 9;
    
    return count;
}