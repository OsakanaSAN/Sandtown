#include "stdafx.h"
#include "Dungeon.h"


struct DungeonMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* DungeonMap[255];

DungeonMapInfo mapLocInfo[] =
{
#include "Map/DungeonF3.h"
};
DungeonMapInfo mapLocInfo2[] =
{
#include "Map/DungeonF5.h"
};

DungeonMapInfo mapLocInfo3[] =

{
#include "Map/DungeonF7.h"
};

int count = 2;

Dungeon::Dungeon()
{
	ChangeObject = 0;
	numObject = 0;
	NoMoveObject = 0;
	mapCount = count;
}

Dungeon::~Dungeon()
{

}

bool Dungeon::Start()
{
	switch (mapCount) {
	case 1:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			DungeonMap[NoMoveObject]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			NoMoveObject++;

		}
		DungeonMap[0]->SoundOnMachi();
		return true; //一回だけ呼ばれる
		break;

	case 2:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo2) / sizeof(mapLocInfo2[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			DungeonMap[NoMoveObject]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
			NoMoveObject++;

		}
		DungeonMap[0]->SoundOnMachi();
		return true; //一回だけ呼ばれる
		break;
	case 3:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo3) / sizeof(mapLocInfo3[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			DungeonMap[NoMoveObject]->Init(mapLocInfo3[i].modelName, mapLocInfo3[i].position, mapLocInfo3[i].rotation);
			NoMoveObject++;

		}
		DungeonMap[0]->SoundOnMachi();
		return true; //一回だけ呼ばれる
		break;


	}
}

void Dungeon::Update()
{

}