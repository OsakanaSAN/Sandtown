#include "stdafx.h"
#include "Map.h"
#include "Mapchip.h"

struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

//マップの配置情報。
SMapInfo mapLocInfo[] = {
#include "locationinfo.h"
};


Map::Map()
{
}


Map::~Map()
{
}

bool Map::Start()
{
	//マップにいくつのオブジェクトが配置されているか調べる。
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。
	for (int i = 0; i < numObject; i++) {
		Mapchip* mapChip = NewGO<Mapchip>(0);
		//モデル名、座標、回転を与えてマップチップを初期化する。
		mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}

	return true; //一回だけ呼ばれる


}

void Map::Update()
{

}