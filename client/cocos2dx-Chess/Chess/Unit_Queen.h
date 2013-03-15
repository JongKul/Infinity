//
//  Unit_Queen.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Unit_Queen__
#define __Chess__Unit_Queen__

#include "Unit_Base.h"

class Unit_Queen : public Unit_Base
{
public:
    Unit_Queen();
    ~Unit_Queen();
    CREATE_FUNC(Unit_Queen);
    virtual bool init();
};

#endif /* defined(__Chess__Unit_Queen__) */
