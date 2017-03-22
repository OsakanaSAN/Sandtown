#include "stdafx.h"
#include "Player.h"
extern Camera* g_gameCamera;

enum {

	Stand_anim,
	Walk_anim,
	Run_anim,
	Jump_anim,

};

Player::Player()
{
	All.SetAmbinetLight({1.0,1.0,1.0});
	
}


Player::~Player()
{

}

bool Player::Start()
{
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&All);	//デフォルトライトを設定。
	m_rotion.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(0.0f));



	//キャラクタコントローラの初期化。
	characterController.Init(0.5f, 1.0f, position);

	Isrun = false;
	Ismove = false;

	currentAnimSetNo = Stand_anim;
	Animation.PlayAnimation(Stand_anim, 0.1f);
	Animation.SetAnimationLoopFlag(Jump_anim, false);
	Animation.SetAnimationEndTime(Run_anim, 0.8);

	return true;

}

void Player::Update()
{
	
	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);
	movespeed.z = 0.2f;
	movespeed.x = 0.2f;
	
	if (GetAsyncKeyState('W') & 0x8000) {
		position.z += movespeed.z;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		position.z -= movespeed.z;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		position.x += movespeed.x;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		position.x -= movespeed.x;
	}

	
	//ワールド行列の更新。
	skinModel.Update(position, m_rotion, CVector3::One);
}

void Player::Move()
{
	
}



void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}