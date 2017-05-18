#include "stdafx.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "Camera.h"

extern BattleEnemy* g_battleenemy;

enum {

	Stand_anim,
	Walk_anim,  //����
	Run_anim,  //����
	

};


BattlePlayer::BattlePlayer()
{
	All.SetAmbinetLight({ 0.2f,0.2f,0.2f });
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
}


BattlePlayer::~BattlePlayer()
{

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

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

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

void BattlePlayer::Particle()
{
	/*if (m_particle == nullptr)
	{
	return;
	}*/

	//�p�[�e�B�N���̐���
	m_particle = NewGO<CParticleEmitter>(0);
	m_particle->Init(m_random, g_gameCamera->GetCamera(),
	{
		"Assets/Particle/burn.png",		//!<�e�N�X�`���̃t�@�C���p�X�B
		{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
		0.3f,											//!<�����B�P�ʂ͕b�B
		0.5f,											//!<�������ԁB�P�ʂ͕b�B
		3.5f,											//!<�p�[�e�B�N���̕��B
		3.5f,											//!<�p�[�e�B�N���̍����B
		{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
		{ 0.0f, 0.0f,0.0f },							//!<�����x�̃����_�����B
		{ 1.0f, 1.0f, 1.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{
			{ 0.0f, 0.0f,0.25f, 0.25f },//0.25,0.5,0.75,1U��V�̈ʒu
			{ 0.0f, 0.0f, 0.0f, 0.0f }, //X,Y,X,Y
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		1,												//!<UV�e�[�u���̃T�C�Y�B
		{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
		true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.3f,											//!<�t�F�[�h���鎞�ԁB
		2.0f,											//!<�����A���t�@�l�B
		true,											//!<�r���{�[�h�H
		3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,												//!<0�����������A1���Z�����B
		{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
	},
		g_battleenemy->Getpos());




}


void BattlePlayer::ParticleDelete()
{
	DeleteGO(m_particle);
	m_particle = nullptr;


}