//
//  PlayLayer.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "PlayLayer.h"
#import "Game.h"

@implementation PlayLayer
@synthesize menu = _menu;

-(id)init
{
    self = [super init];
    
    CGSize size = [[CCDirector sharedDirector] winSize];
    
    CCSprite* bg = [CCSprite spriteWithFile:@"game_bg.png"];
    bg.position = ccp(size.width * 0.5f, size.height * 0.5f);
    [self addChild:bg];
    
    CCMenuItem* left = [CCMenuItemImage itemWithNormalImage:@"Icon.png" selectedImage:nil target:self selector:@selector(ButtonDelegate_Left)];
    left.position = ccp(size.width * 0.1f, size.height * 0.5f);
    
    CCMenuItem* right = [CCMenuItemImage itemWithNormalImage:@"Icon.png" selectedImage:nil target:self selector:@selector(ButtonDelegate_Right)];
    right.position = ccp(size.width * 0.9f, size.height * 0.5f);
    
    _menu = [CCMenu menuWithItems:left, right, nil];
    _menu.position = ccp(0,0);
    [self addChild : _menu];
    
    player = [Player node];
    player.position = ccp(size.width * 0.5f, size.height * 0.12f);
    [self addChild:player];
    
    blcokManager = [BlockManager node];
    blcokManager.position = ccp(0.0f, 0.0f);
    [self addChild:blcokManager];
    
    ui = [PlayLayerUI node];
    ui.position = ccp(0.0f, 0.0f);
    [self addChild:ui];
    
    fCount = 0;
    
    return self;
}

-(void)update:(ccTime)delta
{
    [player update:delta];
    [blcokManager update:delta];
    for(Block* block in blcokManager.blockArray)
    {
        //CGRect re = [block boundingBox];
        //NSLog([NSString stringWithFormat:@"%f %f %f %f",re.origin.x,re.origin.y,re.size.width,re.size.height]);
        
        if(CGRectIntersectsRect([player boundingBox], [block boundingBox]) == YES)
        {
            //NSLog(@"CGRectIntersectsRect");
            if([block type] == 4) ++fCount;
            [blcokManager RemoveBlock:block];
            [ui Set_Count:fCount];
            break;
        }
    }
    
    if(fCount >= 3)
    {
        fCount = 0;
        Game* game = [Game sharedGame];
        [game StopGame];
        [player Dead];
        [ui EndGame];
    }
}

-(void)ButtonDelegate_Left
{
    [player Move:Player_Move_Left];
}

-(void)ButtonDelegate_Right
{
   [player Move:Player_Move_Right];
}

-(void)dealloc
{
    fCount = 0;
    [super dealloc];
}

@end
