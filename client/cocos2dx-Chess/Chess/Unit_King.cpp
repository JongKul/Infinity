//
//  Unit_King.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 15..
//
//

#include "Unit_King.h"

Unit_King::Unit_King():Unit_Base()
{
    
}

Unit_King::~Unit_King()
{
    
}

bool Unit_King::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_kdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(0.3f);
    sprite->setScaleY(0.2f);
    
    return true;
}