//
//  PlayLayer.h
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "Player.h"
#import "BlockManager.h"
#import "Block.h"
#import "PlayLayerUI.h"

@interface PlayLayer : CCLayer
{
    CCMenu* _menu;
    Player* player;
    BlockManager* blcokManager;
    PlayLayerUI* ui;
    int fCount;
}

@property (nonatomic,assign) CCMenu* menu;

-(void)update:(ccTime)delta;

@end
