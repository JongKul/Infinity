//
//  Match_Map.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Match_Map.h"

bool Match_Map::init()
{
    tile_Width = 60;
    tile_Height = 40;
    
    for(int i=0; i<8; ++i)
    {
        for(int j=0; j<8; ++j)
        {
            CCSprite* sprite = NULL;
            if((i+j) % 2 != 0) sprite = CCSprite::create("white.png");
            else sprite = CCSprite::create("black.png");
            
            sprite->setPosition(ccp((tile_Width/2) + (tile_Width*j), (tile_Height/2) + (tile_Height*i)));
            this->addChild(sprite);
            list_MapSprite.push_back(sprite);
        }
    }
    
    return true;
}

//좌측하단이 0,0이고 우,상으로 인덱스가 증가한다.
CCPoint Match_Map::GetPosition_FromIndex(int x, int y)
{
    return ccp((tile_Width/2) + (tile_Width*x), (tile_Height/2) + (tile_Height*y));
}

bool Match_Map::GetPosition_FromTouch(const cocos2d::CCPoint &touchPos, CCPoint* returnPos)
{
    for(int i=0; i<list_MapSprite.size(); ++i)
    {
        if (list_MapSprite[i]->boundingBox().containsPoint(touchPos) == true)
        {
            CCPoint pos = list_MapSprite[i]->getPosition();
            returnPos->x = pos.x;
            returnPos->y = pos.y;
            return true;
        }
    }
    
    return false;
}