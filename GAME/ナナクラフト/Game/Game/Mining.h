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
	void PostRender(CRenderContext& renderContet);
	void Setpos(CVector3 a)
	{
		LightPos2 = a;
	}
	void setas(int D)
	{
		asnumber = D;
	}


private:
	enum ItemRender
	{
		Get,
		NoGet,
	};
	int				ItemRender = NoGet;

	CSprite     IconSeatSprite;
	CTexture    IconSeatTexture;
	CVector2    Iconseatpos = { 0.0f,0.0f };

	CSprite			ButtonSprite;
	CTexture        ButtonTexture;
	CVector2        ButtonPos = { 0.0f,100.0f };

	bool            minigs = false;

	CSoundSource* m_sound_bgm_battle;

	CLight              Maplight;
	CVector3            LightPos2;
	CVector3            Pointpos;

	CSkinModel			skinModel;		//�X�L�����f���B
	CSkinModelDataHandle		skinModelData;	//�X�L�����f���f�[�^�B
	CMeshCollider		meshCollider;	//���b�V���R���C�_�[�B
	CRigidBody			rigidBody;		//���́B

	int                 asnumber;
	int                 minigexp = 5;
	int                 minigcount = 0; //�̌@�ł�����
	const float FADE_TIME_ITEM = 0.5f;		//!<�t�F�[�h�A�E�g�̎��ԁB(�P�ʁF�b)


	float m_timer = 0.0f;
	float S_timer = 0.0f; //������Ƃ�����������\��������
	
};

