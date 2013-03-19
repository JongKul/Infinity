//
//  GameUI_MainTitle.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#include "GameUI_MainTitle.h"
#include "GameScene_MainTitle.h"

bool GameUI_MainTitle::init()
{
    gameLayer = NULL;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* title = CCSprite::create("HelloWorld.png");
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    title->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(title);
    
    CCSprite* test = CCSprite::create("Icon.png");
    test->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(test);
    
    CCTableView* tableView = CCTableView::create(this, CCSizeMake(60, 280));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(50,winSize.height/2-120));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
    
    CCMenuItemImage* start_Button = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this,menu_selector(GameUI_MainTitle::ButtonDelegate_Start));
    CCMenu* menu = CCMenu::create(start_Button, NULL);
    menu->setPosition(ccp(winSize.width * 0.8f, winSize.height * 0.2f));
    this->addChild(menu);
    
    return true;
}


void GameUI_MainTitle::ButtonDelegate_Start(cocos2d::CCObject *sender)
{
    gameLayer->ChangeScene();
}

void GameUI_MainTitle::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize GameUI_MainTitle::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    
    return CCSizeMake(60,60);
}
CCTableViewCell* GameUI_MainTitle::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell)
    {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("Icon.png");
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