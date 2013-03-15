//
//  Unit_Pawn.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Pawn.h"

Unit_Pawn::Unit_Pawn():Unit_Base()
{
    
}

Unit_Pawn::~Unit_Pawn()
{
    
}

bool Unit_Pawn::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_plt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(0.3f);
    sprite->setScaleY(0.2f);
    
    return true;
}