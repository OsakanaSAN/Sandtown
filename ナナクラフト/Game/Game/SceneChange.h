
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
	CSprite		m_ComandBGSprite1;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture1;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite2;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture2;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite3;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture3;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite4;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture4;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	//CSprite	m_ComandBGSprite5;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	//CTexture	m_ComandBGTexture5;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	//CSprite		m_ComandBGSprite6;	//!<�퓬��ʂ̑I���̃X�v���C�g�B
	//CTexture	m_ComandBGTexture6;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	//CSprite		m_ComandBGSprite7;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	//CTexture	m_ComandBGTexture7;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_CasolBGSprite;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_CasolBGTexture;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CVector3	SCpos;

	CLight               Maplight;
	CSkinModel			 skinModel;		//�X�L�����f���B
	CSkinModelDataHandle skinModelData;	//�X�L�����f���f�[�^
	CMeshCollider		 meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			 rigidBody;		//���́B
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

