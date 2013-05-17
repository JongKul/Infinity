//
//  Input_Manager.h
//  Infinity
//
//  Created by 정 기호 on 13. 5. 18..
//
//

#ifndef __Infinity__Input_Manager__
#define __Infinity__Input_Manager__

class Input_Manager
{
public:
    static bool GetInputEnable();
    static void SetInputEnable(bool sig);
    static Input_Manager* SharedInstance();
private:
    bool enableInput;
};

#define ReturnInput() if(Input_Manager::GetInputEnable() == false) return

#endif /* defined(__Infinity__Input_Manager__) */
