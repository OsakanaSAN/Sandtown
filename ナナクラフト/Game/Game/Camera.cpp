#include "stdafx.h"
#include "Camera.h"

extern Player* g_player;


Camera::Camera()
{

	//tag = g_player->Getpos();
}


Camera::~Camera()
{
}
bool Camera::Start()
{
	
	camera.SetPosition(pos); //プレイヤーの真上らへん
	camera.SetTarget(g_player->Getpos());   //プレイヤーの座標

	return true;

}

void Camera::Update()
{
	
	TpsCamera();
	camera.Update();


}

void Camera::TpsCamera()
{

	//回転
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();

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
		if (toPosDir.y < -0.5f) {
			//カメラが上向きすぎ。
			pos = toPositionOld;
		}
		else if (toPosDir.y > 0.8f) {
			//カメラが下向きすぎ。
			pos = toPositionOld;
		}
	}

	else
	{
		V = g_player->Getpos();
		V.y += 1.0f;
		camera.SetTarget(V);
		V.Add(pos);
		camera.SetPosition(V);

	}

}

