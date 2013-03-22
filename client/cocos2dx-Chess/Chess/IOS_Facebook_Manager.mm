//
//  IOS_Facebook_Manager.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 21..
//
//

#include "Facebook_Manager.h"
#include "IOS_Facebook_Manager.h"
#include "IOS_Helper.h"
#import "IOS_Facebook.h"

IOS_Facebook_Manager* IOS_Facebook_Manager::sharedInstance()
{
    static IOS_Facebook_Manager instance;
    return &instance;
}


void IOS_Facebook_Manager::Login()
{
    [[IOS_Facebook shared] Facebook_Login];
}

void IOS_Facebook_Manager::SetMyAccount(const char* name, const char *fbID)
{
    CCLog(name);
    CCLog(fbID);
    
    CCString* cName = CCString::createWithFormat("%s",name);
    CCString* cfbID = CCString::createWithFormat("%s",fbID);
    Facebook_Manager::sharedInstance()->SetMyAccount(cName, cfbID);
    
    [[IOS_Facebook shared] Facebook_Friends];
}

void IOS_Facebook_Manager::AddFriend(const char *name, const char *fbID)
{
    CCString* cName = CCString::createWithFormat("%s",name);
    CCString* cfbID = CCString::createWithFormat("%s",fbID);
    
    Facebook_Manager::sharedInstance()->AddFriend(cName, cfbID);
}

void IOS_Facebook_Manager::Callback_Login(bool ret)
{
    Facebook_Manager::sharedInstance()->Callback_Login(ret);
}

void IOS_Facebook_Manager::GetPicture(cocos2d::CCString *fbID)
{
    [[IOS_Facebook shared] Facebook_Picture: CharToNs(fbID->getCString())];
}

void IOS_Facebook_Manager::Callback_Picture(const char *fbID, void *picture)
{
    UIImage* native = (UIImage*)picture;
    CCImage *imf =new CCImage();
    NSData *imgData = UIImagePNGRepresentation(native);
    NSUInteger len = [imgData length];
    Byte *byteData = (Byte*)malloc(len);
    memcpy(byteData, [imgData bytes], len);
    
    imf->initWithImageData(byteData,imgData.length);
    imf->autorelease();
    CCTexture2D* pTexture = new CCTexture2D();
    pTexture->initWithImage(imf);
    pTexture->autorelease();
    
    CCSprite *sprit = CCSprite::createWithTexture(pTexture);
    Facebook_Manager::sharedInstance()->Callback_Picture(CCString::createWithFormat("%s",fbID), sprit);
}

void IOS_Facebook_Manager::Post()
{
    [[IOS_Facebook shared] Facebook_Post];
}