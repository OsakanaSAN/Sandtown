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


Map::Map()
{
	ChangeObject = 0;
	numObject = 0;
	NoMoveObject = 0;
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

	//マップにいくつのオブジェクトが配置されているか調べる。
	numObject= sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++) {
		

		if (strcmp(mapLocInfo[i].modelName, "Unity") == 0  )
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
			ChangeObject++;

		}
		else if (strcmp(mapLocInfo[i].modelName, "ken") == 0)
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


}

void Map::Update()
{	

}