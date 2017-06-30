#include "stdafx.h"
#include "BattleEnemy.h"
#include "Camera.h"
#include "HUD.h"
#include "EnemyHUD.h"
#include "Enemy.h"
#include "BattlePlayer.h"
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
	

	All.SetAmbinetLight({ 0.4f,0.4f,0.4f });
	All.SetDiffuseLightDirection(0, { 0.0f, -0.707f, 0.707f });
	All.SetDiffuseLightColor(0, { 0.3f, 0.3f, 0.3f, 1.0f });
	All.SetDiffuseLightDirection(1, { 0.0f, 0.707f, 0.707f });
	All.SetDiffuseLightColor(1, { 0.1f, 0.1f, 0.1f, 1.0f });
	All.SetDiffuseLightDirection(2, { 0.0f, -0.707f, -0.707f });
	All.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	All.SetDiffuseLightDirection(3, { 0.0f, 0.707f, -0.707f });
	All.SetDiffuseLightColor(3, { 0.1f, 0.1f, 0.1f, 1.0f });
	CVector3 Wpos = g_battleplayer->Getpos();
	switch (Battlecase)
	{
	case Single:
		Wpos.z += 6.5f;
		position[0] = Wpos;
		break;
	case Double:
		Wpos.z += 4.5f;
		Wpos.x -= 4.5f;
		position[0] = Wpos;
		Wpos = g_battleplayer->Getpos();
		Wpos.x += 4.5f;
		Wpos.z += 4.5f;
		position[1] = Wpos;
		break;
	case Cross:
		Wpos.z += 6.5f;
		position[0] = Wpos;
		Wpos = g_battleplayer->Getpos();
		Wpos.x += 6.5f;
		position[1] = Wpos;
		Wpos = g_battleplayer->Getpos();
		Wpos.x -= 6.5f;
		position[2] = Wpos;
		Wpos = g_battleplayer->Getpos();
		Wpos.z -= 5.5f;
		position[3] = Wpos;
		break;
	case Cross2:
		Wpos.z += 4.5f;
		Wpos.x -= 4.5f;
		position[0] = Wpos;
		Wpos = g_battleplayer->Getpos();
		Wpos.x += 4.5f;
		Wpos.z += 4.5f;
		position[1] = Wpos;
		Wpos = g_battleplayer->Getpos();
		Wpos.x += 4.5f;
		Wpos.z -= 4.5f;
		position[2] = Wpos;
		Wpos = g_battleplayer->Getpos();
		Wpos.x -= 4.5f;
		Wpos.z -= 4.5f;
		position[3] = Wpos;
		break;
	default:
		break;
	}
	/*for (int i = 0;i < eneNo;i++) {

		position[i] = Wpos;
		Wpos.x -= 2.0f;
	}*/

	IsAttack = false;
	IsDamage = false;
	IsStand = true;
	IsAnimend = true;
	currentAnimSetNo = Stand_anim;

	/*switch (Battlecase)
	{
	case 0:

		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}*/
	
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
		switch (Battlecase)
		{
		case Single:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy->GetenemyName(), &Animation[i]);
			}
			break;
		case Double:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy->GetenemyName(), &Animation[i]);
			}
			break;
		case Cross:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy->GetenemyName(), &Animation[i]);
			}
			break;
		case Cross2:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy->GetenemyName(), &Animation[i]);
			}
			break;
		default:
			break;
		}
		
		
		ATK = g_Enemy->GetEATK();
		HP = g_Enemy->GetEHp();
		Exp = g_Enemy->GetExp();
		EGold = g_Enemy->GetEGold();

		g_Enemy->SetEnemyState(Dead);
	}
	else if (g_Enemy2->Getenemyhit() && g_Enemy2->GetEnemyState() == Alive)
	{
		switch (Battlecase)
		{
		case Single:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy2->GetenemyName(), &Animation[i]);
			}
			break;
		case Double:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy2->GetenemyName(), &Animation[i]);
			}
			break;
		case Cross:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy2->GetenemyName(), &Animation[i]);
			}
			break;
		case Cross2:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy2->GetenemyName(), &Animation[i]);
			}
			break;
		default:
			break;
		}

		ATK = g_Enemy2->GetEATK();
		HP = g_Enemy2->GetEHp();
		Exp = g_Enemy2->GetExp();
		EGold = g_Enemy2->GetEGold();
		g_Enemy2->SetEnemyState(Dead);
	}
	else if (g_Enemy3->Getenemyhit() && g_Enemy3->GetEnemyState() == Alive)
	{
		switch (Battlecase)
		{
		case Single:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy3->GetenemyName(), &Animation[i]);
			}
			break;
		case Double:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy3->GetenemyName(), &Animation[i]);
			}
			break;
		case Cross:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy3->GetenemyName(), &Animation[i]);
			}
			break;
		case Cross2:
			for (int i = 0;i < eneNo;i++) {
				skinModelData[i].LoadModelData(g_Enemy3->GetenemyName(), &Animation[i]);
			}
			break;
		default:
			break;
		}

		ATK = g_Enemy3->GetEATK();
		HP = g_Enemy3->GetEHp();
		Exp = g_Enemy3->GetExp();
		EGold = g_Enemy3->GetEGold();

		g_Enemy3->SetEnemyState(Dead);
	}


	g_Enemy->SetActiveFlag(false);
	g_Enemy2->SetActiveFlag(false);
	g_Enemy3->SetActiveFlag(false);
	
	for (int i = 0;i < eneNo;i++) {
		skinModel[i].Init(skinModelData[i].GetBody());
		skinModel[i].SetLight(&All);					//デフォルトライトを設定。
		skinModel[i].SetShadowCasterFlag(true);
		skinModel[i].SetShadowReceiverFlag(true);
		Animation[i].PlayAnimation(Stand_anim, 0.1f);
		Animation[i].SetAnimationEndTime(Attack_anim, 0.5);
		Animation[i].SetAnimationLoopFlag(Attack_anim, false);
		Animation[i].SetAnimationEndTime(Damage_anim, 0.5);
		Animation[i].SetAnimationLoopFlag(Damage_anim, false);

		//m_rotation[i].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(170.0f));

	}



	switch (Battlecase)
	{
	case Single:
		m_rotation[0].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(170.0f));
	/*	m_rotation[1].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(80.0f));
		m_rotation[2].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(-80.0f));
		m_rotation[3].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(350.0f));*/
		break;
	case Double:
		m_rotation[0].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(220.0f));
		m_rotation[1].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(130.0f));
		/*m_rotation[2].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(-80.0f));
		m_rotation[3].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(350.0f));*/
		break;
	case Cross:
		m_rotation[0].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(170.0f));
		m_rotation[1].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(80.0f));
		m_rotation[2].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(-80.0f));
		m_rotation[3].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(350.0f));
		break;
	case Cross2:
		m_rotation[0].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(200.0f));
		m_rotation[1].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(150.0f));
		m_rotation[2].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(65.0f));
		m_rotation[3].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(-65.0f));
		break;
	default:
		break;
	}

	return true;
}



void BattleEnemy::Update()
{
	All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });

	AnimationSet();

	for (int i = 0;i < eneNo;i++) {
		Animation[i].Update(1.0f / 60.0f);
		skinModel[i].Update(position[i], m_rotation[i], CVector3::One);
	}
}



void BattleEnemy::Render(CRenderContext&renderContext)
{
	switch (Battlecase)
	{
	case Single:
		
			skinModel[0].Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
		
		break;
	case Double:
		
			skinModel[0].Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
			skinModel[1].Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

		break;
	case Cross:
		for (int i = 0;i < eneNo;i++) {
			skinModel[i].Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
		}
		break;
	case Cross2:
		for (int i = 0;i < eneNo;i++) {
			skinModel[i].Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
		}
		break;
	default:
		break;
	}
	
}



void BattleEnemy::AnimationSet()
{
	//ターン制のアニメーション
	if (!IsStand) {

		//攻撃モーション開始
		if (IsAttack) {

			IsAnimend = false;
			Animation[EnemyNo].PlayAnimation(Attack_anim, 0.5);

			IsStand = true;
			g_Hud->Damage(ATK);

		}
		
		//ダメージモーション開始
		else if (IsDamage)
		{
			IsAnimend = false;
			Animation[EnemyNo].PlayAnimation(Damage_anim, 0.5);

			IsStand = true;
		}

	}
	else if (!IsAttack && !IsDamage)
	{
		Animation[EnemyNo].PlayAnimation(Stand_anim, 0.3f);

		IsStand = false;

	}



	if (!Animation[EnemyNo].IsPlay())
	{
		Animation[EnemyNo].PlayAnimation(Stand_anim, 0.3f);
		//IsStand = false;
		IsAttack = false;
		IsDamage = false;
		IsAnimend = true;
	}


	//アニメーションの更新
	Animation[EnemyNo].Update(1.0f / 60.0f);

}