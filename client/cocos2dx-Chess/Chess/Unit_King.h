//
//  Unit_King.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 15..
//
//

#ifndef __Chess__Unit_King__
#define __Chess__Unit_King__

#include "Unit_Base.h"

class Unit_King : public Unit_Base
{
public:
    Unit_King();
    ~Unit_King();
    CREATE_FUNC(Unit_King);
    virtual bool init();
};

#endif /* defined(__Chess__Unit_King__) */
