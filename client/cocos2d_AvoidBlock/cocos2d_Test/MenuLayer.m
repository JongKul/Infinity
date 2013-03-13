//
//  MenuLayer.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "MenuLayer.h"
#import "Game.h"

@implementation MenuLayer
-(id)init
{
    self = [super init];
    
    CGSize size = [[CCDirector sharedDirector]winSize];
    
    CCSprite* bg = [CCSprite spriteWithFile:@"start_bg_01.png"];
    bg.position = ccp(size.width * 0.5f, size.height * 0.5f);
    [self addChild:bg];
    
    CCSprite* cha = [CCSprite spriteWithFile:@"start_cha.png"];
    cha.position = ccp(size.width * 0.5f, size.height * 0.5f);
    [self addChild:cha];
    
    id moveDown = [CCMoveBy actionWithDuration:0.7f position:ccp(0.0f,-30.0f)];
    id moveUp = [CCMoveBy actionWithDuration:0.7f position:ccp(0.0f,30.0f)];
    id sequence = [CCSequence actions:moveDown, moveUp, nil];
    id repeat = [CCRepeatForever actionWithAction:sequence];
    [cha runAction:repeat];

    CCMenuItem* button = [CCMenuItemImage itemWithNormalImage:@"start_btn.png" selectedImage:nil target:self selector:@selector(ButtonDelegate_Start)];
    button.position = ccp(0,0);
    
    CCMenu* menu = [CCMenu menuWithItems:button, nil];
    menu.position = ccp(size.width * 0.5f, size.height * 0.12f);
    [self addChild:menu];
    
    return self;
}

-(void)ButtonDelegate_Start
{
    NSLog(@"ButtonDelegate_Start");
    [[Game sharedGame] RunScene:Scene_Play];
}

-(void) dealloc
{
    [super dealloc];
}

@end
