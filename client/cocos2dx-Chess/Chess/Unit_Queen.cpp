//
//  Unit_Queen.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Queen.h"

Unit_Queen::Unit_Queen():Unit_Base()
{
    
}

Unit_Queen::~Unit_Queen()
{
   
}

bool Unit_Queen::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_qdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(0.3f);
    sprite->setScaleY(0.2f);
    
    return true;
}