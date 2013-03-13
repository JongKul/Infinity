//
//  ScheduleTest_Layer.m
//  cocos2d_UnitTest
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "ScheduleTest_Layer.h"

@implementation ScheduleTest_Layer

-(id)init
{
    self = [super init];
    
    CCSprite* sprite = [CCSprite spriteWithFile:@"Icon.png"];
    sprite.position = ccp(100,100);
    [self addChild:sprite];
    
    //[self schedule:@selector(Schedule_Method) interval:1.0f/30.0f];
    
    [self scheduleUpdate];
    
    return self;
}

-(void)update:(ccTime)delta
{
    NSLog(@"update");
}

-(void)Schedule_Method
{
    NSLog(@"Schedule_Method");
}

@end
