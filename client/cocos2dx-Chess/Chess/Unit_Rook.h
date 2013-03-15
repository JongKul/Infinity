//
//  Unit_Rook.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Unit_Rook__
#define __Chess__Unit_Rook__

#include "Unit_Base.h"

class Unit_Rook : public Unit_Base
{
public:
    Unit_Rook();
    ~Unit_Rook();
    CREATE_FUNC(Unit_Rook);
    virtual bool init();
};

#endif /* defined(__Chess__Unit_Rook__) */
