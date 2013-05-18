//
//  Scene_Manager.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#ifndef __Infinity__Scene_Manager__
#define __Infinity__Scene_Manager__

#include "cocos2d.h"
using namespace cocos2d;

class Scene_Manager
{
public:
    static void ChangeScene_Match();
    static void ChangeScene_MainTitle();
    static CCScene* GetCurScene();
    static void SetCurScene(CCScene* scene);
private:
    static void ChangeScene_Common(CCScene* scene);
    
public:
    static Scene_Manager* SharedInstance();
private:
    CCScene* curScene;
};

#endif /* defined(__Infinity__Scene_Manager__) */
