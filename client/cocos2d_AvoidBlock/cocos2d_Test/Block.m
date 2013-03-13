//
//  Block.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "Block.h"


@implementation Block
@synthesize type = _type;
@synthesize vel = _vel;
@synthesize isLive = _isLive;

-(id)init
{
    self = [super init];
    
    _vel = ccp(0.0f, 0.0f);
    _isLive = YES;
    
    return self;
}
+(id)BlockWithType:(const int) type
{
    return [[[self alloc] InitWithType:type]autorelease];
}
-(id)InitWithType:(const int) type
{
    [self init];
    
    _type = type;
    
    body = [CCSprite spriteWithFile:[NSString stringWithFormat:@"block_%d.png",type]];
    body.position = ccp(0.0f, 0.0f);
    
    rect = [CCSprite spriteWithFile:@"block_bound.png"];
    rect.position = ccp(0.0f, 0.0f);
    rect.visible = NO;
    
    [self addChild:body];
    [self addChild:rect];
    self.position = ccp(0.0f, 0.0f);
    
    return self;
}

-(void) update:(ccTime)delta
{
    _vel = ccpAdd(_vel, ccpMult(ccp(0.0f, -10.0f*30.0f),delta));
    self.position = ccpAdd(self.position, ccpMult(_vel,delta));
}

-(void) revive
{
    
}

-(void) dead
{
    [self setVisible:NO];
}

-(void) setVisible:(BOOL)visible
{
    body.visible = visible;
}
-(BOOL) visible
{
    return body.visible;
}
-(CGRect) boundingBox
{
    CGRect rec = [body boundingBox];
    rec.origin = ccpAdd(rec.origin, self.position);
    return rec;
}
-(void) dealloc
{
    [super dealloc];
}

@end
