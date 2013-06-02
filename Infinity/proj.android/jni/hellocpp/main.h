/*
 * main.h
 *
 *  Created on: 2013. 5. 27.
 *      Author: Administrator
 */

#ifndef MAIN_H_
#define MAIN_H_
extern "C"
{

extern void JNI_Login();
extern void JNI_Friend();
extern void JNI_MyAccount();
extern void JNI_Picture(const char* id);
extern void JNI_Invite(const char* id);

extern void JNI_ShowAlert(const char* message);
extern void JNI_GetToken(char* buf );

}


#endif /* MAIN_H_ */
