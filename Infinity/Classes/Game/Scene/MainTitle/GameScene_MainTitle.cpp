//
//  GameScene_MainTitle.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 19..
//
//

#include "GameScene_MainTitle.h"
#include "GameUI_MainTitle.h"

#pragma region Scene

bool GameScene_MainTitle::init()
{
    CCScene::init();
    
    CCLayer* layer = GameLayer_MainTitle::create();
    this->addChild(layer);
    
    return true;
}

#pragma endregion

#pragma region Layer

bool GameLayer_MainTitle::init()
{
    CCLayer::init();
    
    this->setTouchEnabled(true);
    
    GameUI_MainTitle* ui = GameUI_MainTitle::create();
    ui->SetGameLayer(this);
    this->addChild(ui);
    
    return true;
}


void GameLayer_MainTitle::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    
}

void GameLayer_MainTitle::ChangeScene()
{
    CCDirector::sharedDirector()->setDepthTest(true);
    CCTransitionScene *transition;
    CCScene* scene = GameScene_MainTitle::create();
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
    
    this->setTouchEnabled(false);
}

#pragma endregion