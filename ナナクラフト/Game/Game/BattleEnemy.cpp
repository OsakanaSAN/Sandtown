#include "stdafx.h"
#include "BattleEnemy.h"
#include "Camera.h"
#include "HUD.h"
#include "EnemyHUD.h"
#include "Enemy.h"
extern Enemy* g_Enemy;
extern Enemy* g_Enemy2;
extern Enemy* g_Enemy3;


enum {

	Stand_anim,
	Attack_anim,
	Damage_anim,

};

BattleEnemy::BattleEnemy()
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

	IsAttack = false;
	IsDamage = false;
	IsStand = false;
	IsAnimend = true;
	currentAnimSetNo = Stand_anim;


}


BattleEnemy::~BattleEnemy()
{

	if (g_Enemy->GetEnemyState() == Alive)
	{

		g_Enemy->SetActiveFlag(true);
		

	}

	if (g_Enemy2->GetEnemyState() == Alive)
	{
		g_Enemy2->SetActiveFlag(true);

	}
	

	if (g_Enemy3->GetEnemyState() == Alive)
	{
		g_Enemy3->SetActiveFlag(true);
	}
	
	
	
}

bool BattleEnemy::Start()
{
	All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });


	if (g_Enemy->Getenemyhit() && g_Enemy->GetEnemyState() == Alive)
	{
		skinModelData.LoadModelData(g_Enemy->GetenemyName(), &Animation);
		
		ATK = g_Enemy->GetEATK();
		HP = g_Enemy->GetEHp();
		Exp = g_Enemy->GetExp();
		EGold = g_Enemy->GetEGold();

		g_Enemy->SetEnemyState(Dead);
	}
	else if (g_Enemy2->Getenemyhit() && g_Enemy2->GetEnemyState() == Alive)
	{
		skinModelData.LoadModelData(g_Enemy2->GetenemyName(), &Animation);
		
		ATK = g_Enemy2->GetEATK();
		HP = g_Enemy2->GetEHp();
		Exp = g_Enemy2->GetExp();
		EGold = g_Enemy2->GetEGold();
		g_Enemy2->SetEnemyState(Dead);
	}
	else if (g_Enemy3->Getenemyhit() && g_Enemy3->GetEnemyState() == Alive)
	{
		skinModelData.LoadModelData(g_Enemy3->GetenemyName(), &Animation);
		
		ATK = g_Enemy3->GetEATK();
		HP = g_Enemy3->GetEHp();
		Exp = g_Enemy3->GetExp();
		EGold = g_Enemy3->GetEGold();

		g_Enemy3->SetEnemyState(Dead);
	}


	g_Enemy->SetActiveFlag(false);
	g_Enemy2->SetActiveFlag(false);
	g_Enemy3->SetActiveFlag(false);
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&All);	//�f�t�H���g���C�g��ݒ�B



	Animation.PlayAnimation(Stand_anim, 0.1f);

	Animation.SetAnimationEndTime(Attack_anim, 0.5);
	Animation.SetAnimationLoopFlag(Attack_anim, false);
	Animation.SetAnimationEndTime(Damage_anim, 0.5);
	Animation.SetAnimationLoopFlag(Damage_anim, false);

	m_rotation.SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(170.0f));

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	return true;
}



void BattleEnemy::Update()
{
	All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });

	AnimationSet();
	Animation.Update(1.0f / 60.0f);

	skinModel.Update(position, m_rotation, CVector3::One);
}



void BattleEnemy::Render(CRenderContext&renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}



void BattleEnemy::AnimationSet()
{
	//�^�[�����̃A�j���[�V����
	if (!IsStand) {

		//�U�����[�V�����J�n
		if (IsAttack) {

			IsAnimend = false;
			Animation.PlayAnimation(Attack_anim, 0.5);

			IsStand = true;
			g_Hud->Damage(ATK);

		}
		
		//�_���[�W���[�V�����J�n
		else if (IsDamage)
		{
			IsAnimend = false;
			Animation.PlayAnimation(Damage_anim, 0.5);

			IsStand = true;
		}

	}



	if (!Animation.IsPlay())
	{
		Animation.PlayAnimation(Stand_anim, 0.3f);
		IsStand = false;
		IsAttack = false;
		IsDamage = false;
		IsAnimend = true;
	}


	//�A�j���[�V�����̍X�V
	Animation.Update(1.0f / 60.0f);
}


void BattleEnemy::Delete()
{
	DeleteGO(this);
}
void BattleEnemy::EnemyParticle(CVector3 target)
{

	if (m_particle != nullptr) { return; }
	//�p�[�e�B�N���̐���
	m_particle = NewGO<CParticleEmitter>(0);

	m_particle->Init(m_random, g_gameCamera->GetCamera(),
	{
		"Assets/Particle/burn.png",		//!<�e�N�X�`���̃t�@�C���p�X�B
		{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
		0.3f,											//!<�����B�P�ʂ͕b�B
		2.5f,											//!<�������ԁB�P�ʂ͕b�B
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

}
void BattleEnemy::EnemyParticleDelete()
{
	DeleteGO(m_particle);
	m_particle = nullptr;
}