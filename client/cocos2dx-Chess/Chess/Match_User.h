//
//  Match_User.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 15..
//
//

#ifndef __Chess__Match_User__
#define __Chess__Match_User__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

class Match_Map;
class Unit_Base;

class Match_User : public CCNode
{
public:
    bool init();
    CREATE_FUNC(Match_User);
    ~Match_User();
public:
    void Start(Match_Map* map);
    void TouchProcess(CCPoint touchPos);
    void UnitMiveFinish(Unit_Base* unit);
protected:
    Match_Map* curMap;
    Unit_Base* curSelectedUnit;
    std::vector<Unit_Base*> list_Unit;
    void (Match_User::*TouchDelegate)(const CCPoint& touchPos);
private:
    void TouchDelegate_WaitUnitSelect(const CCPoint& touchPos);
    void TouchDelegate_WaitMoveSelect(const CCPoint& touchPos);
};

#endif /* defined(__Chess__Match_User__) */
