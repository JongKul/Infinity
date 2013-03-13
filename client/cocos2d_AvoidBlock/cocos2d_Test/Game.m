//
//  Game.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "Game.h"
#import "PlayScene.h"
#import "MenuScene.h"

@implementation Game

+(id)sharedGame
{
    static Game* Instance = nil;
    if(Instance == nil)
    {
        NSLog(@"Game Instance");
        Instance = [[self alloc] init];
    }
    
    return Instance;
}

-(id)init
{
    NSLog(@"Game Init");
    self = [super init];
    return self;
}

-(void)dealloc
{
    [super dealloc];
}

-(void)StopGame
{
    NSLog(@"Game StopGame");
    _run = NO;
}
-(void)StartGame
{
    NSLog(@"Game StartGame");
    _run = YES;
}
-(BOOL)isRunGame
{
    return _run;
}

-(void)RunScene:(enum Game_SceneType)type
{
    
    CCScene* scene = nil;
    if(type == Scene_Menu) scene = [MenuScene node];
    else if(type == Scene_Play) scene = [PlayScene node];
    
    if(scene == nil) return;
    
    CCDirector* dir = [CCDirector sharedDirector];
    
    if([dir runningScene] == nil) [dir runWithScene:scene];
    else [dir replaceScene:scene];
    
    [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
    [[CCTextureCache sharedTextureCache] removeUnusedTextures];
    [[CCTextureCache sharedTextureCache] removeAllTextures];
}

@end
