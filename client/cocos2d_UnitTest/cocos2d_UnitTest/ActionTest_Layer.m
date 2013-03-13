//
//  ActionTest_Layer.m
//  cocos2d_UnitTest
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "ActionTest_Layer.h"


@implementation ActionTest_Layer

-(id)init
{
    self = [super init];
    
    CCSprite* sprite = [CCSprite spriteWithFile:@"Icon.png"];
    sprite.anchorPoint = ccp(0.5f, 0.5f);
    sprite.position = ccp(100.0f, 100.0f);
    [self addChild:sprite];
    
    /*
    CCAction* move = [CCMoveBy actionWithDuration:2.0f position:ccp(100,100)];
    [sprite runAction:move];
    //*/
    
    /*
    CCAction* scale = [CCScaleBy actionWithDuration:2.0f scale:2.0f];
    [sprite runAction:scale];
    //*/
    
    /*
    CCAction* rotate = [CCRotateBy actionWithDuration:2.0f angle:270.0f];
    [sprite runAction:rotate];
    //*/
    
    /*
    CCAction* blink = [CCBlink actionWithDuration:2.0f blinks:10];
    [sprite runAction:blink];
    //*/
    
    /*
    CCAction* fadeIn = [CCFadeIn actionWithDuration:3.0f];
    [sprite runAction:fadeIn];
    //*/
    
    /*
    CCAction* fadeOut = [CCFadeOut actionWithDuration:3.0f];
    [sprite runAction:fadeOut];
    //*/
    
    /*
    CCAction* tint = [CCTintTo actionWithDuration:3.0f red:255 green:0 blue:0];
    [sprite runAction:tint];
    //*/
    
    /*
    CCBlink* blink = [CCBlink actionWithDuration:2.0f blinks:10];
    CCAction* repeat = [CCRepeatForever actionWithAction:blink];
    [sprite runAction:repeat];
    //*/
    
    /*
    CCRotateBy* rotate = [CCRotateBy actionWithDuration:0.5f angle:360.0f];
    CCRepeat* repeatRotate = [CCRepeat actionWithAction:rotate times:10];
    CCDelayTime* delay = [CCDelayTime actionWithDuration:3.0f];
    CCMoveBy* move_Go = [CCMoveBy actionWithDuration:2.0f position:ccp(100,100)];
    CCMoveBy* move_Back = [CCMoveBy actionWithDuration:2.0f position:ccp(-100,-100)];
    
    CCSequence* sequence = [CCSequence actions:repeatRotate, delay, move_Go, move_Back, nil];
    [sprite runAction:sequence];
    //*/
    
    /*
    CCRotateBy* rotate = [CCRotateBy actionWithDuration:0.5f angle:360.f];
    CCRepeat* repeat = [CCRepeat actionWithAction:rotate times:10];
    CCMoveBy* move = [CCMoveBy actionWithDuration:2.0f position:ccp(150, 200)];
    CCSpawn* spawn = [CCSpawn actions:repeat, move, nil];
    [sprite runAction:spawn];
    //*/
    
    /*
    CCRotateBy* rotate = [CCRotateBy actionWithDuration:0.5f angle:360.0f];
    CCRepeat* repeat = [CCRepeat actionWithAction:rotate times:3];
    CCSpawn* spawn = [CCSpawn actions:repeat, nil];
    CCActionInterval* reverse = [spawn reverse];
    CCSequence* sequence = [CCSequence actions:repeat, reverse, nil];
    [sprite runAction:sequence];
    //*/
    
    CCSprite* child = [CCSprite spriteWithFile:@"Icon.png"];
    child.position = ccp(30,-30);
    [sprite addChild:child];
    
    sprite.anchorPoint = ccp(0.0f,0.5f);
    
    return self;
}

@end
