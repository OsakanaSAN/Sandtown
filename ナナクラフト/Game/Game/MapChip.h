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
	void SoundOnMachi();
	void SoundOnDoukutu();

private:
	CLight               Maplight;
	CSkinModel			 skinModel;		//スキンモデル。
	CSkinModelDataHandle skinModelData;	//スキンモデルデータ
	CMeshCollider		 meshCollider;	//メッシュコライダー。
	CRigidBody			 rigidBody;		//剛体。
	CVector3             Lightpos;
	
	CVector3 li;
	
	


};

