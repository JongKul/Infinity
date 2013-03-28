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
    
    CCSprite* title = CCSprite::create("HelloWorld.png");
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    title->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(title);
    
    CCSprite* test = CCSprite::create("Icon-144.png");
    test->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(test);
    
    CCTableView* tableView = CCTableView::create(this, CCSizeMake(200, 500));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(50,winSize.height/2-120));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
    
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
    Facebook_Manager::sharedInstance()->Post();
}


void GameUI_MainTitle::fb_Callback_Login(bool ret)
{
    if(ret == true)
    {
        CCArray* friList = Facebook_Manager::sharedInstance()->getFriendList();
        for(int i=0; i<friList->count(); ++i)
        {
            Facebook_Account* fri = (Facebook_Account*)friList->objectAtIndex(i);
            Facebook_Manager::sharedInstance()->GetPicture(fri->fbID, this);
        }
        Native_ShowAlert("Native Test");
    }
    else
    {
        
    }
}

void GameUI_MainTitle::fb_Callback_Picture(cocos2d::CCString *fbID, cocos2d::CCSprite *picture)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    picture->setPosition(ccp(CCRANDOM_0_1() * winSize.width,CCRANDOM_0_1() * winSize.height));
    
    if(picture == NULL)CCLOG("NULL");
    addChild(picture);
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
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("Icon-144.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    return cell;
}

unsigned int GameUI_MainTitle::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return 10;
}