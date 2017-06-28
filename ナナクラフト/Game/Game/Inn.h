#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

class Inn :
	public IGameObject
{
public:
	Inn();
	~Inn();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void InnSelect();
	void Setpos(CVector3 a)
	{
		LightPos2 = a;
	}


private:

	CSoundSource*	m_sound_select;

	CSprite		m_ComandBGSprite1;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture1;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_CasolBGSprite;		//!<戦闘画面の選択のスプライト。
	CTexture	m_CasolBGTexture;		//!<戦闘画面の選択のテクスチャ。
	enum InnState
	{
		SREEP,
		NOSREEP,
	};
	InnState			innstate = SREEP;
	CLight              Maplight;
	CVector3            LightPos2;
	CVector3            Pointpos;

	CSkinModel			skinModel;		//スキンモデル。
	CSkinModelDataHandle		skinModelData;	//スキンモデルデータ。
	CMeshCollider		meshCollider;	//メッシュコライダー。
	CRigidBody			rigidBody;		//剛体。

	bool				Innflg = false;
};

extern Inn* g_Inn;