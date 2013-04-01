//
//  Unit_Black.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#ifndef __Infinity__Unit_Black__
#define __Infinity__Unit_Black__


#include "Unit_Base.h"

class Unit_Black : public Unit_Base
{
public:
    CREATE_FUNC(Unit_Black);
    virtual bool init();
};

#endif /* defined(__Infinity__Unit_Black__) */
