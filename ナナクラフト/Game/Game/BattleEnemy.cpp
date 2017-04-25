#include "stdafx.h"
#include "BattleEnemy.h"

extern BattleCamera* g_battleCamera;

enum {

	Stand_anim,
	Attack_anim,
	Damage_anim,

};

BattleEnemy::BattleEnemy()
{
	All.SetAmbinetLight({ 1.0f,1.0f,1.0f });

	IsAttack = false;
	IsDamage = false;
	IsStand = true;
	IsAnimend = true;
	currentAnimSetNo = Stand_anim;



}


BattleEnemy::~BattleEnemy()
{
	/*DeleteGO(this);*/
}

bool BattleEnemy::Start()
{
	All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });


	skinModelData.LoadModelData("Assets/modelData/cabetu2.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&All);	//デフォルトライトを設定。



	Animation.PlayAnimation(Stand_anim, 0.1f);

	Animation.SetAnimationEndTime(Attack_anim, 0.5);
	Animation.SetAnimationLoopFlag(Attack_anim, false);
	Animation.SetAnimationEndTime(Damage_anim, 0.5);
	Animation.SetAnimationLoopFlag(Damage_anim, false);

	m_rotation.SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(170.0f));


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
	skinModel.Draw(renderContext, g_battleCamera->GetViewMatrix(), g_battleCamera->GetProjectionMatrix());
}



void BattleEnemy::AnimationSet()
{
	//ターン制のアニメーション
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


	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);
}

void BattleEnemy::Delete()
{
	DeleteGO(this);
}