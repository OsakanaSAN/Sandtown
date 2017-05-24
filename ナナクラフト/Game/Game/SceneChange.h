
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
	void Norender()
	{
		Norend = true;
	}
	
private:

	CVector3 SCpos;

	CLight               Maplight;
	CSkinModel			 skinModel;		//スキンモデル。
	CSkinModelDataHandle skinModelData;	//スキンモデルデータ
	CMeshCollider		 meshCollider;	//メッシュコライダー。
	CRigidBody			 rigidBody;		//剛体。
	bool                 Norend = false;

};

extern SceneChange* g_SC;

