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
	void Setpos2(CVector3 pos)
	{
		position = pos;
		//���[���h�s��̍X�V�B
		skinModel.Update(position, m_rotion, CVector3::One);
		
	}

	void Setpos()
	{
		characterController.SetPosition(Qpos);

	}


	void SetRot(CQuaternion PRot)
	{
		m_rotion = PRot;
		
	}


	void AngleSet();
	void AnimetionSet();

	void OVERset(int a)
	{
		OVER = a;
	}
	void Loadpos();


private:
	enum ANIME {
		RUN,
		STAND,
	};



	//�������烁���o�ϐ��B
	CSkinModel				skinModel;					//�X�L�����f���B
	CSkinModelData			skinModelData;				//�X�L�����f���f�[�^�B
	CAnimation              Animation;
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				position;	//���W�B
	CVector3                Qpos;

	int                     OVER = -100;
	CQuaternion				m_rotion;

	CVector3                Rposition = { 3.0f,-3.0,1.0f };
	CLight                  All;        //�v���C���̃��C�g
	CLight                  PLight;
	
	CSoundSource*          runsound;
	


	int						currentAnimSetNo;
	bool					Isrun;
	bool					Ismove;
	bool					Isjump;
};