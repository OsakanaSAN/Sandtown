#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "SceneChange.h"
#include "HUD.h"



struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

Mapchip* mapchip[255];
SceneChange* g_SC;

//�}�b�v�̔z�u���B
SMapInfo mapLocInfo[] = {
#include "Map/mati.h"
};


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

	DeleteGO(g_SC);

	/*while (!mapchip[numObject-ChangeObject-1]->IsDead())
	{


	}*/


}

bool Map::Start()
{

	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	numObject= sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++) {
		

		if (strcmp(mapLocInfo[i].modelName, "Unity") == 0  )
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


}

void Map::Update()
{	

}