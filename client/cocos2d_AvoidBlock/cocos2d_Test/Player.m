//
//  Player.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "Player.h"


@implementation Player

-(id) init
{
    self = [super init];
    
    body = [CCSprite spriteWithFile:@"C_default.png"];
    body.position = ccp(0.0f, 0.0f);
    [self addChild:body];
    
    rect = [CCSprite spriteWithFile:@"C_bound.png"];
    rect.position = ccp(0.0f, 35.0f);
    rect.visible = NO;
    [self addChild:rect];
    
    CCAnimation* ani = [[CCAnimation alloc] init];
    [ani setDelayPerUnit:0.08f];
    
    [ani addFrameWithFilename:@"C_left.png"];
    [ani addFrameWithFilename:@"C_default.png"];
    [ani addFrameWithFilename:@"C_right.png"];
    [ani addFrameWithFilename:@"C_default.png"];
    
    CCAnimate* animate = [CCAnimate actionWithAnimation:ani];
    animate = [CCRepeatForever actionWithAction:animate];
    [body runAction:animate];
    
    vel = ccp(0.0f, 0.0f);
    
    return self;
}

-(void)Dead
{
    [body stopAllActions];
    [body setTexture:[[CCTextureCache sharedTextureCache] addImage:@"C_final.png"]];
}

-(void)update:(ccTime)delta
{
    self.position = ccpAdd(self.position, ccpMult(vel, delta));
    
    if(self.position.x < -10.0f)
    {
        self.position = ccp(-10.0f, self.position.y);
    }
    else if(self.position.x > 330.0f)
    {
        self.position = ccp(330.0f, self.position.y);
    }
}

-(void)Move:(enum Player_MoveType)type
{
    if(type == Player_Move_Left) vel = ccp(-100.0f, 0.0f);
    else if(type == Player_Move_Right) vel = ccp(100.0f, 0.0f);
    else if(type == Player_Move_None) vel = ccp(0.0f, 0.0f);
}

-(CGRect) boundingBox
{
    CGRect re = [rect boundingBox];
    re.origin = ccpAdd(re.origin, self.position);
    re.origin = ccpAdd(re.origin, rect.position);
    return re;
}

-(void)dealloc
{
    [super dealloc];
}

@end
