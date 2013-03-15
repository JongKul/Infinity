//
//  Unit_Knight.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Unit_Knight__
#define __Chess__Unit_Knight__

#include "Unit_Base.h"

class Unit_Knight : public Unit_Base
{
public:
    Unit_Knight();
    ~Unit_Knight();
    CREATE_FUNC(Unit_Knight);
    virtual bool init();
};

#endif /* defined(__Chess__Unit_Knight__) */
