#include "stdafx.h"
#include "Map.h"
#include "Player.h"

extern Player* g_player;

struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* mapchip[5];

//マップの配置情報。
SMapInfo mapLocInfo[] = {
#include "Map/mati.h"
};


Map::Map()
{
	ChangeObject = 0;
	numObject = 0;
}


Map::~Map()
{
	//@todo for debug
	for (int i = 0;i < numObject - ChangeObject;i++)
	{
		DeleteGO(mapchip[i]);
	}

}

bool Map::Start()
{
	//@todo for debug
	//マップにいくつのオブジェクトが配置されているか調べる。
	numObject= sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++) {
		

		if (strcmp(mapLocInfo[i].modelName, "unity") == 0  )
		{
			pos = mapLocInfo[i].position;
			rot = mapLocInfo[i].rotation;

			g_player->Setpos2(pos);
			g_player->SetRot(rot);
			
			ChangeObject++;

		}

		else
		{
			mapchip[i] = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			mapchip[i]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}

	}
	
	return true; //一回だけ呼ばれる


}

void Map::Update()
{	


}