//
//  Match_Map.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Match_Map__
#define __Chess__Match_Map__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

class Unit_Base;

class Match_Map : public CCNode
{
public:
    bool init();
    CREATE_FUNC(Match_Map);
    Match_Map():tileCount_Width(8),tileCount_Height(8),tile_Width(60),tile_Height(40){}
    
public:
    CCPoint GetPosition_FromIndex(int x, int y);
    bool GetMovePosition_FromTouch(const CCPoint& touchPos, CCPoint* returnPos, int* index);
    int GetTileCount_Width(){return tileCount_Width;}
    int GetTileCount_Height(){return tileCount_Height;}
    
    void SetUnit_ToMap(Unit_Base* unit, int x, int y);
    void SetEnable_MoveTile(int index, int x, int y);
    void SetDisable_MoveTileAll();
    
public:
    void MoveToUnit(int oldIndex, int newIndex);
    
private:
    const int tile_Width;
    const int tile_Height;
    const int tileCount_Width;
    const int tileCount_Height;
    std::vector<CCSprite*> list_MapSprite;
    std::vector<Unit_Base*> list_MapUnit;
    
private:
    void Init_CreateTile();
};

#endif /* defined(__Chess__Match_Map__) */
