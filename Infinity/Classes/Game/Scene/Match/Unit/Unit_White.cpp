//
//  Unit_White.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "Unit_White.h"

bool Unit_White::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("Unit_White.png");
    
    this->setTag(1);
    
    return true;
}
