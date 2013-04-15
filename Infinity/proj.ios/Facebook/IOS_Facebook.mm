//
//  IOS_Facebook.m
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

#import "IOS_Facebook.h"
#import "IOS_Helper.h"
#include "IOS_Facebook_Manager.h"

@implementation IOS_Facebook

+(IOS_Facebook*) shared
{
    static IOS_Facebook* instance = nil;
    if(instance == nil)
    {
        instance = [[self alloc] init];
        //[[FBSession activeSession]closeAndClearTokenInformation];
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
        NSLog(@"Login Faile");
        [[FBSession activeSession] closeAndClearTokenInformation];
        IOS_Facebook_Manager::sharedInstance()->Callback_Login(false);
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
        IOS_Facebook_Manager::sharedInstance()->SetMyAccount(NsToChar(user.name), NsToChar(user.id));
    }
    else
    {
        NSLog(@"error : %@", error.localizedFailureReason);
        IOS_Facebook_Manager::sharedInstance()->Callback_Login(false);
    }
}

-(void)Facebook_Friends
{
    if (FBSession.activeSession.isOpen)
    {
    [[FBRequest requestForMyFriends] startWithCompletionHandler:^(FBRequestConnection *connection, NSArray<FBGraphUser> *result, NSError *error)
    {
        if(error == nil)
        {
            NSArray *data = [result objectForKey:@"data"];
        
            for (FBGraphObject<FBGraphUser> *fri in data)
            {
                NSString* addName = [[NSString alloc] initWithFormat:@"%@%@",fri.last_name,fri.first_name];
                [addName retain];
                IOS_Facebook_Manager::sharedInstance()->AddFriend(NsToChar(addName), NsToChar(fri.id));
            }
            IOS_Facebook_Manager::sharedInstance()->Callback_Login(true);
        }
        else
        {
            NSLog(@"error : %@", error.localizedFailureReason);
            IOS_Facebook_Manager::sharedInstance()->Callback_Login(false);
        }
    }];
    }
}

-(void)Facebook_Picture:(NSString *)fbID
{
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"https://graph.facebook.com/%@/picture?type=normal", fbID]];
    dispatch_queue_t downloader = dispatch_queue_create("PicDownloader", NULL);
    dispatch_async(downloader,
                   ^{
                       NSData *data = [NSData dataWithContentsOfURL:url];
                       UIImage *image = [UIImage imageWithData:data];
                       dispatch_async(dispatch_get_main_queue(), ^{
                           if(image != nil)
                           {
                               IOS_Facebook_Manager::sharedInstance()->Callback_Picture(NsToChar(fbID), image);
                           }
                           dispatch_release(dispatch_get_main_queue());
                       });
                   });
}

-(void)Facebook_Invite:(NSString *)fbID
{
    NSMutableDictionary* params = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                   @"Othello Friends Invite", @"title",
                                   @"Come check out my app", @"message",
                                   fbID, @"to", nil];
    
    [FBWebDialogs presentDialogModallyWithSession:[FBSession activeSession] dialog:@"apprequests" parameters:params handler:nil];
}

-(void)Facebook_Post
{
    NSMutableDictionary *params =
    [NSMutableDictionary dictionaryWithObjectsAndKeys:
     @"Facebook SDK for iOS", @"name",
     @"Build great social apps and get more installs.", @"caption",
     @"The Facebook SDK for iOS makes it easier and faster to develop Facebook integrated iOS apps.", @"description",
     @"https://developers.facebook.com/ios", @"link",
     @"https://raw.github.com/fbsamples/ios-3.x-howtos/master/Images/iossdk_logo.png", @"picture",
     nil];
    [FBWebDialogs presentFeedDialogModallyWithSession:[FBSession activeSession]
                                           parameters:params
                                              handler:
     ^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
     }
     ];
}

@end
