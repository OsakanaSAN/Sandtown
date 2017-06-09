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
		//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
		numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
		//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
		for (int i = 0; i < numObject; i++) {

			DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			DungeonMap[NoMoveObject]->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
			NoMoveObject++;

		}
		DungeonMap[0]->SoundOnMachi();
		return true; //��񂾂��Ă΂��
		break;

	case 2:
		//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
		numObject = sizeof(mapLocInfo2) / sizeof(mapLocInfo2[0]);
		//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
		for (int i = 0; i < numObject; i++) {

			DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			DungeonMap[NoMoveObject]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
			NoMoveObject++;

		}
		DungeonMap[0]->SoundOnMachi();
		return true; //��񂾂��Ă΂��
		break;
	case 3:
		//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
		numObject = sizeof(mapLocInfo3) / sizeof(mapLocInfo3[0]);
		//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
		for (int i = 0; i < numObject; i++) {

			DungeonMap[NoMoveObject] = NewGO<Mapchip>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			DungeonMap[NoMoveObject]->Init(mapLocInfo3[i].modelName, mapLocInfo3[i].position, mapLocInfo3[i].rotation);
			NoMoveObject++;

		}
		DungeonMap[0]->SoundOnMachi();
		return true; //��񂾂��Ă΂��
		break;


	}
}

void Dungeon::Update()
{

}