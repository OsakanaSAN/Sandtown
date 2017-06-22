#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "SceneChange.h"
#include "HUD.h"
#include "GameSky.h"
#include "shop.h"


struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* mapchip[255];
SceneChange* g_SC;
GameSky*     g_Sky;
shop*		g_shop;

//マップの配置情報。
SMapInfo mapLocInfo[] = {
#include "Map/test.h"
};
SMapInfo mapLoc2[] = {
#include "Map/test2.h"
};

SMapInfo mapLoc3[] = {
#include "Map/test3.h"
};

SMapInfo mapLoc4[] = {
#include "Map/test4.h"
};
int      MapCount = 0;

Map::Map()
{
	ChangeObject = 0;
	numObject = 0;
	NoMoveObject = 0;

	if (g_Hud->GetGold() > 500)
	{
		MapCount = 1;
	}
	else if(g_Hud->GetGold()>2000)
	{
		MapCount = 2;
	}
	else if (g_Hud->GetGold()>4000)
	{
		MapCount = 3;
	}
	

}


Map::~Map()
{
	
	for (int i = 0;i < NoMoveObject;i++)
	{
		DeleteGO(mapchip[i]);
	}


	DeleteGO(g_SC);
	DeleteGO(g_Sky);
	DeleteGO(g_shop);

}

bool Map::Start()
{
	switch (MapCount)
	{
	case 0:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLocInfo[i].modelName, "Unity") == 0)
			{
				pos = mapLocInfo[i].position;
				rot = mapLocInfo[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(rot);
				ChangeObject++;

			}
			else if (strcmp(mapLocInfo[i].modelName, "doa") == 0)
			{

				g_SC = NewGO<SceneChange>(0);
				g_SC->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				g_SC->setpos(mapLocInfo[i].position);
				g_SC->Norender();
				ChangeObject++;

			}
			else if (strcmp(mapLocInfo[i].modelName, "Sign_a") == 0)
			{

				g_shop = NewGO<shop>(0);
				g_shop->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);

				ChangeObject++;

			}
			else if (strcmp(mapLocInfo[i].modelName, "maru") == 0)
			{

				g_Sky = NewGO<GameSky>(0);
				g_Sky->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				ChangeObject++;

			}

			else
			{
				mapchip[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				mapchip[NoMoveObject]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				NoMoveObject++;
			}

		}
		mapchip[0]->SoundOnMachi();
		return true; //一回だけ呼ばれる
		break;
	case 1:

		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLoc2) / sizeof(mapLoc2[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLoc2[i].modelName, "Unity") == 0)
			{
				pos = mapLoc2[i].position;
				rot = mapLoc2[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(rot);
				ChangeObject++;

			}
			else if (strcmp(mapLoc2[i].modelName, "doa") == 0)
			{

				g_SC = NewGO<SceneChange>(0);
				g_SC->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);
				g_SC->setpos(mapLoc2[i].position);
				g_SC->Norender();
				ChangeObject++;

			}
			else if (strcmp(mapLoc2[i].modelName, "Sign_a") == 0)
			{

				g_shop = NewGO<shop>(0);
				g_shop->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);

				ChangeObject++;

			}
			else if (strcmp(mapLoc2[i].modelName, "maru") == 0)
			{

				g_Sky = NewGO<GameSky>(0);
				g_Sky->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);
				ChangeObject++;

			}

			else
			{
				mapchip[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				mapchip[NoMoveObject]->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);
				NoMoveObject++;
			}

		}
		mapchip[0]->SoundOnMachi();
		return true; //一回だけ呼ばれる
		break;
	case 2:

		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLoc3) / sizeof(mapLoc3[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLoc3[i].modelName, "Unity") == 0)
			{
				pos = mapLoc3[i].position;
				rot = mapLoc3[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(rot);
				ChangeObject++;

			}
			else if (strcmp(mapLoc3[i].modelName, "doa") == 0)
			{

				g_SC = NewGO<SceneChange>(0);
				g_SC->Init(mapLoc3[i].modelName, mapLoc3[i].position, mapLoc3[i].rotation);
				g_SC->setpos(mapLoc3[i].position);
				g_SC->Norender();
				ChangeObject++;

			}
			else if (strcmp(mapLoc3[i].modelName, "Sign_a") == 0)
			{

				g_shop = NewGO<shop>(0);
				g_shop->Init(mapLoc3[i].modelName, mapLoc3[i].position, mapLoc3[i].rotation);

				ChangeObject++;

			}
			else if (strcmp(mapLoc3[i].modelName, "maru") == 0)
			{

				g_Sky = NewGO<GameSky>(0);
				g_Sky->Init(mapLoc3[i].modelName, mapLoc3[i].position, mapLoc3[i].rotation);
				ChangeObject++;

			}

			else
			{
				mapchip[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				mapchip[NoMoveObject]->Init(mapLoc3[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);
				NoMoveObject++;
			}

		}
		mapchip[0]->SoundOnMachi();
		return true; //一回だけ呼ばれる
		break;
	case 3:

		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLoc4) / sizeof(mapLoc4[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLoc4[i].modelName, "Unity") == 0)
			{
				pos = mapLoc4[i].position;
				rot = mapLoc4[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(rot);
				ChangeObject++;

			}
			else if (strcmp(mapLoc4[i].modelName, "doa") == 0)
			{

				g_SC = NewGO<SceneChange>(0);
				g_SC->Init(mapLoc4[i].modelName, mapLoc4[i].position, mapLoc4[i].rotation);
				g_SC->setpos(mapLoc4[i].position);
				g_SC->Norender();
				ChangeObject++;

			}
			else if (strcmp(mapLoc4[i].modelName, "Sign_a") == 0)
			{

				g_shop = NewGO<shop>(0);
				g_shop->Init(mapLoc4[i].modelName, mapLoc4[i].position, mapLoc4[i].rotation);

				ChangeObject++;

			}
			else if (strcmp(mapLoc4[i].modelName, "maru") == 0)
			{

				g_Sky = NewGO<GameSky>(0);
				g_Sky->Init(mapLoc4[i].modelName, mapLoc4[i].position, mapLoc4[i].rotation);
				ChangeObject++;

			}

			else
			{
				mapchip[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				mapchip[NoMoveObject]->Init(mapLoc4[i].modelName, mapLoc4[i].position, mapLoc4[i].rotation);
				NoMoveObject++;
			}

		}
		mapchip[0]->SoundOnMachi();
		return true; //一回だけ呼ばれる
		break;
	
	}


}

void Map::Update()
{	

}