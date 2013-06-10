//
//  Sound_Manager.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 6. 10..
//
//

#include "Sound_Manager.h"
#include "SimpleAudioEngine.h"


void Sound_Manager::PlayBackground()
{
    SetSoundVolume();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound_BGM.mp3", true);
}
void Sound_Manager::PlayEffect(const char* file)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(file);
}
void Sound_Manager::SetSoundVolume()
{
    float bgm = CCUserDefault::sharedUserDefault()->getFloatForKey("volume_bgm", 1.0f);
    float effect = CCUserDefault::sharedUserDefault()->getFloatForKey("volume_effect", 1.0f);
    
    //CCLOG("bgm : %f, effect : %f", bgm, effect);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(bgm);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(effect);
}
void Sound_Manager::SetSoundOff()
{
    CCUserDefault::sharedUserDefault()->setFloatForKey("volume_effect", 0.0f);
    CCUserDefault::sharedUserDefault()->setFloatForKey("volume_bgm", 0.0f);
    
    SetSoundVolume();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
}
void Sound_Manager::SetSoundOn()
{
    CCUserDefault::sharedUserDefault()->setFloatForKey("volume_effect", 1.0f);
    CCUserDefault::sharedUserDefault()->setFloatForKey("volume_bgm", 1.0f);
    
    SetSoundVolume();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
}