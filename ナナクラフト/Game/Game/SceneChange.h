
#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"


class SceneChange :public IGameObject
{
public:
	SceneChange();
	~SceneChange();
	bool Start()override;
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void setpos(CVector3 pos)
	{
		SCpos = pos;
	}
	
private:

	CVector3 SCpos;

	CLight               Maplight;
	CSkinModel			 skinModel;		//�X�L�����f���B
	CSkinModelDataHandle skinModelData;	//�X�L�����f���f�[�^
	CMeshCollider		 meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			 rigidBody;		//���́B


};

extern SceneChange* g_SC;

