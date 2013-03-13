//
//  PlayLayerUI.h
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface PlayLayerUI : CCNode
{
    CCLabelTTF *count_label;
    CCSprite* blind;
    CCMenu* menu;
}

-(void)Set_Count:(int)count;
-(void)EndGame;

@end
