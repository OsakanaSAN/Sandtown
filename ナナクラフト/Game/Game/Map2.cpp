#include "stdafx.h"
#include "Map2.h"
#include "Player.h"
#include "SceneChange.h"



struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

SceneChange* SC2;
Mining* mining[255];
Mapchip* mapChip[255];

//マップの配置情報。
SMapInfo mapLocInfo2[] = {
#include "Map/DOUKUTU.h";
};

Map2::Map2()
{

	ChangeObject = 0;0;
	NoRenderObjct = 0;
	NoMoveObject = 0;

}


Map2::~Map2()
{
	for (int i = 0;i < NoMoveObject;i++) {
		DeleteGO(mapChip[i]);
	}

	for (int j = 0;j < ChangeObject;j++)
	{
		if (mining[j] != nullptr) {
			DeleteGO(mining[j]);
		}
	}
	DeleteGO(SC2);

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
		else if (strcmp(mapLocInfo2[i].modelName, "Unity") == 0)
		{
			CVector3 pos = mapLocInfo2[i].position;
			CQuaternion prot = mapLocInfo2[i].rotation;

			g_player->Setpos2(pos);
			g_player->SetRot(prot);
			//ChangeObject++;
			NoRenderObjct++;
		}
		else if (strcmp(mapLocInfo2[i].modelName, "doa") == 0)
		{

			SC2 = NewGO<SceneChange>(0);
			SC2->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
			SC2->setpos(mapLocInfo2[i].position);
			SC2->Norender();
			//ChangeObject++;
			NoRenderObjct++;


		}

		else {
			mapChip[NoMoveObject] = NewGO<Mapchip>(0);
			//モデル名、座標、回転を与えてマップチップを初期化する。
			mapChip[NoMoveObject]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
			NoMoveObject++;
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