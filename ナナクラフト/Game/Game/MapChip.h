#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class MapChip :
	public IGameObject
{
public:
	MapChip();
	~MapChip();

	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

	//�������烁���o�ϐ�
	CSkinModel			skinModel;		//�X�L�����f��
	CSkinModelData		skinModelData;	//�X�L�����f���f�[�^
	CLight                  All;
	CMeshCollider		meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			rigidBody;		//���́B
};

