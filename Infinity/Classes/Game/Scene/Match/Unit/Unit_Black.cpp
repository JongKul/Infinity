//
//  Unit_Black.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "Unit_Black.h"


bool Unit_Black::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("c_b.png");
    sprite->setAnchorPoint(ccp(0.5, 0.5));
    
    this->setTag(0);
    
    return true;
}