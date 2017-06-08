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
	CSprite		m_ComandBGSprite1;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture1;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite2;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture2;		//!<�퓬��ʂ̑I���̃e�N�X�`���B


	CSprite		m_ComandBGSprite3;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture3;		//!<�퓬��ʂ̑I���̃e�N�X�`���B
	
	CSprite		m_CasolBGSprite5;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_CasolBGTexture5;		//!<�퓬��ʂ̑I���̃e�N�X�`���B


	CSkinModel			skinModel;		//�X�L�����f���B
	CSkinModelDataHandle		skinModelData;	//�X�L�����f���f�[�^�B
	CMeshCollider		meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			rigidBody;		//���́B

	bool shopflg = false;
};

