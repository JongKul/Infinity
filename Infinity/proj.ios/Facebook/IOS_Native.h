//
//  IOS_Native.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

@interface IOS_Native : NSObject

+(void) applicationDidBecomeActive;
+(BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication
        annotation:(id)annotation;

+ (void)applicationWillResignActive:(UIApplication *)application;
+ (void)applicationDidEnterBackground:(UIApplication *)application;
+ (void)applicationWillEnterForeground:(UIApplication *)application;
+ (void)applicationWillTerminate:(UIApplication *)application;

+(void) ShowAlert:(NSString*)message;

@end
