//
//  Unit_Knight.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Knight.h"

Unit_Knight::Unit_Knight():Unit_Base()
{
    
}

Unit_Knight::~Unit_Knight()
{
   
}

bool Unit_Knight::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_ndt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(0.3f);
    sprite->setScaleY(0.2f);
    
    return true;
}