#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "SceneChange.h"
#include "HUD.h"



struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* mapchip[10];
SceneChange* g_SC;

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
	
	for (int i = 0;i < numObject - ChangeObject;i++)
	{
		DeleteGO(mapchip[i]);
	}

	DeleteGO(g_SC);

	while (!mapchip[numObject-ChangeObject-1]->IsDead())
	{


	}


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

		else
		{
			mapchip[i] = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			mapchip[i]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}

	}
	

	mapchip[0]->SoundOnMachi();
	return true; //一回だけ呼ばれる


}

void Map::Update()
{	

}