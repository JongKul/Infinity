//
//  Unit_Pawn.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Unit_Pawn__
#define __Chess__Unit_Pawn__

#include "Unit_Base.h"

class Unit_Pawn : public Unit_Base
{
public:
    Unit_Pawn();
    ~Unit_Pawn();
    CREATE_FUNC(Unit_Pawn);
    virtual bool init();
};

#endif /* defined(__Chess__Unit_Pawn__) */
