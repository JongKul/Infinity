//
//  UI_Utility.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 6. 1..
//
//

#include "UI_Utility.h"

void UI_Utility::Util_AddLabel(CCNode* parent, const CCPoint& pos, const CCPoint& anchor, const char* str, int fontSize, const ccColor3B& color)
{
    CCLabelTTF *label = CCLabelTTF::create(str, "Helvetica", fontSize);
    label->setPosition(pos);
    label->setAnchorPoint(anchor);
    label->setColor(color);
    parent->addChild(label);
}