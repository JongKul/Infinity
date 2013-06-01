//
//  UI_Utility.h
//  Infinity
//
//  Created by 정 기호 on 13. 6. 1..
//
//

#ifndef __Infinity__UI_Utility__
#define __Infinity__UI_Utility__

#include "cocos2d.h"

using namespace cocos2d;

class UI_Utility
{
public:
    static void Util_AddLabel(CCNode* parent, const CCPoint& pos, const CCPoint& anchor, const char* str, int fontSize, const ccColor3B& color);
};

#endif /* defined(__Infinity__UI_Utility__) */
