//
//  Scene_Manager.cpp
//  Infinity
//
//  Created by 정 기호 on 13. 4. 1..
//
//

#include "Scene_Manager.h"
#include "GameScene_MainTitle.h"
#include "GameScene_Match.h"
#include "Facebook_Manager.h"

void Scene_Manager::ChangeScene_Match()
{
    ChangeScene_Common(GameScene_Match::create());
}

void Scene_Manager::ChangeScene_MainTitle()
{
    ChangeScene_Common(GameScene_MainTitle::create());
}

void Scene_Manager::ChangeScene_Common(CCScene* scene)
{
    Facebook_Manager::sharedInstance()->SetNullDelegate();
    
    CCTransitionScene *transition;
#pragma region Transition Effect
    //transition = CCTransitionPageTurn::create(3.0f, scene, false);//책 넘기듯이 페이지를 넘기는 효과.
    //transition = CCTransitionRotoZoom::create(3.0f, scene); //원래 그림이 돌면서 없어지고 다음씬이 돌면서 나타난다.
    //transition = CCTransitionJumpZoom::create(3.0f, scene); //점프하면서 촐삭대면서 씬이 바뀜.
    //transition = CCTransitionMoveInL::create(3.0f, scene); //다음씬이 옆에서 들어온다.
    //transition = CCTransitionShrinkGrow::create(3.0f, scene); //원래씬은 작아지고 다음씬이 커지면서 바뀐다.
    //transition = CCTransitionFlipX::create(3.0f, scene, kOrientationLeftOver); //Y축기준으로 회전하면서 씬이 바뀐다.
    transition = CCTransitionFade::create(3.0f, scene); //일반적인 Fade In,Out 효과.
    //transition = CCTransitionCrossFade::create(3.0f, scene); //원래씬과 다음씬이 서로 페이드되면서 바뀐다.
    //transition = CCTransitionTurnOffTiles::create(1.5f, scene); //씬이 타일 단위로 쪼개져서 막 나타난다.
    //transition = CCTransitionSplitCols::create(3.0f, scene);//Scene을 짤라서 막 이동하면서 바뀐다.
    //transition = CCTransitionFadeTR::create(3.0f, scene);//대각선방향으로 씬이 점진적으로 나온다.
    //transition = CCTransitionProgressRadialCCW::create(3.0f, scene); //프로그래스바처럼 반시계방향으로 화면이 나온다.
#pragma endregion
    CCDirector::sharedDirector()->replaceScene(transition);
}