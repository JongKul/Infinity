//
//  Block.h
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface Block : CCNode
{
    int _type;
    BOOL _isLive;
    CCSprite* body;
    CCSprite* rect;
    CGPoint _vel;
}

@property (nonatomic, readwrite, assign) int type;
@property (nonatomic, readwrite, assign) CGPoint vel;
@property (nonatomic, readwrite, assign) BOOL isLive;

+(id)BlockWithType:(const int) type;
-(id)InitWithType:(const int) type;

-(void) update:(ccTime)delta;
-(void) revive;
-(void) dead;
-(void) setVisible:(BOOL)visible;
-(BOOL) visible;
-(CGRect) boundingBox;

@end
