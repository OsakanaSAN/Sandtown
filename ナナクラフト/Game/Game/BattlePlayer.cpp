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
	Walk_anim,  //歩く
	Run_anim,  //走る
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
	Animation.SetAnimationLoopFlag(Stand_anim, true); //スタンドアニメーションをループさせる

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
			Animation.SetAnimationLoopFlag(Stand_anim, true); //スタンドアニメーションをループさせる


			
			
		}

		skinModel.Update(BakPositon, m_rotation,scale);

		//アニメーションの更新
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
		//アニメーションの更新
		Animation.Update(1.0f / 60.0f);
	}

	else if (IsSetPoint == true)
	{

		Time += GameTime().GetFrameDeltaTime();
		//アニメーションの更新
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
	//ターン制のアニメーション
	if (!IsStand) {

		//攻撃時
		if (IsAttack) {
			IsAnimend = false;
			Animation.PlayAnimation(Jump_anim, 0.05f);
			Animation.SetAnimationLoopFlag(Jump_anim,false);
			Animation.SetAnimationSpeedRate(2);

			IsStand = true;

		}
		//ダメージを食らった時
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
	

	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);

}

void BattlePlayer::Particle(CVector3 target)
{
	if (m_particle != nullptr) { return;}
	switch (currentParticle)
	{
	case ATTACK://攻撃


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
		break;
	case HEAL://回復


		//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);
		//m_random.Init((unsigned long)time(NULL));
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/Particle/Heal.tga",		//!<テクスチャのファイルパス。
			{ 0.0f, 0.0f, 0.0f },							//!<初速度。
			0.3f,											//!<寿命。単位は秒。
			0.5f,											//!<発生時間。単位は秒。
			0.5f,											//!<パーティクルの幅。
			0.5f,											//!<パーティクルの高さ。
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
			{ 0.0f, 1.0f, 0.0f },							//!<重力。
			true,											//!<死ぬときにフェードアウトする？
			0.3f,											//!<フェードする時間。
			2.0f,											//!<初期アルファ値。
			true,											//!<ビルボード？
			3.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
			1,												//!<0半透明合成、1加算合成。
			{ 1.0f, 1.0f, 1.0f },							//!<乗算カラー。
		},
			target);//パーティクルを生成する座標　CVector3型？
		break;
	
	}
}


void BattlePlayer::ParticleDelete()
{
	
	DeleteGO(m_particle);
	m_particle = nullptr;
	


}