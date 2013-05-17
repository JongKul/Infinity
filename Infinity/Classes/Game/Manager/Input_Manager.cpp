//
//  Input_Manager.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 5. 18..
//
//

#include "Input_Manager.h"

bool Input_Manager::GetInputEnable()
{
    return SharedInstance()->enableInput;
}
void Input_Manager::SetInputEnable(bool sig)
{
    SharedInstance()->enableInput = sig;
}
Input_Manager* Input_Manager::SharedInstance()
{
    static Input_Manager instance;
    return &instance;
}