//
//  IOS_Helper.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 20..
//
//

#import <Foundation/Foundation.h>
#import "IOS_Helper.h"
#import "IOS_Native.h"
#import "GameUI_MainTitle.h"

IOS_Helper* IOS_Helper::sharedInstance()
{
    static IOS_Helper instance;
    return &instance;
}

void IOS_Helper::ShowAlert(const char* str)
{   
    [IOS_Native ShowAlert:CharToNs(str)];
}

/*
void IOS_Helper::FacebookPicture(void *picture)
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
    sprit->setPosition(ccp(100,100));
    
    //ui->Facebook_Picture(sprit);
}*/