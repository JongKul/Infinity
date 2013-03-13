//
//  ScheduleTest_Scene.m
//  cocos2d_UnitTest
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "ScheduleTest_Scene.h"
#import "ScheduleTest_Layer.h"

@implementation ScheduleTest_Scene

-(id)init
{
    self = [super init];
    
    CCLayer* layer = [ScheduleTest_Layer node];
    layer.position = ccp(0,0);
    [self addChild:layer];
    
    return self;
}

@end
