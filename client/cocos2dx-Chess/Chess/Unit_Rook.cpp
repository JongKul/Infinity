//
//  Unit_Rook.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Rook.h"

Unit_Rook::Unit_Rook():Unit_Base()
{
    
}

Unit_Rook::~Unit_Rook()
{
    
}

bool Unit_Rook::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_rdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(0.3f);
    sprite->setScaleY(0.2f);
    
    return true;
}