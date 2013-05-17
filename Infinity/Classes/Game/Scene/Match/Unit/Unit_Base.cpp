 //
//  Unit_Base.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Base.h"

Unit_Base::Unit_Base()
{
    
}

Unit_Base::~Unit_Base()
{

}

bool Unit_Base::init()
{
    sprite = NULL;
    return true;
}

void Unit_Base::SetParent(CCNode* parent)
{
    if(parent != NULL && sprite != NULL)
    {
        parent->addChild(this);
        this->addChild(sprite);
    }
}

void Unit_Base::setPosition(const cocos2d::CCPoint &var)
{
    if(sprite != NULL)
    {
        //sprite->setPosition((ccp(0,0)));
        sprite->setPosition(var);
    }
}

void Unit_Base::SetMapScale(float width, float height)
{
    if(sprite == NULL)return;
    
    CCSize size = sprite->getContentSize();
    float scale_X = width / size.width;
    float scale_Y = height / size.height;
    
    sprite->setScaleX(scale_X);
    sprite->setScaleY(scale_Y);
}

CCRect Unit_Base::boundingBox()
{
    return sprite->boundingBox();
}