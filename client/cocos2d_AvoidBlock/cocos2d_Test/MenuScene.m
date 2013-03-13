//
//  MenuScene.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "MenuScene.h"
#import "MenuLayer.h"

@implementation MenuScene

-(id) init
{
    self = [super init];
    
    CCLayer* menuLayer = [MenuLayer node];
    [self addChild:menuLayer];
    
    return self;
}

-(void) dealloc
{
    [super dealloc];
}

@end
