#include "stdafx.h"
#include "BattlePlayer.h"
#include "Camera.h"




enum {

	Stand_anim,
	Walk_anim,  //����
	Run_anim,  //����
	

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
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&All);

	characterController.Init(0.5f, 1.0f, position);


	//Animation.PlayAnimation(Stand_anim, 0.1f);
	Animation.SetAnimationEndTime(Run_anim, 0.8);

	//Animation.SetAnimationEndTime(Attack_anim, 0.5);
	Animation.SetAnimationLoopFlag(Run_anim, false);
	Animation.SetAnimationEndTime(Stand_anim, 0.1f);
	Animation.SetAnimationLoopFlag(Stand_anim, false);


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
	//�^�[�����̃A�j���[�V����
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
	

	//�A�j���[�V�����̍X�V
	Animation.Update(1.0f / 60.0f);

}
