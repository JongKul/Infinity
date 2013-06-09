//
//  GameUI_MainTitle_RoomList.h
//  Infinity
//
//  Created by 정 기호 on 13. 5. 18..
//
//

#ifndef __Infinity__GameUI_MainTitle_RoomList__
#define __Infinity__GameUI_MainTitle_RoomList__

#include "cocos2d.h"
#include "CCTableView.h"
#include "Facebook_Manager.h"
#include "GameUI_MainTitle.h"
#include "Room_Manager.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class Room_List;

class GameUI_MainTitle_RoomList : public CCNode, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate, public Facebook_Callback, public Room_Callback
{
private:
    GameUI_MainTitle* uiMain;
    CCTableView *tableView_MyTurn, *tableView_Waiting;
    std::vector<Room_List*> list_MyTurn, list_Waiting;
    int curMakeTable;
    int picture_Width, picture_Height, picture_Pos;
public:
    virtual bool init();
    CREATE_FUNC(GameUI_MainTitle_RoomList);
public:
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
    
    virtual void fb_Callback_Login (bool){}
    virtual void fb_Callback_Picture (CCString* fbID, CCSprite* picture);
private:
    void AddPicture(CCNode* parent, CCSprite* picture, CCPoint anchor, CCPoint pos, int tag, float width, float height);
    void AddTableView_MyTurn();
    void AddTableView_Waiting();
public:
    virtual void Callback_RoomInfo(int roomIndex);
    void onHttpRequestCompleted_RoomList(cocos2d::CCNode *sender, void *data);
};

#endif /* defined(__Infinity__GameUI_MainTitle_RoomList__) */
