#include "stdafx.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "Camera.h"

extern BattleEnemy* g_battleenemy;

enum {

	Stand_anim,
	Walk_anim,  //歩く
	Run_anim,  //走る
	

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

void BattlePlayer::Particle()
{
	/*if (m_particle == nullptr)
	{
	return;
	}*/

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
		{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
		{ 0.0f, 0.0f,0.0f },							//!<初速度のランダム幅。
		{ 1.0f, 1.0f, 1.0f },							//!<速度の積分のときのランダム幅。
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
		g_battleenemy->Getpos());




}


void BattlePlayer::ParticleDelete()
{
	DeleteGO(m_particle);
	m_particle = nullptr;


}