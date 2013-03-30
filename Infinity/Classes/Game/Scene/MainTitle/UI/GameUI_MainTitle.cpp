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
    
    return true;
}


void GameUI_MainTitle::ButtonDelegate_Start(cocos2d::CCObject *sender)
{
    //IOS_Helper::sharedInstance()->ShowAlert();
    //IOS_Helper::sharedInstance()->FacebookLogin();
    //gameLayer->ChangeScene();
    Facebook_Manager::sharedInstance()->Login(this);
}

void GameUI_MainTitle::ButtonDelegate_Post(cocos2d::CCObject *sender)
{
    //Facebook_Manager::sharedInstance()->Post();
    Facebook_Manager::sharedInstance()->GetPicture(CCString::create("100001756203467"), this);
    
}


void GameUI_MainTitle::fb_Callback_Login(bool ret)
{
    if(ret == true)
    {
        CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        tableView = CCTableView::create(this, CCSizeMake(144, 144*5));
        tableView->setDirection(kCCScrollViewDirectionVertical);
        tableView->setPosition(ccp(50,winSize.height/2-120));
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(tableView);
        //tableView->reloadData();
        
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
    
    int index = 0;
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    for(index=0; index<friList->count(); ++index)
    {
        Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(index);
        if(fri != NULL && fri->fbID->isEqual(fbID) == true)break;
    }

    CCTableViewCell *cell = tableView->cellAtIndex(index);
    if(cell == NULL)
    {
        CCLog("Cell NULL index : %d", index);
        return;
    }
    picture->setAnchorPoint(CCPointZero);
    picture->setPosition(ccp(0, 0));
    cell->addChild(picture);
    
    //addChild(picture);
}
 

void GameUI_MainTitle::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize GameUI_MainTitle::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(144,144);
}
CCTableViewCell* GameUI_MainTitle::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
    Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(idx);
    CCTableViewCell *cell = table->cellAtIndex(idx);//table->dequeueCell();
    //CCLog("tableCellAtIndex : %d, name : %s", idx, fri->name->getCString());
    //CCString *string = CCString::createWithFormat("%d", idx);
    if (!cell)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSprite* item = CCSprite::create("Icon-144.png");
        item->setPosition(CCPointZero);
		item->setAnchorPoint(CCPointZero);
        cell->addChild(item);

        CCLabelTTF *label = CCLabelTTF::create(fri->name->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);//, 10);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(fri->name->getCString());
    }
    
    tableView = table;
    
    return cell;
}

unsigned int GameUI_MainTitle::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    //CCLog("count : %d", Facebook_Manager::sharedInstance()->getFriendList()->count());

    return 30;//Facebook_Manager::sharedInstance()->getFriendList()->count();
}