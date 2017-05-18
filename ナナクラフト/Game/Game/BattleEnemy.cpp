#include "stdafx.h"
#include "BattleEnemy.h"
#include "Camera.h"
#include "HUD.h"






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
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&All);	//デフォルトライトを設定。



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
	//ターン制のアニメーション
	if (!IsStand) {
		if (IsAttack) {
			IsAnimend = false;
			Animation.PlayAnimation(Attack_anim, 0.5);

			IsStand = true;
			g_Hud->Damage(50);

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