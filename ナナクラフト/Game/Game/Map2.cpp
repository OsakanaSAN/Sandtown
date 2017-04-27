#include "stdafx.h"
#include "Map2.h"



struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};



//マップの配置情報。
SMapInfo mapLocInfo2[] = {
#include "locationInfo.h"
};

Map2::Map2()
{
}


Map2::~Map2()
{
	DeleteGO(mapChip);
}

bool Map2::Start()
{
	//マップにいくつのオブジェクトが配置されているか調べる。
	numObject = sizeof(mapLocInfo2) / sizeof(mapLocInfo2[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。


	for (int i = 0; i < numObject; i++) {
		if (strcmp(mapLocInfo2[i].modelName, "cube") == 0)
		{
			torch = NewGO<Torch>(0);
			torch->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
		}
		else {
			mapChip = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			mapChip->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
		}
	}

	return true; //一回だけ呼ばれる


}

void Map2::Update()
{

}