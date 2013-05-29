//
//  GameUI_MainTitle_Rank.h
//  Infinity
//
//  Created by 정 기호 on 13. 5. 21..
//
//

#ifndef __Infinity__GameUI_MainTitle_Rank__
#define __Infinity__GameUI_MainTitle_Rank__

#include "cocos2d.h"
#include "CCTableView.h"
#include "Facebook_Manager.h"
#include "GameUI_MainTitle.h"
#include "Room_Manager.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GameUI_MainTitle_Rank : public CCNode, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate, public Facebook_Callback, public Room_Callback
{
private:
    GameUI_MainTitle* uiMain;
    CCTableView* tableView;
public:
    virtual bool init();
    CREATE_FUNC(GameUI_MainTitle_Rank);
public:
    void ButtonDelegate_Start(CCObject* sender);
    void ButtonDelegate_Post(CCObject* sender);
    void ButtonDelegate_ChangeScene(CCObject* sender);
    void ButtonDelegate_Picture(CCObject* sender);
    
    void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {}
    void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
public:
    void SetGameLayer(GameUI_MainTitle* main){ uiMain = main; }
    virtual void setVisible(bool visible);
    
    virtual void fb_Callback_Login (bool);
    virtual void fb_Callback_Picture (CCString* fbID, CCSprite* picture);
public:
    virtual void Callback_RoomMake(int roomIndex);
private:
    void AddPicture(CCNode* parent, CCSprite* picture, CCPoint anchor, CCPoint pos, int tag, float width, float height);
};

#endif /* defined(__Infinity__GameUI_MainTitle_Rank__) */
