//
//  GameUI_MainTitle.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#ifndef __Chess__GameUI_MainTitle__
#define __Chess__GameUI_MainTitle__

#include "cocos2d.h"
#include "CCTableView.h"
#include "Facebook_Manager.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GameLayer_MainTitle;

class GameUI_MainTitle : public CCNode, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate, public Facebook_Callback
{
private:
    GameLayer_MainTitle* gameLayer;
    CCTableView* tableView;
public:
    virtual bool init();
    CREATE_FUNC(GameUI_MainTitle);
public:
    void ButtonDelegate_Start(CCObject* sender);
    void ButtonDelegate_Post(CCObject* sender);

    void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {}
    void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
public:
    void SetGameLayer(GameLayer_MainTitle* layer){ gameLayer = layer; }
    virtual void fb_Callback_Login (bool);
    virtual void fb_Callback_Picture (CCString* fbID, CCSprite* picture);
private:
    void AddPicture(CCNode* parent, CCSprite* picture, CCPoint anchor, CCPoint pos, int tag, float width, float height);
};

#endif /* defined(__Chess__GameUI_MainTitle__) */
