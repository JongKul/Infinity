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

class Match_Map : public CCNode
{
public:
    bool init();
    CREATE_FUNC(Match_Map);
public:
    CCPoint GetPosition_FromIndex(int x, int y);
    bool GetPosition_FromTouch(const CCPoint& touchPos, CCPoint* returnPos);
private:
    int tile_Width;
    int tile_Height;
    std::vector<CCSprite*> list_MapSprite;
};

#endif /* defined(__Chess__Match_Map__) */
