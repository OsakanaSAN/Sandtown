#include "stdafx.h"
#include "Camera.h"
#include "BattlePlayer.h"



Camera::Camera()
{

	
}


Camera::~Camera()
{
}
bool Camera::Start()
{
	
	camera.SetPosition(pos); //プレイヤーの真上らへん
	camera.SetTarget(g_player->Getpos());   //プレイヤーの座標

	cameraCollisionSolver.Init(0.2f);
	return true;

}

void Camera::Update()
{
	switch (scene)
	{
	case START:
		TpsCamera();
		camera.Update();
	

		break;
	case STOP:
		camera.Update();
		break;
	}


}

void Camera::TpsCamera()
{

	//回転
	float rStick_x = Pad(0).GetRStickXF() * 2.0f;
	float rStick_y = Pad(0).GetRStickYF() * 2.0f;

	if (fabs(rStick_x) > 0.0f)
	{
		CMatrix mRot;
		mRot.MakeRotationY(0.05f * rStick_x);
		mRot.Mul(pos);


	}
	if (fabsf(rStick_y) > 0.0f) {
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, pos);
		rotAxis.Normalize();
		CMatrix mRot;
		mRot.MakeRotationAxis(rotAxis, 0.05f * rStick_y);
		CVector3 toPositionOld = pos;
		mRot.Mul(pos);
		CVector3 toPosDir = pos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.2f) {
			//カメラが上向きすぎ。
			pos = toPositionOld;
		}
		else if (toPosDir.y > 0.8f) {
			//カメラが下向きすぎ。
			pos = toPositionOld;
		}
	}

	
	
	if (g_player != nullptr) {
		V = g_player->Getpos();
		V.y += 1.0f;
		camera.SetTarget(V);
		V.Add(pos);
		camera.SetPosition(V);
	}

	CVector3 newPos;
	if (cameraCollisionSolver.Execute(newPos, camera.GetPosition(), camera.GetTarget()))
	{
		camera.SetPosition(newPos);
		//camera.ClearSpringParame();

	}


}

void Camera::BattleCamera()
{
	camera.SetPosition(Battlepos); //プレイヤーの真上らへん
	camera.SetTarget(Battletag);   //プレイヤーの座標

}

void Camera::PlayerBatlleCamera(CVector3 trget)
{
	CVector3 TG = trget;
	

	camera.SetTarget(TG);   //プレイヤーの座標
	//回転
	float rStick_x = 0.1f;


	if (fabs(rStick_x) > 0.0f)
	{
		CMatrix mRot;
		mRot.MakeRotationY(0.05f * rStick_x);
		mRot.Mul(BattlePlayerCameraPos);


	}


	if (g_battleplayer != nullptr) {
		V = g_battleplayer->Getpos();
		V.y += 1.0f;
		camera.SetTarget(V);
		V.Add(BattlePlayerCameraPos);
		camera.SetPosition(V);
	}

	camera.Update();

}