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

	CSprite		m_ComandBGSprite1;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture1;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_CasolBGSprite;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_CasolBGTexture;		//!<�퓬��ʂ̑I���̃e�N�X�`���B
	enum InnState
	{
		SREEP,
		NOSREEP,
	};
	InnState			innstate = SREEP;
	CLight              Maplight;
	CVector3            LightPos2;
	CVector3            Pointpos;

	CSkinModel			skinModel;		//�X�L�����f���B
	CSkinModelDataHandle		skinModelData;	//�X�L�����f���f�[�^�B
	CMeshCollider		meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			rigidBody;		//���́B

	bool				Innflg = false;
};

extern Inn* g_Inn;