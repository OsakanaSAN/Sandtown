#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Camera.h"

class Player : public IGameObject
{
public:

	//�������烁���o�֐��B
	Player();
	~Player();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();
	CVector3 Getpos()
	{
		return position;
	}

	void Setpos()
	{
		characterController.SetPosition(Qpos);

	}

	void OVERset(int a)
	{
		OVER = a;
	}


private:
	//�������烁���o�ϐ��B
	CSkinModel				skinModel;					//�X�L�����f���B
	CSkinModelData			skinModelData;				//�X�L�����f���f�[�^�B
	CAnimation              Animation;
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				position = { 3.0f,-4.0f,1.0f };	//���W�B
	CVector3                Qpos;

	int                     OVER = -100;
	CQuaternion				m_rotion;

	CVector3                Rposition = { 3.0f,-3.0,1.0f };
	CLight                  All;        //�v���C���̃��C�g
	float					angle = 90;

	int						currentAnimSetNo;
	bool					Isrun;
	bool					Ismove;
	bool					Isjump;
};