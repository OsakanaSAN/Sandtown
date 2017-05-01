#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class Torch : public IGameObject
{
public:
	Torch();
	~Torch();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Setpos(CVector3 a)
	{
		LightPos2 = a;
	}

private:
	CLight              Maplight;
	CVector3            LightPos2;
	CVector3            Pointpos;

	CSkinModel			skinModel;		//スキンモデル。
	CSkinModelData		skinModelData;	//スキンモデルデータ。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。

};

