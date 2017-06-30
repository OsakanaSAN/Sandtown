
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
	void MapSelect();
	void setpos(CVector3 pos)
	{
		SCpos = pos;
	}
	void Norender()
	{
		Norend = true;
	}

	int GetMapNo()
	{
		return DungeonNo;
	}

	bool GetMapSelectflg()
	{
		return MapSelectflg;
	}
	void Setflg(bool flg)
	{
		Out = flg;
	}
private:

	CSoundSource*	m_sound_select;
	enum DungeonState
	{
		Dungeon,
		DungeonF2,
		DungeonF3,
	};

	DungeonState DungeonNo = Dungeon;
	CSprite		m_ComandBGSprite1;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture1;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite2;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture2;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite3;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture3;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite4;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture4;		//!<戦闘画面の選択のテクスチャ。

	//CSprite	m_ComandBGSprite5;		//!<戦闘画面の選択のスプライト。
	//CTexture	m_ComandBGTexture5;		//!<戦闘画面の選択のテクスチャ。

	//CSprite		m_ComandBGSprite6;	//!<戦闘画面の選択のスプライト。
	//CTexture	m_ComandBGTexture6;		//!<戦闘画面の選択のテクスチャ。

	//CSprite		m_ComandBGSprite7;		//!<戦闘画面の選択のスプライト。
	//CTexture	m_ComandBGTexture7;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_CasolBGSprite;		//!<戦闘画面の選択のスプライト。
	CTexture	m_CasolBGTexture;		//!<戦闘画面の選択のテクスチャ。

	CVector3	SCpos;

	CLight               Maplight;
	CSkinModel			 skinModel;		//スキンモデル。
	CSkinModelDataHandle skinModelData;	//スキンモデルデータ
	CMeshCollider		 meshCollider;	//メッシュコライダー。
	CRigidBody			 rigidBody;		//剛体。
	bool                 Norend = false;
	bool                 Out = false;

	int					MapNo = 0;

	CSprite				ButtonSprite;
	CTexture			ButtonTexture;
	CVector2			ButtonPos = { 0.0f,100.0f };
	bool				Cahange = false;
	bool				MapSelectflg = false;

	bool                RendButton = false;

};

extern SceneChange* g_SC;

