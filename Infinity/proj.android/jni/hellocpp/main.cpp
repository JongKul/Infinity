#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include "Facebook_Manager.h"
#include <jni.h>
#include <android/log.h>
#include "main.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;


// get env and cache it


extern "C"
{


jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);
    LOGD("hello world!!");
    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
	LOGD("hello world!! init!!!");
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();
          
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
		CCNotificationCenter::sharedNotificationCenter()->postNotification(
				EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}


JNIEXPORT void JNICALL Java_game_mobile_infinity_FacebookManager_jniCallbackLogin(JNIEnv*  env, jobject thiz, jboolean ret)
{
	Facebook_Manager::sharedInstance()->Callback_Login((bool)(ret == JNI_TRUE));
}

JNIEXPORT void JNICALL Java_game_mobile_infinity_FacebookManager_jniSetMyAccount(JNIEnv*  env, jobject thiz, jstring jname , jstring jid)
{
	LOGD("Java_game_mobile_infinity_FacebookManager_jniSetMyAccount");
	const char *name = env->GetStringUTFChars(  jname, 0);
	const char *id = env->GetStringUTFChars(  jid, 0);

	 CCString* cName = CCString::createWithFormat("%s",name);
	 CCString* cfbID = CCString::createWithFormat("%s",id);
	 Facebook_Manager::sharedInstance()->SetMyAccount(cName, cfbID);


	env->ReleaseStringUTFChars(  jname, name);
	env->ReleaseStringUTFChars(  jid, id);

	JNI_Friend();
}

JNIEXPORT void JNICALL Java_game_mobile_infinity_FacebookManager_jniAddFriend(JNIEnv*  env, jobject thiz, jstring jname , jstring jid)
{


	const char *name = env->GetStringUTFChars(  jname, 0);
	const char *id = env->GetStringUTFChars(  jid, 0);


	 CCString* cName = new CCString(name);
	 CCString* cfbID =new  CCString(id);

	 Facebook_Manager::sharedInstance()->AddFriend(cName, cfbID);


	env->ReleaseStringUTFChars(  jname, name);
	env->ReleaseStringUTFChars(  jid, id);
}

JNIEXPORT void JNICALL Java_game_mobile_infinity_FacebookManager_jniCallbackPicture(JNIEnv*  env, jobject thiz, jstring jid , jbyteArray  jimage)
{

	const char *id = env->GetStringUTFChars(  jid, 0);

	CCString* cfbID = CCString::createWithFormat("%s",id);

	int len  = env->GetArrayLength(jimage);
	char* byteData = (char*)malloc(len);
	env->GetByteArrayRegion(jimage,0,len,(jbyte*)byteData);


	CCImage* imf = new CCImage();
	imf->initWithImageData(byteData,len);
	imf->autorelease();

	CCTexture2D* pTexture = new CCTexture2D();
	pTexture->initWithImage(imf);
	pTexture->autorelease();

	CCSprite *sprit = CCSprite::createWithTexture(pTexture);
	Facebook_Manager::sharedInstance()->Callback_Picture(cfbID, sprit);


	env->ReleaseStringUTFChars(  jid, id);

}





JNIEXPORT void JNICALL JNI_ShowAlert(const char* message)
{
	JniMethodInfo minfo;
		bool isHave =JniHelper::getStaticMethodInfo( minfo,"game/mobile/infinity/Helper" ,"getInstance", "()Lgame/mobile/infinity/Helper;" );
		if (!isHave) {
			LOGD("jni:method no found.");
		}
		jobject instance = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
		if (instance==0) {
				LOGD("instance is empty");
		}
		isHave =JniHelper::getMethodInfo(minfo, "game/mobile/infinity/Helper","alert", "(Ljava/lang/String;)V" );
		if (!isHave) {
			LOGD("jni:method no found.");
		}

		jstring jstr = minfo.env->NewStringUTF(  message);
		minfo.env->CallVoidMethod( instance,minfo.methodID,jstr);


}
void JNI_GetToken(char* buf )
{
	LOGD("jni:JNI_GetToken");
	JniMethodInfo minfo;
	bool isHave =JniHelper::getStaticMethodInfo( minfo,"game/mobile/infinity/Helper" ,"getInstance", "()Lgame/mobile/infinity/Helper;" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	jobject instance = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	if (instance==0) {
			LOGD("instance is empty");
	}
	isHave =JniHelper::getMethodInfo(minfo, "game/mobile/infinity/Helper","getToken", "()Ljava/lang/String;" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	jstring string = (jstring)minfo.env->CallObjectMethod( instance,minfo.methodID);
	const char *id = minfo.env->GetStringUTFChars(  string, 0);
	strcpy(buf,id);
	minfo.env->ReleaseStringUTFChars(  string, id);
}

 void JNI_Login()
{
	JniMethodInfo minfo;
	bool isHave =JniHelper::getStaticMethodInfo( minfo,"game/mobile/infinity/FacebookManager" ,"getInstance", "()Lgame/mobile/infinity/FacebookManager;" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	jobject instance = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	if (instance==0) {
			LOGD("instance is empty");
	}
	isHave =JniHelper::getMethodInfo(minfo, "game/mobile/infinity/FacebookManager","login", "()V" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}

	minfo.env->CallVoidMethod( instance,minfo.methodID);

}

 void JNI_Friend()
{
	LOGD("JNI_Friend");
	JniMethodInfo minfo;
	bool isHave =JniHelper::getStaticMethodInfo( minfo,"game/mobile/infinity/FacebookManager" ,"getInstance", "()Lgame/mobile/infinity/FacebookManager;" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	jobject instance = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	if (instance==0) {
			LOGD("instance is empty");
	}
	isHave =JniHelper::getMethodInfo(minfo, "game/mobile/infinity/FacebookManager","requestFriends", "()V" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	minfo.env->CallVoidMethod( instance,minfo.methodID);
}

 void JNI_MyAccount()
{
	 LOGD("JNI_MyAccount");
	JniMethodInfo minfo;
	bool isHave =JniHelper::getStaticMethodInfo( minfo,"game/mobile/infinity/FacebookManager" ,"getInstance", "()Lgame/mobile/infinity/FacebookManager;" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	jobject instance = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	if (instance==0) {
			LOGD("instance is empty");
	}
	isHave =JniHelper::getMethodInfo(minfo, "game/mobile/infinity/FacebookManager","requestMyAccount", "()V" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	minfo.env->CallVoidMethod( instance,minfo.methodID);

}

 void JNI_Picture( const char* id)
{

	JniMethodInfo minfo;
	bool isHave =JniHelper::getStaticMethodInfo( minfo,"game/mobile/infinity/FacebookManager" ,"getInstance", "()Lgame/mobile/infinity/FacebookManager;" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}
	jobject instance = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	if (instance==0) {
			LOGD("instance is empty");
	}
	isHave =JniHelper::getMethodInfo(minfo, "game/mobile/infinity/FacebookManager","requestPicture", "(Ljava/lang/String;)V" );
	if (!isHave) {
		LOGD("jni:method no found.");
	}

	jstring jstr = minfo.env->NewStringUTF(  id);
	minfo.env->CallVoidMethod( instance,minfo.methodID,jstr);
	minfo.env->DeleteLocalRef(jstr);
}

 void JNI_Invite(const char* id)
{
		JniMethodInfo minfo;
		bool isHave =JniHelper::getStaticMethodInfo( minfo,"game/mobile/infinity/FacebookManager" ,"getInstance", "()Lgame/mobile/infinity/FacebookManager;" );
		if (!isHave) {
			LOGD("jni:method no found.");
		}
		jobject instance = minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
		if (instance==0) {
				LOGD("instance is empty");
		}
		isHave =JniHelper::getMethodInfo(minfo, "game/mobile/infinity/FacebookManager","invite", "(Ljava/lang/String;)V" );
		if (!isHave) {
			LOGD("jni:method no found.");
		}

		jstring jstr = minfo.env->NewStringUTF(  id);
		minfo.env->CallVoidMethod( instance,minfo.methodID,jstr);
		minfo.env->DeleteLocalRef(jstr);
}
}
