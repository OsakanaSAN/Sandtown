#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#define  MOVESPEED  6.0
using  namespace std;




enum {

	Stand_anim,
	Walk_anim,
	Run_anim,
	Jump_anim,

};

Player::Player()
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
	

	position = { -5.0f,0.0f,0.0f };

	runsound = NewGO<CSoundSource>(0);
	runsound->Init("Assets/sound/Runsound.wav");
	runsound->SetVolume(0.3);


	
}


Player::~Player()
{
	runsound->Release();
	//ファイルの書き込み
	ofstream fout("Assets/DATA/tst.txt");
	if (!fout)
	{
		exit(0);
	}

	fout.precision(3);

	fout << position.x << endl;
	fout << position.y << endl;
	fout << position.z << endl;
	fout.close();

}

bool Player::Start()
{
	

	skinModelData.LoadModelData("Assets/modelData/Knight.X", &Animation);
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&All);//デフォルトライトを設定。
	skinModel.SetShadowCasterFlag(true);


	m_rotion.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(0.0f));
	//キャラクタコントローラの初期化。
	characterController.Init(0.5f, 1.0f, position);

	Isrun = false;
	Ismove = false;

	currentAnimSetNo = Stand_anim;
	Animation.PlayAnimation(Stand_anim, 0.1f);
	Animation.SetAnimationLoopFlag(Jump_anim, false);
	Animation.SetAnimationEndTime(Run_anim, 0);

	
	radius = 0.6f;
	height = 0.3f;
	
	scale.Scale(0.4);
	return true;

}

void Player::Update()
{
	
	switch (IsMove)
	{

	case START:

		characterController.SetPosition(position);

		AngleSet();  //キャラクターの向きを変更する
		AnimetionSet();
		Move();      //キャラの移動
		
		
		skinModel.EntryShadowMap();
		//ワールド行列の更新。
		skinModel.Update(position, m_rotion, /*CVector3::One*/scale);

		break;

	case STOP:

		break;

	}
	//skinModel.Update(position, m_rotion, /*CVector3::One*/scale);
}

void Player::Move()
{
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;

	

	CVector3 old_move = move;

	CVector3 moveXZ = move;						//方向ベクトル
	moveXZ.y = 0.0f;

	

	
	if (move.x  !=  0.0f || move.z != 0.0f)
	{
		Ismove = true;
		
		
	}

	else
	{
		Ismove = false;
	}



}

void Player::AngleSet()
{
	CVector3 moveSpeed = characterController.GetMoveSpeed();

	CVector3 moveDirLocal;
	moveDirLocal.y = 0.0f;
	moveDirLocal.x = Pad(0).GetLStickXF();
	moveDirLocal.z = Pad(0).GetLStickYF();
	const CMatrix& mViewInv = g_gameCamera->GetCamera().GetViewMatrixInv();

	CVector3 cameraZ;
	cameraZ.x = mViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y軸いらない。
	cameraZ.z = mViewInv.m[2][2];
	cameraZ.Normalize();	//Y軸を打ち消しているので正規化する。
							//カメラから見た横方向のベクトルを取得。
	CVector3 cameraX;
	cameraX.x = mViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y軸はいらない。
	cameraX.z = mViewInv.m[0][2];
	cameraX.Normalize();	//Y軸を打ち消しているので正規化する。

	CVector3 moveDir;
	moveDir.x = cameraX.x * moveDirLocal.x + cameraZ.x * moveDirLocal.z;
	moveDir.y = 0.0f;	//Y軸はいらない。
	moveDir.z = cameraX.z * moveDirLocal.x + cameraZ.z * moveDirLocal.z;

	moveSpeed.x = moveDir.x * MOVESPEED;
	moveSpeed.z = moveDir.z * MOVESPEED;




	if (Pad(0).IsPress(enButtonRB1))
	{
		moveSpeed.x = moveDir.x * MOVESPEED * 1.3;
		moveSpeed.z = moveDir.z * MOVESPEED * 1.3;
		Animation.SetAnimationSpeedRate(6.8);
		Animation.SetAnimationEndTime(Run_anim, 2.0f);
	}

	if (moveDir.LengthSq() > 0.0001f) {

		m_rotion.SetRotation(CVector3::Up, atan2f(moveDir.x, moveDir.z));
		
	}

	

	characterController.SetMoveSpeed(moveSpeed);

	characterController.Execute(0.03f);

	position = characterController.GetPosition();

}



void Player::AnimetionSet()
{
	//キャラの移動
	if (!Isrun) {
		if (Ismove) {

			Animation.PlayAnimation(Run_anim,1.0);
			Isrun = true;

			//runsound->SetPosition(Getpos());

			/*runsound->Play(true);*/

			//runsound->Play(true);


			Animation.SetAnimationSpeedRate(4.5);
			Animation.SetAnimationEndTime(Run_anim,2.0f);


		}
	}
	else if (!Ismove)
	{
		Animation.SetAnimationSpeedRate(0.3);
		Animation.PlayAnimation(Stand_anim, 0.3f);
		Isrun = false;
	//	runsound->Stop();
		Animation.SetAnimationSpeedRate(1);

	}

	
	
	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);

}


void Player::Render(CRenderContext& renderContext)
{


	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
	
}

void Player::Loadpos()
{
	ifstream fin("Assets/DATA/tst.txt");
	if (!fin)
	{
		exit(0);
	}

	fin.precision(3);
	fin >> position.x >> position.y >> position.z;
	fin.close();
}


