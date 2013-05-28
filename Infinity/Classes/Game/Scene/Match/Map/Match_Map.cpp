//
//  Match_Map.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Match_Map.h"
#include "Unit_Base.h"
#include "Room_Manager.h"
#include "Othello_Logic.h"

bool Match_Map::init()
{
    Init_CreateTile();
    Init_Unit();
    
    return true;
}

void Match_Map::Init_Unit()
{
    for(int i=0; i<tileCount_Height; ++i)
    {
        for(int j=0; j<tileCount_Width; ++j)
        {
            list_MapUnit.push_back(NULL);
        }
    }
    
    Room_List* curRoom = Room_Manager::sharedInstance()->curMatchRoom;
    for(int i=0; i<tileCount_Height; ++i)
    {
        for(int j=0; j<tileCount_Width; ++j)
        {
            int index = i * tileCount_Width + j;
            Unit_Base* unit = Othello_Logic::CreateUnit(curRoom->room_data[index]);
            if(unit != NULL)
            {
                SetUnit_ToMap(unit, j, (tileCount_Height-1) - i);
            }
        }
    }
}

void Match_Map::Init_CreateTile()
{
    /*
    CCSprite* mapBack = CCSprite::create("frame2.png");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    mapBack->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(mapBack);
     */
    
    for(int i=0; i<tileCount_Height; ++i)
    {
        for(int j=0; j<tileCount_Width; ++j)
        {
            CCSprite* tile = CCSprite::create("tile.png");
            int offset_X = j * tile_Width;
            int offset_Y = i * tile_Height;
            
            tile->setPosition(ccp(tile_X + offset_X + tile_Width/2, tile_Y + offset_Y + tile_Height/2));
            this->addChild(tile);
        }
    }
}

int Match_Map::GetUnitCount_White()
{
    int count = 0;
    
    for(int i=0; i<list_MapUnit.size(); ++i)
    {
        if(list_MapUnit[i] != NULL && list_MapUnit[i]->getTag() == 1)
            ++count;
    }
    
    return count;
}
int Match_Map::GetUnitCount_Black()
{
    int count = 0;
    
    for(int i=0; i<list_MapUnit.size(); ++i)
    {
        if(list_MapUnit[i] != NULL && list_MapUnit[i]->getTag() == 0)
            ++count;
    }
    
    return count;
}

//좌측하단이 0,0이고 우,상으로 인덱스가 증가한다.
CCPoint Match_Map::GetPosition_FromIndex(int x, int y)
{
    return ccp((tile_X + tile_Width/2) + (tile_Width*x), (tile_Y + tile_Height/2) + (tile_Height*y));
    //return ccp((tile_X) + (tile_Width*x), (tile_Y) + (tile_Height*y));
}

int Match_Map::GetTileTag(int index_X, int index_Y)
{
    int index = GetConvertedTileIndex(index_X, index_Y);
    
    if(list_MapUnit[index] == NULL) return -1;
    else return list_MapUnit[index]->getTag();
}

bool Match_Map::GetEmptyTile_FromTouch(const cocos2d::CCPoint &touchPos,  int* index_X, int* index_Y)
{
    int touch_X = (int)(touchPos.x);
    int touch_Y = (int)(touchPos.y);
    
    if(touch_X < tile_X || touch_X > (tile_X + tile_Width * tileCount_Width)) return false;
    if(touch_Y < tile_Y || touch_Y > (tile_Y + tile_Height * tileCount_Width)) return false;
    
    *index_X = (touch_X - tile_X) / tile_Width;
    *index_Y = (touch_Y - tile_Y) / tile_Height;
    
    return GetTileTag(*index_X, *index_Y) == -1;
}

void Match_Map::SetUnit_ToMap(Unit_Base *unit, int x, int y)
{
    int index = GetConvertedTileIndex(x, y);
    list_MapUnit[index] = unit;
    unit->SetParent(this);
    unit->setPosition(GetPosition_FromIndex(x, y));
    unit->SetMapScale(tile_Width, tile_Height);
}

void Match_Map::RemoveUnit(int index)
{
    //CCLOG("Index : %d", index);
    if(list_MapUnit[index] != NULL)
    {
        list_MapUnit[index]->removeAllChildren();
        this->removeChild(list_MapUnit[index]);
        //list_MapUnit[index]->release();
        list_MapUnit[index] = NULL;
    }
}

void Match_Map::Update_MapData()
{
    Room_List* curRoom = Room_Manager::sharedInstance()->curMatchRoom;
    for(int i=0; i<tileCount_Height; ++i)
    {
        for(int j=0; j<tileCount_Width; ++j)
        {
            int clientIndex = i * tileCount_Width + j;
            int serverIndex = ((tileCount_Height - 1) - i) * tileCount_Width + j;
            
            if(GetTileTag(j, i) != curRoom->room_data[serverIndex])
            {
                RemoveUnit(clientIndex);
                Unit_Base* unit = Othello_Logic::CreateUnit(curRoom->room_data[serverIndex]);
                SetUnit_ToMap(unit, j, i);
            }
        }
    }
}