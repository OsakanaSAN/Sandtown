#include "stdafx.h"
#include "Camera.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleScene.h"


Camera::Camera()
{

	
}


Camera::~Camera()
{
}
bool Camera::Start()
{
	
	camera.SetPosition(pos); //�v���C���[�̐^���ւ�
	camera.SetTarget(g_player->Getpos());   //�v���C���[�̍��W

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

	//��]
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
			//�J����������������B
			pos = toPositionOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������B
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
		

	}


}

//�퓬�ɓ���O�̃J����
void Camera::BattleCamera()
{
	int Bc=g_battleScene->GetBcase();
	if (Bc== 0 || Bc == 1)
	{
		Battlepos = { -4.0f,52.0f,-8.0f };
	}
	else if (Bc == 2)
	{
		Battlepos = { -6.0f,52.0f,-11.5f };
	}
	else if(Bc==3)
	{
		Battlepos = { -4.0f,52.0f,-12.0f };
	}
	CVector3 bpos;
	bpos = g_battleplayer->Getpos2();
	Battletag.z = bpos.z + 7;
	camera.SetPosition(Battlepos); 
	camera.SetTarget(Battletag);

}


//�G�ɒ��ڂ����J����
void Camera::EnemyBattleCamera()
{
	BattlePlayerCameraPos = { -1.5f,0.0f,1.0f };

	if (g_battleplayer != nullptr) {
		V = *g_battleenemy->Getpos(0);
		V.y += 1.0f;
		camera.SetTarget(V);
		//V.Add(BattleEnemyCameraPos);
		camera.SetPosition(BattleEnemyCameraPos);
	}

	camera.Update();


}


//�v���C���[�̎�����܂��J����
void Camera::PlayerBatlleCamera()
{
	
	
	//��]
	float rStick_x = 0.05f;


	if (fabs(rStick_x) > 0.0f)
	{
		CMatrix mRot;
		mRot.MakeRotationY(0.05f * rStick_x);
		mRot.Mul(BattlePlayerCameraPos);


	}


	if (g_battleplayer != nullptr) {
		V = g_battleplayer->Getpos2();
		V.y += 1.0f;
		camera.SetTarget(V);
		V.Add(BattlePlayerCameraPos);
		camera.SetPosition(V);
	}

	camera.Update();

}

