#include "stdafx.h"
#include "Dungeon.h"
#include "SceneChange.h"
#include "Player.h"
#include "Mining.h"
#include "Enemy.h"


struct DungeonMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* DungeonMap[255];
SceneChange* SceneChan;
Mining* minings[255];
//Enemy* enemy[5];


DungeonMapInfo mapLocInfo[] =
{
#include "Map/DOUKUTU.h"
};
DungeonMapInfo mapLocInfo2[] =
{
#include "Map/DungeonF2.h"
};

DungeonMapInfo mapLocInfo3[] =

{
#include "Map/DungeonF3.h"
};

int count = 0;

Dungeon::Dungeon()
{
	ChangeObject = 0;
	numObject = 0;
	NoMoveObject = 0;
	EnemyObjct = 0;
	count = (g_random.GetRandInt() % 3 + 1);
	mapCount = count;
	
}

Dungeon::~Dungeon()
{
	for (int mn = 0;mn < ChangeObject;mn++)
	{
		DeleteGO(minings[mn]);
	}

	for (int map = 0;map < NoMoveObject;map++)
	{
		DeleteGO(DungeonMap[map]);
	}

	DeleteGO(SceneChan);

}

bool Dungeon::Start()
{
	switch (mapCount) {
	case 1:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			if (strcmp(mapLocInfo[i].modelName, "stone") == 0)
			{

				minings[ChangeObject] = NewGO<Mining>(0);
				minings[ChangeObject]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				minings[ChangeObject]->setas(ChangeObject);
				ChangeObject++;
			}
			else if (strcmp(mapLocInfo[i].modelName, "Unity") == 0)
			{
				CVector3 pos = mapLocInfo[i].position;
				CQuaternion prot = mapLocInfo[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(prot);
				//NoRenderObjct++;
			}
			else if (strcmp(mapLocInfo[i].modelName, "doa") == 0)
			{

				SceneChan = NewGO<SceneChange>(0);
				SceneChan->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				SceneChan->setpos(mapLocInfo[i].position);
				SceneChan->Norender();
				NoRenderObjct++;


			}

			else
			{
				DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				DungeonMap[NoMoveObject]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				NoMoveObject++;
			}

		}

		DungeonMap[0]->SoundOnDoukutu();

		return true; //一回だけ呼ばれる
		break;

	case 2:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo2) / sizeof(mapLocInfo2[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLocInfo2[i].modelName, "stone") == 0)
			{

				minings[ChangeObject] = NewGO<Mining>(0);
				minings[ChangeObject]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
				minings[ChangeObject]->setas(ChangeObject);
				ChangeObject++;
			}
			else if (strcmp(mapLocInfo2[i].modelName, "Unity") == 0)
			{
				CVector3 pos = mapLocInfo2[i].position;
				CQuaternion prot = mapLocInfo2[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(prot);
				//NoRenderObjct++;
			}
			else if (strcmp(mapLocInfo2[i].modelName, "doa") == 0)
			{

				SceneChan = NewGO<SceneChange>(0);
				SceneChan->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
				SceneChan->setpos(mapLocInfo2[i].position);
				SceneChan->Norender();
				NoRenderObjct++;


			}

			else
			{
				DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				DungeonMap[NoMoveObject]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
				NoMoveObject++;
			}

		}

		
		DungeonMap[0]->SoundOnDoukutu();
		return true; //一回だけ呼ばれる
		break;
	case 3:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo3) / sizeof(mapLocInfo3[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			if (strcmp(mapLocInfo3[i].modelName, "stone") == 0)
			{

				minings[ChangeObject] = NewGO<Mining>(0);
				minings[ChangeObject]->Init(mapLocInfo3[i].modelName, mapLocInfo3[i].position, mapLocInfo3[i].rotation);
				minings[ChangeObject]->setas(ChangeObject);
				ChangeObject++;
			}
			else if (strcmp(mapLocInfo3[i].modelName, "Unity") == 0)
			{
				CVector3 pos = mapLocInfo3[i].position;
				CQuaternion prot = mapLocInfo3[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(prot);
				//NoRenderObjct++;
			}
			else if (strcmp(mapLocInfo3[i].modelName, "doa") == 0)
			{

				SceneChan = NewGO<SceneChange>(0);
				SceneChan->Init(mapLocInfo3[i].modelName, mapLocInfo3[i].position, mapLocInfo3[i].rotation);
				SceneChan->setpos(mapLocInfo3[i].position);
				SceneChan->Norender();
				NoRenderObjct++;


			}

			else
			{
				DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				DungeonMap[NoMoveObject]->Init(mapLocInfo3[i].modelName, mapLocInfo3[i].position, mapLocInfo3[i].rotation);
				NoMoveObject++;
			}

		}
		DungeonMap[0]->SoundOnDoukutu();
		return true; //一回だけ呼ばれる
		break;


	}
}

void Dungeon::Update()
{

}