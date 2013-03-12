//
//  BlockManager.h
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "Block.h"

@interface BlockManager : CCNode
{
    NSMutableArray* _blockArray;
    ccTime _time;
    ccTime _period;
}

@property (nonatomic, readwrite, assign)NSMutableArray* blockArray;
-(void)update:(ccTime)delta;
-(void)RemoveBlock:(Block*)block;
@end
