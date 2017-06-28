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

	bool GetInnflg()
	{
		return Innflg;
	}

private:

	CSoundSource*	m_sound_select;

	CSprite		m_ComandBGSprite1;		//!<選択のスプライト。
	CTexture	m_ComandBGTexture1;		//!<選択のテクスチャ。

	CSprite		m_ComandBGSprite2;		//!<選択のスプライト。
	CTexture	m_ComandBGTexture2;		//!<選択のテクスチャ。

	CSprite		m_ComandBGSprite3;		//!<選択のスプライト。
	CTexture	m_ComandBGTexture3;		//!<選択のテクスチャ。

	CSprite		m_CasolBGSprite;		//!<選択のスプライト。
	CTexture	m_CasolBGTexture;		//!<選択のテクスチャ。

	CSprite		m_TextSprite;		//!<選択のスプライト。
	CTexture	m_TextTexture;		//!<選択のテクスチャ。

	enum InnState
	{
		SREEP,
		NOSREEP,
	};
	InnState			innstate = SREEP;
	bool				Innflg = false;

	bool				Fadeflg = false;

	CLight              Maplight;
	CVector3            LightPos2;
	CVector3            Pointpos;

	CSkinModel				skinModel;		//スキンモデル。
	CSkinModelDataHandle	skinModelData;	//スキンモデルデータ。
	CMeshCollider			meshCollider;	//メッシュコライダー。
	CRigidBody				rigidBody;		//剛体。
	
};

extern Inn* g_Inn;