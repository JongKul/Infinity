//
//  BlockManager.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 12..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "BlockManager.h"
#import "Block.h"

@implementation BlockManager

@synthesize blockArray = _blockArray;

-(id)init
{
    self = [super init];
    
    _blockArray = [[NSMutableArray alloc] initWithCapacity:150];
    
    _time = 0.0f;
    _period = 0.1f;
    
    self.position = ccp(0.0f, 0.0f);
    
    NSLog(@"BlockManager");
    
    return self;
}

-(void)dealloc
{
    [_blockArray removeAllObjects];
    [super dealloc];
}

-(void)MakeBlock
{
    if([_blockArray count] >= 149) return;
    
    int blockType = 0;
    int proba = arc4random()%100;
    
    if(proba > 90) blockType = 0;
    else if(proba > 80) blockType = 1;
    else if(proba > 70) blockType = 2;
    else if(proba > 60) blockType = 3;
    else blockType = 4;
    
    Block* block = [Block BlockWithType:blockType];
    block.position = ccp(rand()%3200 *0.1f, 520.0f);
    [self addChild:block];
    [_blockArray addObject:block];
}

-(void)update:(ccTime)delta
{
    _time += delta;
    
    if(_time > _period)
    {
        [self MakeBlock];
        _time = 0.0f;
    }
    
    for(int i = [_blockArray count] - 1; i>= 0; --i)
    {
        Block* block = [_blockArray objectAtIndex:i];
        [block update:delta];
        if(block.position.y < -50.0f)
        {
            [self RemoveBlock: block];
        }
    }
}

-(void)RemoveBlock:(Block *)block
{
    [_blockArray removeObject:block];
    [self removeChild:block];
}

@end
