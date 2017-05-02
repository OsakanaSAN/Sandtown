#include "stdafx.h"
#include "BattlePlayer.h"


extern BattleCamera* g_battleCamera;

enum {

	Stand_anim,
	Attack_anim,
	Damage_anim,

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

	

}


bool BattlePlayer::Start()
{
	skinModelData.LoadModelData("Assets/modelData/cabetu2.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&All);

	characterController.Init(0.5f, 1.0f, position);


	Animation.PlayAnimation(Stand_anim, 0.1f);

	Animation.SetAnimationEndTime(Attack_anim, 0.5);
	Animation.SetAnimationLoopFlag(Attack_anim, false);
	Animation.SetAnimationEndTime(Damage_anim, 0.5);
	Animation.SetAnimationLoopFlag(Damage_anim, false);


	return true;
}


void BattlePlayer::Update()
{
	All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });

	AnimationSet();

	skinModel.Update(position, m_rotation, CVector3::One);

}


void BattlePlayer::Render(CRenderContext&renderContext)
{

	skinModel.Draw(renderContext, g_battleCamera->GetViewMatrix(), g_battleCamera->GetProjectionMatrix());

}


void BattlePlayer::AnimationSet()
{
	//�^�[�����̃A�j���[�V����
	if (!IsStand) {
		if (IsAttack) {
			IsAnimend = false;
			Animation.PlayAnimation(Attack_anim, 0.5);

			IsStand = true;

		}
		else if (IsDamage)
		{
			IsAnimend = false;
			Animation.PlayAnimation(Damage_anim, 0.5);

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
