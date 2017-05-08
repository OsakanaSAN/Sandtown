#include "stdafx.h"
#include "BattlePlayer.h"
#include "Camera.h"



extern Camera*       g_gameCamera;

enum {

	Stand_anim,
	Walk_anim,  //歩く
	Run_anim,  //走る
	

};


BattlePlayer::BattlePlayer()
{
	All.SetAmbinetLight({ 1.0f,1.0f,1.0f });
	IsDamage = false;
	IsAttack = false;
	IsStand = true;
	IsAnimend = true;
	currentAnimSetNo = Stand_anim;
}


BattlePlayer::~BattlePlayer()
{

	/*DeleteGO(this);*/

}


bool BattlePlayer::Start()
{
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&All);

	characterController.Init(0.5f, 1.0f, position);


	//Animation.PlayAnimation(Stand_anim, 0.1f);
	//Animation.SetAnimationEndTime(Run_anim, 0.8);

	//Animation.PlayAnimation(Stand_anim, 0.1f);
	//Animation.SetAnimationEndTime(Run_anim, 0.8);


	/*Animation.SetAnimationEndTime(Attack_anim, 0.5);
	Animation.SetAnimationLoopFlag(Attack_anim, false);
	Animation.SetAnimationEndTime(Damage_anim, 0.5);
	Animation.SetAnimationLoopFlag(Damage_anim, false);*/


	return true;
}


void BattlePlayer::Update()
{
	//All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });
	characterController.Execute(0.03f);

	AnimationSet();

	skinModel.Update(position, m_rotation, CVector3::One);

}


void BattlePlayer::Render(CRenderContext&renderContext)
{

	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

}


void BattlePlayer::AnimationSet()
{
	//ターン制のアニメーション
	if (!IsStand) {
		if (IsAttack) {
			IsAnimend = false;
			Animation.PlayAnimation(Run_anim, 0.05f);

			IsStand = true;

		}
		else if (IsDamage)
		{
			IsAnimend = false;
			Animation.PlayAnimation(Stand_anim, 0.3f);

			IsStand = true;
		}

	}
	else if (!IsAttack && !IsDamage)
	{
		Animation.PlayAnimation(Stand_anim, 0.3f);

		IsStand = false;

	}

	if (!Animation.IsPlay())
	{
		IsAttack = false;
		IsDamage = false;
		IsAnimend = true;
	}
	

	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);

}
