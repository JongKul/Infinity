//
//  PlayScene.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "PlayScene.h"
#import "PlayLayer.h"

@implementation PlayScene

-(id) init
{
    self = [super init];
    
    game = [Game sharedGame];
    
    playLayer = [PlayLayer node];
    [self addChild:playLayer];
    
    [game StartGame];
    [self scheduleUpdate];
    
    return self;
}

-(void)update:(ccTime)delta
{
    if([game isRunGame] == YES)
    {
        [playLayer update:delta];
    }
    //else     NSLog(@"Update");
}

-(void) dealloc
{
    [super dealloc];
}
@end
