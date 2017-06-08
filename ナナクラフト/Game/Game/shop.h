#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"
class shop :
	public IGameObject
{
public:
	shop();
	~shop();
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
	enum State
	{
		A,
		C,
		D
	};
	int state = A;
	CSprite		m_ComandBGSprite1;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture1;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite2;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture2;		//!<戦闘画面の選択のテクスチャ。


	CSprite		m_ComandBGSprite3;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture3;		//!<戦闘画面の選択のテクスチャ。
	
	CSprite		m_CasolBGSprite5;		//!<戦闘画面の選択のスプライト。
	CTexture	m_CasolBGTexture5;		//!<戦闘画面の選択のテクスチャ。


	CSkinModel			skinModel;		//スキンモデル。
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。

	bool shopflg = false;
};

