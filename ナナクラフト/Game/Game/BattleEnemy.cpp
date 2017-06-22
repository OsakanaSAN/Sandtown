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
	

	All.SetAmbinetLight({ 0.2f,0.2f,0.2f });
	All.SetDiffuseLightDirection(0, { 0.0f, -0.707f, 0.707f });
	All.SetDiffuseLightColor(0, { 0.3f, 0.3f, 0.3f, 1.0f });
	All.SetDiffuseLightDirection(1, { 0.0f, 0.707f, 0.707f });
	All.SetDiffuseLightColor(1, { 0.1f, 0.1f, 0.1f, 1.0f });
	All.SetDiffuseLightDirection(2, { 0.0f, -0.707f, -0.707f });
	All.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	All.SetDiffuseLightDirection(3, { 0.0f, 0.707f, -0.707f });
	All.SetDiffuseLightColor(3, { 0.1f, 0.1f, 0.1f, 1.0f });

	CVector3 Wpos =g_battleplayer->Getpos();
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
	/*for (int i = 0;i < eneNo;i++) {

		position[i] = Wpos;
		Wpos.x -= 2.0f;
	}*/

	IsAttack = false;
	IsDamage = false;
	IsStand = true;
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
		for (int i = 0;i < eneNo;i++) {
			skinModelData[i].LoadModelData(g_Enemy->GetenemyName(), &Animation[i]);
		}
		ATK = g_Enemy->GetEATK();
		HP = g_Enemy->GetEHp();
		Exp = g_Enemy->GetExp();
		EGold = g_Enemy->GetEGold();

		g_Enemy->SetEnemyState(Dead);
	}
	else if (g_Enemy2->Getenemyhit() && g_Enemy2->GetEnemyState() == Alive)
	{
		for (int i = 0;i < eneNo;i++) {
			skinModelData[i].LoadModelData(g_Enemy2->GetenemyName(), &Animation[i]);
		}
		ATK = g_Enemy2->GetEATK();
		HP = g_Enemy2->GetEHp();
		Exp = g_Enemy2->GetExp();
		EGold = g_Enemy2->GetEGold();
		g_Enemy2->SetEnemyState(Dead);
	}
	else if (g_Enemy3->Getenemyhit() && g_Enemy3->GetEnemyState() == Alive)
	{
		for (int i = 0;i < eneNo;i++) {
			skinModelData[i].LoadModelData(g_Enemy3->GetenemyName(), &Animation[i]);
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
	m_rotation[0].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(170.0f));
	m_rotation[1].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(80.0f));
	m_rotation[2].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(-80.0f));
	m_rotation[3].SetRotation(CVector3(0.0f, -1.0f, 0.0f), CMath::DegToRad(350.0f));
	


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
	for (int i = 0;i < eneNo;i++) {
		skinModel[i].Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
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


void BattleEnemy::Delete()
{
	DeleteGO(this);
}
void BattleEnemy::EnemyParticle(CVector3 target)
{

	if (m_particle != nullptr) { return; }
	//パーティクルの生成
	m_particle = NewGO<CParticleEmitter>(0);

	m_particle->Init(m_random, g_gameCamera->GetCamera(),
	{
		"Assets/Particle/burn.png",		//!<テクスチャのファイルパス。
		{ 0.0f, 0.0f, 0.0f },							//!<初速度。
		0.3f,											//!<寿命。単位は秒。
		0.5f,											//!<発生時間。単位は秒。
		3.5f,											//!<パーティクルの幅。
		3.5f,											//!<パーティクルの高さ。
		{ 0.0f, 0.0f,0.0f },							//!<初期位置のランダム幅。
		{ 0.0f, 0.0f,0.0f },							//!<初速度のランダム幅。
		{ 1.0f, 1.0f,1.0f },							//!<速度の積分のときのランダム幅。
		{
			{ 0.0f, 0.0f,0.25f, 0.25f },//0.25,0.5,0.75,1UとVの位置
			{ 0.0f, 0.0f, 0.0f, 0.0f }, //X,Y,X,Y
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		},//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		1,												//!<UVテーブルのサイズ。
		{ 0.0f, 0.0f, 0.0f },							//!<重力。
		true,											//!<死ぬときにフェードアウトする？
		0.3f,											//!<フェードする時間。
		2.0f,											//!<初期アルファ値。
		true,											//!<ビルボード？
		3.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,												//!<0半透明合成、1加算合成。
		{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
	},
		target);//パーティクルを生成する座標　CVector3型？

}
void BattleEnemy::EnemyParticleDelete()
{
	DeleteGO(m_particle);
	m_particle = nullptr;
}