#include "stdafx.h"
#include "Enemy.h"
#include "Camera.h"
#include "Player.h"





Enemy::Enemy()
{

}


Enemy::~Enemy()
{

	
}

bool Enemy::Start() {
	
	Enemylight.SetAmbinetLight({ 1.0f,1.0f,1.0f});

	skinModelData.LoadModelData("Assets/modelData/cabetu2.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&Enemylight);	//デフォルトライトを設定。

								//キャラクタコントローラの初期化。
	characterController.Init(0.5f, 1.0f, position);
	CVector3 move = characterController.GetMoveSpeed();
	//move.x = -Pad(0).GetLStickXF() * 5.0f;
	//move.z = -Pad(0).GetLStickYF() * 5.0f;

	return true;

}

void Enemy::Update() {

	

	Tracking();
	skinModel.Update(position, m_rotation, CVector3::One);
}

void Enemy::Render(CRenderContext&renderContext) {

	
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

void Enemy::Tracking()
{
	CVector3 pPos = g_player->Getpos();

	CVector3 diff = pPos;

	diff.Subtract(position);

	if (diff.Length() < SearchRaeng&& diff.Length() > 1.5f)
	{
		if (over == true) {
			diff.Div(diff.Length());

			position.x += diff.x*0.1f;
			position.y += diff.y*0.1;
			position.z += diff.z*0.1;
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

