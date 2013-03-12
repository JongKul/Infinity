//
//  PlayScene.h
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "Game.h"
#import "PlayLayer.h"

@interface PlayScene : CCScene
{
    Game* game;
    PlayLayer* playLayer;
}

-(void)update:(ccTime)delta;

@end
