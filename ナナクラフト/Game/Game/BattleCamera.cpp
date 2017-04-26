#include "stdafx.h"
#include "BattleCamera.h"

extern BattlePlayer* g_battleplayer;

BattleCamera::BattleCamera()
{
}


BattleCamera::~BattleCamera()
{
}

bool BattleCamera::Start()
{
	Bcamera.SetPosition(pos); //プレイヤーの真上らへん
	Bcamera.SetTarget(tag/*g_battleplayer->Getpos()*/);   //プレイヤーの座標

	return true;


}

void BattleCamera::Update()
{

	Bcamera.Update();
}