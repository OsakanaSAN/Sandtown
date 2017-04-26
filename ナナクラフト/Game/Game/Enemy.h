#pragma once
#include "Camera.h"
//#include "tkEngine/character/tkCharacterController.h"
class Enemy :
	public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();

	CVector3 Getpos()
	{
		return position;
	}

	CVector3 Setmove(CVector3 pos)
	{
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;


	}
	void AnimetionSet();

private:
	enum ANIME {
		RUN,
		STAND,
	};



	//�������烁���o�ϐ��B
	CSkinModel				skinModel;					//�X�L�����f���B
	CSkinModelData			skinModelData;				//�X�L�����f���f�[�^�B
	CAnimation              Animation;
	CVector3				position = { -2.0f,0.0f,-4.0f };	//���W�B
	CVector3                Qpos;
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[�B

	int                     OVER = -100;
	CQuaternion				m_rotion;

	CVector3                Rposition = { 3.0f,-3.0,1.0f };
	CLight                  All;        //�v���C���̃��C�g
	CLight                  PLight;


	int						currentAnimSetNo;
	bool					Isrun;
	bool					Ismove;
	bool					Isjump;
};
