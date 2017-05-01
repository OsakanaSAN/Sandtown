#include "stdafx.h"
#include "Map2.h"



struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};



//�}�b�v�̔z�u���B
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
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	numObject = sizeof(mapLocInfo2) / sizeof(mapLocInfo2[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B


	for (int i = 0; i < numObject; i++) {
		if (strcmp(mapLocInfo2[i].modelName, "cube") == 0)
		{
			torch = NewGO<Torch>(0);
			torch->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
		}
		else {
			mapChip = NewGO<Mapchip>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			mapChip->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
		}
	}

	return true; //��񂾂��Ă΂��


}

void Map2::Update()
{

}