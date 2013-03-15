//
//  Unit_Bishop.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Unit_Bishop__
#define __Chess__Unit_Bishop__

#include "Unit_Base.h"

class Unit_Bishop : public Unit_Base
{
public:
    Unit_Bishop();
    ~Unit_Bishop();
    CREATE_FUNC(Unit_Bishop);
    virtual bool init();
};

#endif /* defined(__Chess__Unit_Bishop__) */
