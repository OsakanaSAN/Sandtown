#include "stdafx.h"
#include "Map.h"
#include "Player.h"

extern Player* g_player;

struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* mapchip[5];

//�}�b�v�̔z�u���B
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
	//@todo for debug
	for (int i = 0;i < numObject - ChangeObject;i++)
	{
		DeleteGO(mapchip[i]);
	}

}

bool Map::Start()
{
	//@todo for debug
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	numObject= sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++) {
		

		if (strcmp(mapLocInfo[i].modelName, "unity") == 0  )
		{
			pos = mapLocInfo[i].position;
			rot = mapLocInfo[i].rotation;

			g_player->Setpos2(pos);
			g_player->SetRot(rot);
			
			ChangeObject++;

		}

		else
		{
			mapchip[i] = NewGO<Mapchip>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			mapchip[i]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}

	}
	
	return true; //��񂾂��Ă΂��


}

void Map::Update()
{	


}