//
//  IOS_Native.m
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

#import "IOS_Native.h"
#import "IOS_Facebook.h"

@implementation IOS_Native

+(void) applicationDidBecomeActive
{
    NSLog(@"applicationDidBecomeActive");
    [[IOS_Facebook shared] applicationDidBecomeActive];
}


+ (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation
{
    NSLog(@"application");
    [[IOS_Facebook shared] application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
    return YES;
}

+ (void)applicationWillResignActive:(UIApplication *)application
{
    NSLog(@"applicationWillResignActive");
}
+ (void)applicationDidEnterBackground:(UIApplication *)application
{
   NSLog(@"applicationDidEnterBackground"); 
}
+ (void)applicationWillEnterForeground:(UIApplication *)application
{
    NSLog(@"applicationWillEnterForeground");
}
+ (void)applicationWillTerminate:(UIApplication *)application
{
    NSLog(@"applicationWillTerminate");
    [[IOS_Facebook shared] applicationWillTerminate];
}


+(void) ShowAlert:(NSString*)message
{
    UIAlertView *alertDialog;
    
    alertDialog = [[UIAlertView alloc]
                   initWithTitle:@"IOS Native!"
                   message:message
                   delegate:nil
                   cancelButtonTitle: @"OK"
                   otherButtonTitles: nil];
    
    [alertDialog show];
    [alertDialog release];
}

+(void) FacebookLogin
{
    [[IOS_Facebook shared] Facebook_Login];
}

@end
