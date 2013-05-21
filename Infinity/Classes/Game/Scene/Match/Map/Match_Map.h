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
    Match_Map():tileCount_Width(8),tileCount_Height(8),tile_Width(80),tile_Height(80),tile_X(40),tile_Y(640 - (720/2) + 40){}
    
public:
    CCPoint GetPosition_FromIndex(int x, int y);
    bool GetEmptyTile_FromTouch(const CCPoint& touchPos, int* index_X, int* index_Y);
    int GetTileCount_Width(){return tileCount_Width;}
    int GetTileCount_Height(){return tileCount_Height;}
    int GetTileTag(int index_X, int index_Y);
    int GetConvertedTileIndex(int index_X, int index_Y) { return (index_Y * tileCount_Width) + index_X;}
    int GetConvertedTileIndex_X(int index) { return index % tileCount_Width;}
    int GetConvertedTileIndex_Y(int index) { return index / tileCount_Height;}
    int GetUnitCount_White();
    int GetUnitCount_Black();
    
    void SetUnit_ToMap(Unit_Base* unit, int x, int y);
    void RemoveUnit(int index);
    void Update_MapData();
private:
    const int tile_Width, tile_Height;
    const int tileCount_Width, tileCount_Height;
    const int tile_X,tile_Y;
    std::vector<Unit_Base*> list_MapUnit;
    
private:
    void Init_Unit();
    void Init_CreateTile();
};

#endif /* defined(__Chess__Match_Map__) */
