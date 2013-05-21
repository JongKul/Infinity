//
//  Othello_Logic.h
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#ifndef __Infinity__Othello_Logic__
#define __Infinity__Othello_Logic__

#include "cocos2d.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class Match_Map;
class Unit_Base;

class Othello_Logic
{
public:
    static Unit_Base* CreateUnit(int tag);
    static bool Logic_AddUnit(Match_Map* cur_Map, const CCPoint& touchPos, int& x, int& y, int tag);
private:
    static bool Logic_CheckInterUnit(Match_Map* cur_Map, int index_X, int index_Y, int tag);
    static bool Logic_CheckInterUnit_Hori_Right(Match_Map* cur_Map, int index_X, int index_Y, int tag);
    static bool Logic_CheckInterUnit_Hori_Left(Match_Map* cur_Map, int index_X, int index_Y, int tag);
    static bool Logic_CheckInterUnit_Verti_Up(Match_Map* cur_Map, int index_X, int index_Y, int tag);
    static bool Logic_CheckInterUnit_Verti_Down(Match_Map* cur_Map, int index_X, int index_Y, int tag);
    static bool Logic_CheckInterUnit_DirLR_Up(Match_Map* cur_Map, int index_X, int index_Y, int tag); //대각선 \방향임.
    static bool Logic_CheckInterUnit_DirLR_Down(Match_Map* cur_Map, int index_X, int index_Y, int tag); //대각선 \방향임.
    static bool Logic_CheckInterUnit_DirRL_Up(Match_Map* cur_Map, int index_X, int index_Y, int tag); //대각선 /방향임.
    static bool Logic_CheckInterUnit_DirRL_Down(Match_Map* cur_Map, int index_X, int index_Y, int tag); //대각선 /방향임.
    static bool Logic_CheckInterUnit_AfterLogic(Match_Map* cur_Map, vector<int>& list_InterUnit, int index_X, int index_Y, int tag);
};

#endif /* defined(__Infinity__Othello_Logic__) */
