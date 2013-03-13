//
//  Game.h
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

enum Game_SceneType
{
    Scene_None = 0,
    Scene_Menu,
    Scene_Play,
    Scene_Max,
};

@interface Game : CCNode
{
    BOOL _run;
}

+(id)sharedGame;
-(void)RunScene:(enum Game_SceneType)type;
-(void)StopGame;
-(void)StartGame;
-(BOOL)isRunGame;
@end
