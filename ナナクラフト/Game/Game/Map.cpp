#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "SceneChange.h"
#include "HUD.h"
#include "GameSky.h"
#include "shop.h"


struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* mapchip[255];
SceneChange* g_SC;
GameSky*     g_Sky;
shop*		g_shop;

//�}�b�v�̔z�u���B
SMapInfo mapLocInfo[] = {
#include "Map/test3.h"
};
SMapInfo mapLoc2[] = {
#include "Map/test4.h"
};
int      MapCount = 0;

Map::Map()
{
	ChangeObject = 0;
	numObject = 0;
	NoMoveObject = 0;
}


Map::~Map()
{
	
	for (int i = 0;i < NoMoveObject;i++)
	{
		DeleteGO(mapchip[i]);
	}

	MapCount = 1;

	DeleteGO(g_SC);
	DeleteGO(g_Sky);
	DeleteGO(g_shop);

}

bool Map::Start()
{
	switch (MapCount)
	{
	case 0:
		//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
		numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
		//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLocInfo[i].modelName, "Unity") == 0)
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
				g_SC->Norender();
				ChangeObject++;

			}
			else if (strcmp(mapLocInfo[i].modelName, "Sign_a") == 0)
			{

				g_shop = NewGO<shop>(0);
				g_shop->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);

				ChangeObject++;

			}
			else if (strcmp(mapLocInfo[i].modelName, "maru") == 0)
			{

				g_Sky = NewGO<GameSky>(0);
				g_Sky->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				ChangeObject++;

			}

			else
			{
				mapchip[NoMoveObject] = NewGO<Mapchip>(0);
				//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
				mapchip[NoMoveObject]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
				NoMoveObject++;
			}

		}
		mapchip[0]->SoundOnMachi();
		return true; //��񂾂��Ă΂��
		break;
	case 1:

		//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
		numObject = sizeof(mapLoc2) / sizeof(mapLoc2[0]);
		//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
		for (int i = 0; i < numObject; i++) {


			if (strcmp(mapLoc2[i].modelName, "Unity") == 0)
			{
				pos = mapLoc2[i].position;
				rot = mapLoc2[i].rotation;

				g_player->Setpos2(pos);
				g_player->SetRot(rot);
				ChangeObject++;

			}
			else if (strcmp(mapLoc2[i].modelName, "doa") == 0)
			{

				g_SC = NewGO<SceneChange>(0);
				g_SC->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);
				g_SC->setpos(mapLoc2[i].position);
				g_SC->Norender();
				ChangeObject++;

			}
			else if (strcmp(mapLoc2[i].modelName, "Sign_a") == 0)
			{

				g_shop = NewGO<shop>(0);
				g_shop->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);

				ChangeObject++;

			}
			else if (strcmp(mapLoc2[i].modelName, "maru") == 0)
			{

				g_Sky = NewGO<GameSky>(0);
				g_Sky->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);
				ChangeObject++;

			}

			else
			{
				mapchip[NoMoveObject] = NewGO<Mapchip>(0);
				//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
				mapchip[NoMoveObject]->Init(mapLoc2[i].modelName, mapLoc2[i].position, mapLoc2[i].rotation);
				NoMoveObject++;
			}

		}
		mapchip[0]->SoundOnMachi();
		return true; //��񂾂��Ă΂��
		break;

	}


}

void Map::Update()
{	

}