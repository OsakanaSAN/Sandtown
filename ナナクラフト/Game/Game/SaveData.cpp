#include "stdafx.h"
#include "SaveData.h"
#include "Player.h"
#include "Camera.h"
#include "HUD.h"
#include "Menu.h"
#include "Map.h"



SaveData::SaveData()
{
}


SaveData::~SaveData()
{
}


void SaveData::Update()
{
	if (g_map == nullptr) { return; }
	SaveTime += GameTime().GetFrameDeltaTime();

	//定期的にセーブしますよ。
	if (SaveTime > 60 && g_player != nullptr)
	{
		SaveDatas();
		SaveTime = 0;
	}

}

void SaveData::LoadDatas()
{

	//各自でやってもらったほうがええわ

}

////////////////////////
//Saveの機構
void SaveData::SaveDatas()
{


	ofstream fout("Assets/DATA/Player.dat");
	if (!fout)
	{
		exit(0);
	}

	fout.precision(3);

	//Playerのデータ
	fout << g_player->Getpos().x << endl;//X座標
	fout << g_player->Getpos().y << endl;//Y座標
	fout << g_player->Getpos().z << endl;//Z座標
	fout.close();

	ofstream HudData("Assets/DATA/Hud.dat");
	if (!HudData)
	{
		exit(0);
	}

	HudData.precision(3);

	//Hudのデータ
	HudData << g_Hud->GetATK() << endl;     //攻撃力
	HudData << g_Hud->GetEXP() << endl;     //経験値
	HudData << g_Hud->GetGold() << endl;    //お金
	HudData << g_Hud->GetHP() << endl;      //体力
	HudData << g_Hud->GetLV() << endl;      //レベル
	HudData << g_Hud->GetMaxHP() << endl;   //最大HP
	HudData << g_Hud->GetNextExp() << endl; //次回のレベルアップまでの経験値
	HudData << g_Hud->GetNextHp() << endl;  //次のHP
	HudData.close();

	ofstream CameraData("Assets/DATA/Camera.dat");
	if (!CameraData)
	{
		exit(0);
	}

	CameraData.precision(3);
	//Cameraのデータ
	CameraData << g_gameCamera->GetPos().x << endl;
	CameraData << g_gameCamera->GetPos().y << endl;
	CameraData << g_gameCamera->GetPos().z << endl;
	CameraData.close();


	ofstream InventData("Assets/DATA/Invent.dat");
	if (!InventData)
	{
		exit(0);
	}

	

	for (int count = 0;count < 30;count++)
	{
		InventData << g_menu->GetInvenntPack()[count] << endl;
	}
	InventData.close();


}