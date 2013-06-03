//
//  GameUI_MainTitle_Store.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 6. 4..
//
//

#include "GameUI_MainTitle_Store.h"

bool GameUI_MainTitle_Store::init()
{
    CCNode::init();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* back = CCSprite::create("playing.png");
    back->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(back);
    
    return true;
}