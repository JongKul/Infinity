//
//  MyCocos2DClass.m
//  cocos2d_Test
//
//  Created by 정 기호 on 13. 3. 11..
//  Copyright 2013년 정 기호. All rights reserved.
//

#import "MyCocos2DClass.h"


@implementation MyCocos2DClass
// Helper class method that creates a Scene with the HelloWorldLayer as the only child.
+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	MyCocos2DClass *layer = [MyCocos2DClass node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

//
-(id) init
{
	if( (self=[super init])) {
        
		// ask director for the window size
		CGSize size = [[CCDirector sharedDirector] winSize];
        
		CCSprite *background;
        background = [CCSprite spriteWithFile:@"Icon.png"];
		background.position = ccp(size.width * 0.5f, size.height * 0.5f);
        
		// add the label as a child to this Layer
		[self addChild: background];
	}
	
	return self;
}
@end
