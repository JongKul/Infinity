//
//  PlayLayerUI.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "PlayLayerUI.h"
#import "Game.h"

@implementation PlayLayerUI

-(id)init
{
    self = [super init];
    
    count_label = [CCLabelTTF labelWithString:@"F:0" fontName:@"Marker Felt" fontSize:32];
    count_label.position = ccp(150.0f, 400.0f);
    [self addChild:count_label];
    
    blind = [CCSprite spriteWithFile:@"blind.png"];
    blind.position = ccp(160.0f, 240.0f);
    blind.scale = 100.0f;
    blind.opacity = 70.0f;
    blind.visible = NO;
    [self addChild:blind];
    
    CGSize size = [[CCDirector sharedDirector] winSize];
    
    CCMenuItem* reStart = [CCMenuItemImage itemWithNormalImage:@"restart_btn.png" selectedImage:nil target:self selector:@selector(ButtonDelegate_Restart)];
    reStart.position = ccp(size.width * 0.5f, size.height * 0.24f);
    
    CCMenuItem* main = [CCMenuItemImage itemWithNormalImage:@"main_btn.png" selectedImage:nil target:self selector:@selector(ButtonDelegate_Main)];
    main.position = ccp(size.width * 0.5f, size.height * 0.12f);
    
    menu = [CCMenu menuWithItems:reStart, main, nil];
    menu.position = ccp(0.0f, 0.0f);
    menu.visible = NO;
    [self addChild:menu];
    
    return self;
}

-(void)EndGame
{
    blind.visible = YES;
    menu.visible = YES;
}

-(void)ButtonDelegate_Restart
{
    [[Game sharedGame] StartGame];
    [[Game sharedGame] RunScene:Scene_Play];
}
-(void)ButtonDelegate_Main
{
    [[Game sharedGame] RunScene:Scene_Menu];
}

-(void)Set_Count:(int)count
{
    [count_label setString:[NSString stringWithFormat:@"F:%d", count]];
}

@end
