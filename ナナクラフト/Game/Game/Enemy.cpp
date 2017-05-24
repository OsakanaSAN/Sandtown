#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"
#include "Player.h"
#include "Scene/GameScene.h"






Enemy::Enemy()
{
	Enemylight.SetAmbinetLight({ 0.2f,0.2f,0.2f });
	Enemylight.SetDiffuseLightDirection(0, { 0.0f, -0.707f, 0.707f });
	Enemylight.SetDiffuseLightColor(0, { 0.3f, 0.3f, 0.3f, 1.0f });
	Enemylight.SetDiffuseLightDirection(1, { 0.0f, 0.707f, 0.707f });
	Enemylight.SetDiffuseLightColor(1, { 0.1f, 0.1f, 0.1f, 1.0f });
	Enemylight.SetDiffuseLightDirection(2, { 0.0f, -0.707f, -0.707f });
	Enemylight.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	Enemylight.SetDiffuseLightDirection(3, { 0.0f, 0.707f, -0.707f });
	Enemylight.SetDiffuseLightColor(3, { 0.1f, 0.1f, 0.1f, 1.0f });
}


Enemy::~Enemy()
{

	
}

bool Enemy::Start() {
	
	/*Enemylight.SetAmbinetLight({ 1.0f,1.0f,1.0f});*/

	skinModelData.LoadModelData("Assets/modelData/ghost.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&Enemylight);	//デフォルトライトを設定。

								//キャラクタコントローラの初期化。
	characterController.Init(0.5f, 1.0f, position);
	CVector3 move = characterController.GetMoveSpeed();
	//move.x = -Pad(0).GetLStickXF() * 5.0f;
	//move.z = -Pad(0).GetLStickYF() * 5.0f;

	Animation.PlayAnimation(3, 0.2f);
	Animation.SetAnimationSpeedRate(1.5);
	skinModel.SetShadowCasterFlag(true);
	/*skinModel.SetShadowReceiverFlag(true);*/
	return true;

}

void Enemy::Update() {

	

	Tracking();
	
	
	// アニメーションの更新a
	Animation.Update(1.0f / 60.0f);
	skinModel.Update(position, m_rotation, CVector3::One);
}

void Enemy::Render(CRenderContext&renderContext) {

	
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

void Enemy::Tracking()
{

	if (g_player == nullptr) { return; }
	CVector3 pPos = g_player->Getpos();

	CVector3 diff = pPos;

	diff.Subtract(position);

	if (diff.Length() < SearchRaeng&& diff.Length() > 1.5f)
	{
		if (diff.Length() < 2)
		{
			g_gameScene->Batoset(true);
			DeleteGO(this);
		}


		else if (over == true) {
			diff.Div(diff.Length());

			position.x += diff.x*0.1f;
			position.y += diff.y*0.1;
			position.z += diff.z*0.1;
			CVector3 paly = g_player->Getpos();


			CVector3 Def;
			Def.Subtract(position, g_player->Getpos());

			m_rotation.SetRotation(CVector3::Up, atan2f(-Def.x, -Def.z)); //前が背中なんで　マイナスする


			

		}
		else
		{
			SearchRaeng *= 2;
			over = true;
		}

	}

	else if (diff.Length() > SearchRaeng)
	{
		SearchRaeng = 3.5f;
		over = false;
	}

	

}

