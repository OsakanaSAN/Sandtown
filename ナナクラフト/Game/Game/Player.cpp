#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#define  MOVESPEED  5.0
using  namespace std;




extern Camera* g_gameCamera;

enum {

	Stand_anim,
	Walk_anim,
	Run_anim,
	Jump_anim,

};

Player::Player()
{
	//ファイルの読み込み
	All.SetAmbinetLight({ 1.0f,1.0f,1.0f });

	/*
	ifstream fin("Assets/DATA/tst.txt");
	if (!fin)
	{
		exit(0);
	}

	fin.precision(3);
	fin >> position.x >> position.y >> position.z;
	fin.close();
	*/
	
}


Player::~Player()
{
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
	All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });
	


	skinModelData.LoadModelData("Assets/modelData/Unity.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&All);//デフォルトライトを設定。
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
	All.SetPointLightPosition(Getpos());

	AngleSet();  //キャラクターの向きを変更する
	Move();      //キャラの移動
	AnimetionSet();
	
	//ワールド行列の更新。
	skinModel.Update(position, m_rotion, CVector3::One);


}

void Player::Move()
{
	CVector3 move = characterController.GetMoveSpeed();
	move.x = -Pad(0).GetLStickXF() * 5.0f;
	move.z = -Pad(0).GetLStickYF() * 5.0f;


	CVector3 old_move = move;

	CVector3 moveXZ = move;						//方向ベクトル
	moveXZ.y = 0.0f;

	

	
	if (move.x != 0.0f || move.z != 0.0f)
	{
		Ismove = true;
	}
	else
	{
		Ismove = false;
	}


	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		characterController.Jump();
		move.y = 6.0f;
		Isjump = true;

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

			Animation.PlayAnimation(Run_anim,0.05);
			Isrun = true;

		}
	}
	else if (!Ismove)
	{
		Animation.PlayAnimation(Stand_anim, 0.3f);
		Isrun = false;

	}

	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);

}


void Player::Render(CRenderContext& renderContext)
{


	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}