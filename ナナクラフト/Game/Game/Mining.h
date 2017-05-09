#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class Mining : public IGameObject
{
public:
	Mining();
	~Mining();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Setpos(CVector3 a)
	{
		LightPos2 = a;
	}
	void setas(int D)
	{
		asnumber = D;
	}

private:
	CLight              Maplight;
	CVector3            LightPos2;
	CVector3            Pointpos;

	CSkinModel			skinModel;		//スキンモデル。
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。
	int                 asnumber;

};

