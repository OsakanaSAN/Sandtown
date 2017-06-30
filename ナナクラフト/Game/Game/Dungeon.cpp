#include "stdafx.h"
#include "Dungeon.h"
#include "SceneChange.h"
#include "Player.h"
#include "Mining.h"
#include "Enemy.h"
#include "particle.h"

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
DungeonMapInfo mapLocInfo4[] =
{
#include "Map/DungeonF4.h"
};
DungeonMapInfo mapLocInfo5[] =
{
#include "Map/DungeonF5.h"
};
DungeonMapInfo mapLocInfo6[] =
{
#include "Map/DungeonF6.h"
};
DungeonMapInfo mapLocInfo7[] =
{
#include "Map/DungeonF7.h"
};

int count = 0;

Dungeon::Dungeon()
{
	ChangeObject = 0;
	numObject = 0;
	NoMoveObject = 0;
	EnemyObjct = 0;
	//count = (g_random.GetRandInt() % 3 + 1);
	mapCount = g_SC->GetMapNo();
	g_particle = NewGO<particle>(0);
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
	g_particle->ParticleDelete();
}

bool Dungeon::Start()
{
	switch (mapCount) {
	case 0:
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
				g_particle->Particle(mapLocInfo[i].position, 1);//ダンジョン入り口パーティクル
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
				SceneChan->Setflg(true);
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

	case 1:
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
				g_particle->Particle(mapLocInfo2[i].position, 1);//ダンジョン入り口パーティクル
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
				SceneChan->Setflg(true);
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
	case 2:
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
				g_particle->Particle(mapLocInfo3[i].position, 1);//ダンジョン入り口パーティクル
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
				SceneChan->Setflg(true);
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
		return true;//一回だけ呼ばれる
		break;
	case 3:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo4) / sizeof(mapLocInfo4[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLocInfo4[i].modelName, "rock") == 0)
			{

				minings[ChangeObject] = NewGO<Mining>(0);
				minings[ChangeObject]->Init(mapLocInfo4[i].modelName, mapLocInfo4[i].position, mapLocInfo4[i].rotation);
				minings[ChangeObject]->setas(ChangeObject);
				ChangeObject++;
			}
			else if (strcmp(mapLocInfo4[i].modelName, "Unity") == 0)
			{
				CVector3 pos = mapLocInfo4[i].position;
				CQuaternion prot = mapLocInfo4[i].rotation;
				g_particle->Particle(mapLocInfo4[i].position, 1);
				g_player->Setpos2(pos);
				g_player->SetRot(prot);
				//NoRenderObjct++;
			}
			else if (strcmp(mapLocInfo4[i].modelName, "doa") == 0)
			{

				SceneChan = NewGO<SceneChange>(0);
				SceneChan->Init(mapLocInfo4[i].modelName, mapLocInfo4[i].position, mapLocInfo4[i].rotation);
				SceneChan->setpos(mapLocInfo4[i].position);
				SceneChan->Norender();
				NoRenderObjct++;
				SceneChan->Setflg(true);

			}
			else
			{
				DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				DungeonMap[NoMoveObject]->Init(mapLocInfo4[i].modelName, mapLocInfo4[i].position, mapLocInfo4[i].rotation);
				NoMoveObject++;
			}

		}

		DungeonMap[0]->SoundOnDoukutu();
		return true; //一回だけ呼ばれる
		break;
	case 4:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo5) / sizeof(mapLocInfo5[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			if (strcmp(mapLocInfo5[i].modelName, "rock") == 0)
			{

				minings[ChangeObject] = NewGO<Mining>(0);
				minings[ChangeObject]->Init(mapLocInfo5[i].modelName, mapLocInfo5[i].position, mapLocInfo5[i].rotation);
				minings[ChangeObject]->setas(ChangeObject);
				ChangeObject++;
			}
			else if (strcmp(mapLocInfo5[i].modelName, "Unity") == 0)
			{
				CVector3 pos = mapLocInfo5[i].position;
				CQuaternion prot = mapLocInfo5[i].rotation;
				g_particle->Particle(mapLocInfo5[i].position, 1);
				g_player->Setpos2(pos);
				g_player->SetRot(prot);
				//NoRenderObjct++;
			}
			else if (strcmp(mapLocInfo5[i].modelName, "doa") == 0)
			{

				SceneChan = NewGO<SceneChange>(0);
				SceneChan->Init(mapLocInfo5[i].modelName, mapLocInfo5[i].position, mapLocInfo5[i].rotation);
				SceneChan->setpos(mapLocInfo5[i].position);
				SceneChan->Norender();
				NoRenderObjct++;
				SceneChan->Setflg(true);

			}

			else
			{
				DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				DungeonMap[NoMoveObject]->Init(mapLocInfo5[i].modelName, mapLocInfo5[i].position, mapLocInfo5[i].rotation);
				NoMoveObject++;
			}

		}
		DungeonMap[0]->SoundOnDoukutu();
		return true;//一回だけ呼ばれる
		break;
	case 5:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo6) / sizeof(mapLocInfo6[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			if (strcmp(mapLocInfo6[i].modelName, "cry") == 0)
			{

				minings[ChangeObject] = NewGO<Mining>(0);
				minings[ChangeObject]->Init(mapLocInfo6[i].modelName, mapLocInfo6[i].position, mapLocInfo6[i].rotation);
				minings[ChangeObject]->setas(ChangeObject);
				ChangeObject++;
			}
			else if (strcmp(mapLocInfo6[i].modelName, "Unity") == 0)
			{
				CVector3 pos = mapLocInfo6[i].position;
				CQuaternion prot = mapLocInfo6[i].rotation;
				g_particle->Particle(mapLocInfo6[i].position, 1);
				g_player->Setpos2(pos);
				g_player->SetRot(prot);
				//NoRenderObjct++;
			}
			else if (strcmp(mapLocInfo6[i].modelName, "doa") == 0)
			{

				SceneChan = NewGO<SceneChange>(0);
				SceneChan->Init(mapLocInfo6[i].modelName, mapLocInfo6[i].position, mapLocInfo6[i].rotation);
				SceneChan->setpos(mapLocInfo6[i].position);
				SceneChan->Norender();
				NoRenderObjct++;
				SceneChan->Setflg(true);

			}

			else
			{
				DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				DungeonMap[NoMoveObject]->Init(mapLocInfo6[i].modelName, mapLocInfo6[i].position, mapLocInfo6[i].rotation);
				NoMoveObject++;
			}

		}
		DungeonMap[0]->SoundOnDoukutu();
		return true;//一回だけ呼ばれる
		break;
	case 6:
		//マップにいくつのオブジェクトが配置されているか調べる。
		numObject = sizeof(mapLocInfo7) / sizeof(mapLocInfo7[0]);
		//置かれているオブジェクトの数だけマップチップを生成する。
		for (int i = 0; i < numObject; i++) {

			if (strcmp(mapLocInfo7[i].modelName, "cry") == 0)
			{

				minings[ChangeObject] = NewGO<Mining>(0);
				minings[ChangeObject]->Init(mapLocInfo7[i].modelName, mapLocInfo7[i].position, mapLocInfo7[i].rotation);
				minings[ChangeObject]->setas(ChangeObject);
				ChangeObject++;
			}
			else if (strcmp(mapLocInfo7[i].modelName, "Unity") == 0)
			{
				CVector3 pos = mapLocInfo7[i].position;
				CQuaternion prot = mapLocInfo7[i].rotation;
				g_particle->Particle(mapLocInfo7[i].position, 1);
				g_player->Setpos2(pos);
				g_player->SetRot(prot);
				//NoRenderObjct++;
			}
			else if (strcmp(mapLocInfo7[i].modelName, "doa") == 0)
			{

				SceneChan = NewGO<SceneChange>(0);
				SceneChan->Init(mapLocInfo7[i].modelName, mapLocInfo7[i].position, mapLocInfo7[i].rotation);
				SceneChan->setpos(mapLocInfo7[i].position);
				SceneChan->Norender();
				NoRenderObjct++;
				SceneChan->Setflg(true);

			}

			else
			{
				DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
				//モデル名、座標、回転を与えてマップチップを初期化する。
				DungeonMap[NoMoveObject]->Init(mapLocInfo7[i].modelName, mapLocInfo7[i].position, mapLocInfo7[i].rotation);
				NoMoveObject++;
			}

		}
		DungeonMap[0]->SoundOnDoukutu();
		return true;//一回だけ呼ばれる
		break;

	}
	return true;

	
}

void Dungeon::Update()
{

}