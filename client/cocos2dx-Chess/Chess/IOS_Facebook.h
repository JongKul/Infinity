//
//  IOS_Facebook.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

#import <Foundation/Foundation.h>
#import <FacebookSDK/FacebookSDK.h>

@interface IOS_Facebook : NSObject

+(IOS_Facebook*) shared;

-(void)applicationDidBecomeActive;
-(void)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;
-(void)applicationWillTerminate;

-(void)Facebook_Login;
-(void)Callback_Login;

-(void)Facebook_MyAccount;
-(void)Callback_MyAccount:(FBRequestConnection*)con user : (NSDictionary<FBGraphUser>*)user error :(NSError*)error;

@end
