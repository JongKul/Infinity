//
//  Sound_Manager.h
//  Infinity
//
//  Created by 정 기호 on 13. 6. 10..
//
//

#ifndef __Infinity__Sound_Manager__
#define __Infinity__Sound_Manager__

#include "cocos2d.h"

using namespace cocos2d;

class Sound_Manager
{
public:
    static void PlayBackground();
    static void PlayEffect(const char* file);
    static void SetSoundVolume();
    static void SetSoundOff();
    static void SetSoundOn();
};

#endif /* defined(__Infinity__Sound_Manager__) */
