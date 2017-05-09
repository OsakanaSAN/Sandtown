#include "stdafx.h"
#include "Map2.h"
#include "Player.h"

extern Player* g_player;

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
	ChangeObject = 0;
}


Map2::~Map2()
{
	for (int i = 0;i < numObject - ChangeObject;i++) {
		DeleteGO(mapChip[i]);
	}
	for (int j = 0;j < ChangeObject;j++)
	{
		if (mining[j] != nullptr) {
			DeleteGO(mining[j]);
		}
	}

}

bool Map2::Start()
{
	
	//マップにいくつのオブジェクトが配置されているか調べる。
	numObject = sizeof(mapLocInfo2) / sizeof(mapLocInfo2[0]);
	//置かれているオブジェクトの数だけマップチップを生成する。

	
	for (int i = 0; i < numObject; i++) {
		if (strcmp(mapLocInfo2[i].modelName, "stone") == 0)
		{
			
			mining[ChangeObject] = NewGO<Mining>(0);
			mining[ChangeObject]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
			mining[ChangeObject]->setas(ChangeObject);
			ChangeObject++;
		}
		else if (strcmp(mapLocInfo2[i].modelName, "unity") == 0)
		{
			CVector3 pos = mapLocInfo2[i].position;
			CQuaternion prot = mapLocInfo2[i].rotation;

			g_player->Setpos2(pos);
			g_player->SetRot(prot);
			ChangeObject++;

		}

		else {
			mapChip[i] = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			mapChip[i]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
		}
	}
	
	mapChip[0]->SoundOnDoukutu();
	return true; //一回だけ呼ばれる


}

void Map2::Update()
{

}
void Map2::AsDete(int Dete)
{
	DeleteGO(mining[Dete]);
	mining[Dete] = nullptr;
}