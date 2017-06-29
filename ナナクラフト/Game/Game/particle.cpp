#include "stdafx.h"
#include "particle.h"
#include "Camera.h"

particle::particle()
{
	m_random.Init((unsigned long)time(NULL));
}


particle::~particle()
{
}

bool particle::Start()
{
	return true;
}

void particle::Update()
{

}

void particle::Render(CRenderContext&renderContext)
{

}

void particle::Particle(CVector3 target, int ParticleNumber)
{
	if (m_particle != nullptr) { return; }
	switch (ParticleNumber)
	{
	case ATTACK://攻撃


				//パーティクルの生成
		m_particle = NewGO<CParticleEmitter>(0);

		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/Particle/burn.png",						//!<テクスチャのファイルパス。
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
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/Particle/Heal.tga",		//!<テクスチャのファイルパス。
			{ 0.0f, 1.4f, 0.0f },							//!<初速度。
			0.5f,											//!<寿命。単位は秒。
			0.1f,											//!<発生時間。単位は秒。
			0.25f,											//!<パーティクルの幅。
			0.25f,											//!<パーティクルの高さ。
			{ 0.2f, 0.2f, 0.2f },							//!<初期位置のランダム幅。
			{ 0.0f, 2.0f, 0.0f },							//!<初速度のランダム幅。
			{ 1.0f, 1.0f, 1.0f },							//!<速度の積分のときのランダム幅。
			{
				{ 0.0f, 0.0f, 1.0f, 1.0f },//0.25,0.5,0.75,1UとVの位置
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

	}
}


void particle::ParticleDelete()
{
	//if (m_particle == nullptr) { return; }

	DeleteGO(m_particle);
	m_particle = nullptr;

}
