//
//  IOS_Facebook.m
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

#import "IOS_Facebook.h"
#import "IOS_Helper.h"

@implementation IOS_Facebook

+(IOS_Facebook*) shared
{
    static IOS_Facebook* instance = nil;
    if(instance == nil)
    {
        instance = [[self alloc] init];
        [[FBSession activeSession]closeAndClearTokenInformation];
    }
    
    return instance;
}

-(void) applicationDidBecomeActive
{
    [[FBSession activeSession] handleDidBecomeActive];
}

-(void)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation
{
    [[FBSession activeSession] handleOpenURL:url];
}

-(void)applicationWillTerminate
{
    [[FBSession activeSession] close];
}

-(void) Facebook_Login
{
    NSArray *permissions = [NSArray arrayWithObjects:@"email",nil];
    [FBSession openActiveSessionWithReadPermissions:permissions
                                       allowLoginUI:YES
                                  completionHandler:^(FBSession *session, FBSessionState state, NSError *error) {
                    
                                      [self Callback_Login];
                                  }];
}

-(void) Callback_Login
{
    if([FBSession activeSession].isOpen)
    {
        NSLog(@"access_token=%@",[FBSession activeSession].accessTokenData.accessToken);
        [self Facebook_MyAccount];
    }
    else
    {
        [[FBSession activeSession] closeAndClearTokenInformation];
        NSLog(@"Login Faile");
    }
}

- (void)Facebook_MyAccount
{
    if (FBSession.activeSession.isOpen)
    {
        [[FBRequest requestForMe] startWithCompletionHandler:
         ^(FBRequestConnection *connection,
           NSDictionary<FBGraphUser> *user,
           NSError *error) {
             [self Callback_MyAccount:connection user:user error:error];
         }];
    }
}

-(void)Callback_MyAccount:(FBRequestConnection*)con user : (NSDictionary<FBGraphUser>*)user error :(NSError*)error
{
    if (!error)
    {
        NSLog(@"name : %@, id : %@", user.name, user.id);
        IOS_Helper::sharedInstance()->ShowAlert(NsToChar(user.name));
    }
    else
    {
        NSLog(@"error : %@", error.localizedFailureReason);
    }
}

@end
