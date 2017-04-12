#include "stdafx.h"
#include "Map.h"
#include "Mapchip.h"

struct SMapInfo {
	const char* modelName;
	CVector3	position;
	CQuaternion	rotation;
};

//�}�b�v�̔z�u���B
SMapInfo mapLocInfo[] = {
#include "locationinfo.h"
};


Map::Map()
{
}


Map::~Map()
{
}

bool Map::Start()
{
	//�}�b�v�ɂ����̃I�u�W�F�N�g���z�u����Ă��邩���ׂ�B
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	//�u����Ă���I�u�W�F�N�g�̐������}�b�v�`�b�v�𐶐�����B
	for (int i = 0; i < numObject; i++) {
		Mapchip* mapChip = NewGO<Mapchip>(0);
		//���f�����A���W�A��]��^���ă}�b�v�`�b�v������������B
		mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
	}

	return true; //��񂾂��Ă΂��


}

void Map::Update()
{

}