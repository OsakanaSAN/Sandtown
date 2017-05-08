#include "stdafx.h"
#include "Map.h"


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
}


Map::~Map()
{
	for (int i = 0;i < 5;i++)
	{
		DeleteGO(mapchip[i]);
	}

}

bool Map::Start()
{
	//マップにいくつのオブジェクトが配置されているか調べる。
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++) {
		 mapchip[i] = NewGO<Mapchip>(0);
		//モデル名、座標、回転を与えてマップチップを初期化する。
		mapchip[i]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}

	return true; //一回だけ呼ばれる


}

void Map::Update()
{

}