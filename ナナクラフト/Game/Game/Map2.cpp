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
	for (int i = 0;i < 6;i++) {
		DeleteGO(mapChip[i]);
	}
	for (int j = 0;j < 4;j++)
	{
		if (mining[j] != nullptr) {
			DeleteGO(mining[j]);
		}
	}

}

bool Map2::Start()
{
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	numObject = sizeof(mapLocInfo2) / sizeof(mapLocInfo2[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B

	int J = 0;
	for (int i = 0; i < numObject; i++) {
		if (strcmp(mapLocInfo2[i].modelName, "stone") == 0)
		{
			
			mining[J] = NewGO<Mining>(0);
			mining[J]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
			mining[J]->setas(J);
			J++;
		}
		else {
			mapChip[i] = NewGO<Mapchip>(0);
			//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
			mapChip[i]->Init(mapLocInfo2[i].modelName, mapLocInfo2[i].position, mapLocInfo2[i].rotation);
		}
	}

	return true; //��񂾂��Ă΂��


}

void Map2::Update()
{

}
void Map2::AsDete(int Dete)
{
	DeleteGO(mining[Dete]);
	mining[Dete] = nullptr;
}