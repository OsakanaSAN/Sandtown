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
	Bcamera.SetPosition(pos); //�v���C���[�̐^���ւ�
	Bcamera.SetTarget(tag/*g_battleplayer->Getpos()*/);   //�v���C���[�̍��W

	return true;


}

void BattleCamera::Update()
{

	Bcamera.Update();
}