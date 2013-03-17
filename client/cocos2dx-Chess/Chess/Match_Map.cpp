//
//  Match_Map.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Match_Map.h"
#include "Unit_Base.h"

bool Match_Map::init()
{    
    Init_CreateTile();
    
    return true;
}

void Match_Map::Init_CreateTile()
{
    for(int i=0; i<tileCount_Height; ++i)
    {
        for(int j=0; j<tileCount_Width; ++j)
        {
            CCSprite* sprite = NULL;
            if((i+j) % 2 != 0) sprite = CCSprite::create("white.png");
            else sprite = CCSprite::create("black.png");
            
            sprite->setPosition(ccp((tile_Width/2) + (tile_Width*j), (tile_Height/2) + (tile_Height*i)));
            this->addChild(sprite);
            list_MapSprite.push_back(sprite);
            list_MapUnit.push_back(NULL);
        }
    }
}

//좌측하단이 0,0이고 우,상으로 인덱스가 증가한다.
CCPoint Match_Map::GetPosition_FromIndex(int x, int y)
{
    return ccp((tile_Width/2) + (tile_Width*x), (tile_Height/2) + (tile_Height*y));
}

void Match_Map::MoveToUnit(int oldIndex, int newIndex)
{
    Unit_Base* unit = list_MapUnit[oldIndex];
    list_MapUnit[oldIndex] = NULL;
    list_MapUnit[newIndex] = unit;
    unit->SetMapIndex(newIndex);
}

bool Match_Map::GetMovePosition_FromTouch(const cocos2d::CCPoint &touchPos, CCPoint* returnPos, int* index)
{
    for(int i=0; i<list_MapSprite.size(); ++i)
    {
        if(list_MapSprite[i]->getColor().r == 0)
        {
            if (list_MapSprite[i]->boundingBox().containsPoint(touchPos) == true)
            {
                CCPoint pos = list_MapSprite[i]->getPosition();
                returnPos->x = pos.x;
                returnPos->y = pos.y;
                *index = i;
                return true;
            }
        }
    }
    
    return false;
}

void Match_Map::SetUnit_ToMap(Unit_Base *unit, int x, int y)
{
    int index = x*tileCount_Width + y;
    list_MapUnit[index] = unit;
    unit->SetMapIndex(index);
}

void Match_Map::SetEnable_MoveTile(int index, int x, int y)
{
    int unit_X = index % tileCount_Width;
    int unit_Y = index / tileCount_Height;
    int unit_MoveX = unit_X + x;
    int unit_MoveY = unit_Y + y;
    
    if(unit_MoveX < 0 || unit_MoveX >= tileCount_Width) return;
    if(unit_MoveY < 0 || unit_MoveY >= tileCount_Height) return;
    
    int finalIndex = unit_MoveY * tileCount_Height + unit_MoveX;
    if(list_MapUnit[finalIndex] != NULL) return;
    
    list_MapSprite[finalIndex]->setColor(ccc3(0, 255, 0));
}

void Match_Map::SetDisable_MoveTileAll()
{
    for(int i=0; i<list_MapSprite.size(); ++i)
    {
        list_MapSprite[i]->setColor(ccc3(255, 255, 255));
    }
}