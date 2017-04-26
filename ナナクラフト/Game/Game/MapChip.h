#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class Mapchip : public IGameObject
{
public:
	Mapchip();
	~Mapchip();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:
	CLight              Maplight;
	CSkinModel			skinModel;		//�X�L�����f���B
	CSkinModelData		skinModelData;	//�X�L�����f���f�[�^�B
	CMeshCollider		meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			rigidBody;		//���́B
	
	//bool BATTLE = false;

};

