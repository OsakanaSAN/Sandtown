#include "stdafx.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleScene.h"
#include "Camera.h"
#include "Player.h"
#include "HUD.h"
extern BattleEnemy* g_battleenemy;
extern Player* g_player;
enum {

	Stand_anim,
	Walk_anim,  //����
	Run_anim,  //����
	Jump,
	Dameg,

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
	
}


BattlePlayer::~BattlePlayer()
{

}


bool BattlePlayer::Start()
{
	skinModelData.LoadModelData("Assets/modelData/kano.X", &Animation);
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&All);

	characterController.Init(0.5f, 1.0f, position);



	Animation.PlayAnimation(Run_anim, 0.1f);

	Animation.SetAnimationEndTime(Stand_anim, 0.8);
	


	Animation.SetAnimationLoopFlag(Run_anim, true);
	Animation.SetAnimationLoopFlag(Stand_anim, true); //�X�^���h�A�j���[�V���������[�v������

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	scale.Scale(0.4);
	m_random.Init((unsigned long)time(NULL));
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
			Animation.SetAnimationSpeedRate(2);
			Animation.SetAnimationEndTime(Run_anim, 2.0f);
			
			g_gameCamera->BattleCamera();

		}

		else if (diff.Length() < 1.1)
		{
			IsSetPoint = true;
			Animation.SetAnimationLoopFlag(Run_anim, false);


			Animation.PlayAnimation(Stand_anim, 0.1f);
			Animation.SetAnimationLoopFlag(Stand_anim, true); //�X�^���h�A�j���[�V���������[�v������


			
			
		}

		skinModel.Update(BakPositon, m_rotation,scale);

		//�A�j���[�V�����̍X�V
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
		//�A�j���[�V�����̍X�V
		Animation.Update(1.0f / 60.0f);
	}

	else if (IsSetPoint == true)
	{

		Time += GameTime().GetFrameDeltaTime();
		//�A�j���[�V�����̍X�V
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
	//�^�[�����̃A�j���[�V����
	if (!IsStand) {

		//�U����
		if (IsAttack) {
			IsAnimend = false;
			Animation.PlayAnimation(Jump_anim, 0.05f);
			Animation.SetAnimationLoopFlag(Jump_anim,false);
			Animation.SetAnimationSpeedRate(2);

			IsStand = true;

		}
		//�_���[�W��H�������
		else if (IsDamage)
		{
			IsAnimend = false;
			Animation.PlayAnimation(Dameg_anim, 0.1f);
			Animation.SetAnimationLoopFlag(Dameg_anim, false);
			Animation.SetAnimationSpeedRate(1);

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
		Animation.SetAnimationSpeedRate(1);
		IsAttack = false;
		IsDamage = false;
		IsAnimend = true;
	}
	

	//�A�j���[�V�����̍X�V
	Animation.Update(1.0f / 60.0f);

}

void BattlePlayer::Particle(CVector3 target)
{
	if (m_particle != nullptr) { return;}
	switch (currentParticle)
	{
	case ATTACK://�U��


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
			{ 0.0f, 0.0f,0.0f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 0.0f,0.0f },							//!<�����x�̃����_�����B
			{ 1.0f, 1.0f,1.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
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
			target);//�p�[�e�B�N���𐶐�������W�@CVector3�^�H
		break;
	case HEAL://��


		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		//m_random.Init((unsigned long)time(NULL));
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/Particle/Heal.tga",		//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
			0.3f,											//!<�����B�P�ʂ͕b�B
			0.5f,											//!<�������ԁB�P�ʂ͕b�B
			0.5f,											//!<�p�[�e�B�N���̕��B
			0.5f,											//!<�p�[�e�B�N���̍����B
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
			{ 0.0f, 1.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);//�p�[�e�B�N���𐶐�������W�@CVector3�^�H
		break;
	
	}
}


void BattlePlayer::ParticleDelete()
{
	
	DeleteGO(m_particle);
	m_particle = nullptr;
	


}