//
//  SoundTest_Scene.m
//  cocos2d_UnitTest
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "SoundTest_Scene.h"
#import "SoundTest_Layer.h"

@implementation SoundTest_Scene

-(id)init
{
    self = [super init];
    
    CCLayer* layer = [SoundTest_Layer node];
    layer.position = ccp(0,0);
    [self addChild:layer];
    
    return self;
}

@end
