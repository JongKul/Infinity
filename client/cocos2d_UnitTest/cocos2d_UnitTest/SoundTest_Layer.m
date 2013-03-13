//
//  SoundTest_Layer.m
//  cocos2d_UnitTest
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "SoundTest_Layer.h"
#import "SimpleAudioEngine.h"

@implementation SoundTest_Layer

-(id)init
{
    self = [super init];
    
    SimpleAudioEngine* audio = [SimpleAudioEngine sharedEngine];
    
    [audio playBackgroundMusic:@"bg.mp3"];
     [audio playEffect:@"effect.mp3"];
    
    
    return self;
}

@end
