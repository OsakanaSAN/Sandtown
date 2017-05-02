#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#define  MOVESPEED  4.0
using  namespace std;

extern Camera* g_gameCamera;

enum {

	Run_anim,
	Attack_anim,
	Damage_anim,

};


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	All.SetPointLightColor({ 1.0f,1.0f,1.5f,4.0f });


	skinModelData.LoadModelData("Assets/modelData/cabetu2.X", &Animation);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&All);	//デフォルトライトを設定。


//キャラクタコントローラの初期化。
//*characterController.Init(0.5f, 1.0f, position);*/

	Isrun = false;
	Ismove = false;

	currentAnimSetNo = Run_anim;
	Animation.PlayAnimation(Run_anim, 0.1f);
	/*Animation.SetAnimationLoopFlag(Jump_anim, false);*/
	/*Animation.SetAnimationEndTime(Run_anim, 0.8);*/

	return true;

}

void Enemy::Update()
{
	All.SetPointLightPosition(Getpos());

	AnimetionSet();
	//ワールド行列の更新。
	skinModel.Update(position, m_rotion, CVector3::One);


}

void Enemy::Move()
{

	//CVector3 old_move = move;

	//CVector3 moveXZ = move;						//方向ベクトル
	//moveXZ.y = 0.0f;



	//if (move.x != 0.0f || move.z != 0.0f)
	//{
	//	Ismove = true;
	//}
	//else
	//{
	//	Ismove = false;
	//}

}




void Enemy::AnimetionSet()
{


	/*Isrun = true;*/
	////キャラの移動
	//if (!Isrun) {
	//	if (Ismove) {

	//		

	//	}
	//}
	//else if (!Ismove)
	//{
	//	Animation.PlayAnimation(Run_anim, 0.3f);
	//	Isrun = false;

	//}

	//アニメーションの更新
	Animation.Update(1.0f / 60.0f);

}


void Enemy::Render(CRenderContext& renderContext)
{


	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}
