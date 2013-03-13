//
//  Player.h
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

enum Player_MoveType
{
    Player_Move_None = 0,
    Player_Move_Stop,
    Player_Move_Left,
    Player_Move_Right,
    Player_Move_MAX,
};

@interface Player : CCNode
{
    CCSprite* body;
    CCSprite* rect;
    CGPoint vel;
}

-(void)update:(ccTime)delta;
-(void)Move:(enum Player_MoveType)type;
-(void)Dead;
-(CGRect) boundingBox;

@end
