#include "stdafx.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleScene.h"
#include "Camera.h"
#include "Player.h"
#include "HUD.h"
//extern BattleEnemy* g_battleenemy;
//extern Player* g_player;
//enum {
//
//	Stand_anim,
//	Walk_anim,  //歩く
//	Run_anim,  //走る
//	Jump,
//	Dameg,
//
//};

enum ANIME {
	Stand_anim,
	Dameg_anim,
	Run_anim,
	Attack_anim,


};


BattlePlayer::BattlePlayer()
{
	All.SetAmbinetLight({ 0.8f,0.8f,0.8f });
	All.SetDiffuseLightDirection(0, { 0.0f, -0.707f, 0.707f });
	All.SetDiffuseLightColor(0, { 0.3f, 0.3f, 0.3f, 1.0f });
	All.SetDiffuseLightDirection(1, { 0.0f, 0.707f, 0.707f });
	All.SetDiffuseLightColor(1, { 0.1f, 0.1f, 0.1f, 1.0f });
	All.SetDiffuseLightDirection(2, { 0.0f, -0.707f, -0.707f });
	All.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	All.SetDiffuseLightDirection(3, { 0.0f, 0.707f, -0.707f });
	All.SetDiffuseLightColor(3, { 0.1f, 0.1f, 0.1f, 1.0f });
	IsDamage = false;
	IsAttack = false;
	IsStand = true;
	IsAnimend = true;
	currentAnimSetNo = Stand_anim;
	ATK = g_Hud->GetATK();
	HP = g_Hud->GetHP();
	
}


BattlePlayer::~BattlePlayer()
{

}


bool BattlePlayer::Start()
{
	skinModelData.LoadModelData("Assets/modelData/Knight.X", &Animation);
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&All);

	characterController.Init(0.5f, 1.0f, position);



	Animation.PlayAnimation(Run_anim, 0.1f);

	//Animation.SetAnimationEndTime(Stand_anim, 0.8);
	



	Animation.SetAnimationLoopFlag(Run_anim, true);
	Animation.SetAnimationLoopFlag(Stand_anim, true); //スタンドアニメーションをループさせる

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	scale.Scale(0.4);

	return true;
}


void BattlePlayer::Update()
{
	
	
	if (IsSetPoint == false)
	{
		CVector3 diff = BakPositon;

		diff.Subtract(position);


		if (diff.Length() > 1)
		{

			BakPositon.z += 0.1f;

			Animation.SetAnimationSpeedRate(4.5);

			Animation.SetAnimationEndTime(Run_anim, 2.0f);
			
			g_gameCamera->BattleCamera();

		}

		else if (diff.Length() < 1.1)
		{
			IsSetPoint = true;
			Animation.SetAnimationLoopFlag(Run_anim, false);

			Animation.SetAnimationSpeedRate(0.3);
			Animation.PlayAnimation(Stand_anim, 0.1f);
			Animation.SetAnimationLoopFlag(Stand_anim, true); //スタンドアニメーションをループさせる


			
			
		}

		skinModel.Update(BakPositon, m_rotation,scale);

		//アニメーションの更新
		Animation.Update(1.0f / 60.0f);

		
		


	}

	else if (Time > 0.5 && IsStop == true)
	{
		IsStop = false;
		g_battleScene->IsBattleStrat();
		
	}

	else if(IsStop == false)
	{

		//characterController.Execute(0.03f);
		AnimationSet();
		skinModel.Update(BakPositon, m_rotation, scale);
		//アニメーションの更新
		Animation.Update(1.0f / 60.0f);
	}

	else if (IsSetPoint == true)
	{

		Time += GameTime().GetFrameDeltaTime();
		//アニメーションの更新
		Animation.Update(1.0f / 60.0f);
		skinModel.Update(BakPositon, m_rotation, scale);

	}
		
	
}


void BattlePlayer::Render(CRenderContext&renderContext)
{

	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

}


void BattlePlayer::AnimationSet()
{
	//ターン制のアニメーション
	if (!IsStand) {

		//攻撃時
		if (IsAttack) {
			IsAnimend = false;
			Animation.PlayAnimation(Attack_anim, 0.05f);
			Animation.SetAnimationLoopFlag(Attack_anim,false);
			Animation.SetAnimationSpeedRate(1);

			IsStand = true;

		}
		//ダメージを食らった時
		else if (IsDamage)
		{
			IsAnimend = false;
			Animation.PlayAnimation(Dameg_anim, 0.1f);
			Animation.SetAnimationLoopFlag(Dameg_anim, false);
			Animation.SetAnimationSpeedRate(0.7);

			IsStand = true;
		}

	}

	else if (!IsAttack && !IsDamage)
	{

		IsStand = false;

	}

	if (!Animation.IsPlay())
	{
		
		Animation.PlayAnimation(Stand_anim, 0.1f);
		
		Animation.SetAnimationLoopFlag(Stand_anim, true);
		Animation.SetAnimationSpeedRate(0.3);
		IsAttack = false;
		IsDamage = false;
		IsAnimend = true;
	}
	

	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);

}