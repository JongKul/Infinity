//
//  Unit_Bishop.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Bishop.h"

Unit_Bishop::Unit_Bishop():Unit_Base()
{
    
}

Unit_Bishop::~Unit_Bishop()
{
   
}

bool Unit_Bishop::init()
{
    Unit_Base::init();
    
    sprite = CCSprite::create("200px-Chess_bdt45_svg.png");
    sprite->setPosition(ccp(30, 20));
    sprite->setScaleX(0.3f);
    sprite->setScaleY(0.2f);
    
    return true;
}