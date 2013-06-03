//
//  GameUI_MainTitle_Invite.h
//  Infinity
//
//  Created by 정 기호 on 13. 6. 4..
//
//

#ifndef __Infinity__GameUI_MainTitle_Invite__
#define __Infinity__GameUI_MainTitle_Invite__

#include "cocos2d.h"
#include "CCTableView.h"
#include "Facebook_Manager.h"
#include "GameUI_MainTitle.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class GameUI_MainTitle_Invite : public CCNode, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate, public Facebook_Callback
{
public:
    virtual bool init();
    CREATE_FUNC(GameUI_MainTitle_Invite);
public:
    void ButtonDelegate_Invite(CCObject* sender);
    void ButtonDelegate_Back(CCObject* sender);
    
    void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {}
    void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
public:    
    virtual void fb_Callback_Login (bool){}
    virtual void fb_Callback_Picture (CCString* fbID, CCSprite* picture);
private:
    void AddPicture(CCNode* parent, CCSprite* picture, CCPoint anchor, CCPoint pos, int tag, float width, float height);
    CCTableView* tableView;
    int picture_Width, picture_Height, picture_Pos;
    float cell_Width, cell_Height;
};

#endif /* defined(__Infinity__GameUI_MainTitle_Invite__) */
