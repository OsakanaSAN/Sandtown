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

	//����I�ɃZ�[�u���܂���B
	if (SaveTime > 60 && g_player != nullptr)
	{
		SaveDatas();
		SaveTime = 0;
	}

}

void SaveData::LoadDatas()
{

	//�e���ł���Ă�������ق���������

}

////////////////////////
//Save�̋@�\
void SaveData::SaveDatas()
{


	ofstream fout("Assets/DATA/Player.dat");
	if (!fout)
	{
		exit(0);
	}

	fout.precision(3);

	//Player�̃f�[�^
	fout << g_player->Getpos().x << endl;//X���W
	fout << g_player->Getpos().y << endl;//Y���W
	fout << g_player->Getpos().z << endl;//Z���W
	fout.close();

	ofstream HudData("Assets/DATA/Hud.dat");
	if (!HudData)
	{
		exit(0);
	}

	HudData.precision(3);

	//Hud�̃f�[�^
	HudData << g_Hud->GetATK() << endl;     //�U����
	HudData << g_Hud->GetEXP() << endl;     //�o���l
	HudData << g_Hud->GetGold() << endl;    //����
	HudData << g_Hud->GetHP() << endl;      //�̗�
	HudData << g_Hud->GetLV() << endl;      //���x��
	HudData << g_Hud->GetMaxHP() << endl;   //�ő�HP
	HudData << g_Hud->GetNextExp() << endl; //����̃��x���A�b�v�܂ł̌o���l
	HudData << g_Hud->GetNextHp() << endl;  //����HP
	HudData.close();

	ofstream CameraData("Assets/DATA/Camera.dat");
	if (!CameraData)
	{
		exit(0);
	}

	CameraData.precision(3);
	//Camera�̃f�[�^
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