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
	//�|�W�V������n��
	CVector3 Getpos()
	{
		return position;
	}

	//�|�W�V�������Z�b�g����
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

	//�������Z�b�g
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
	
	void IsMoveSTOP()
	{
		IsMove = STOP;
	}
	void IsMoveSTART()
	{
		IsMove = START;
	}


	int GetMaxHp()const
	{
		return MaxHp;
	}

	int GetPHp()const
	{
		return PHp;
	}
	void StopSound()
	{
		runsound->Stop();
	}


private:
	enum ANIME {
		RUN,
		STAND,
	};

	enum IS {
		START,
		STOP,

	};

	IS         IsMove;
	//�������烁���o�ϐ��B
	CSkinModel				skinModel;					//�X�L�����f���B
	CSkinModelDataHandle	skinModelData;				//�X�L�����f���f�[�^�B
	CAnimation              Animation;
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				position;	//���W�B
	CVector3                Qpos;
	int                     OVER = -100;
	CQuaternion				m_rotion;

	CVector3                Rposition = { 3.0f,-3.0,1.0f };
	CLight                  All;        //�v���C���̃��C�g
	CLight                  PLight;
	
	int                    MaxHp = 100; //�ő�HP
	int                    PHp = 100;   //����HP


	CSoundSource*          runsound; //����


	int						currentAnimSetNo;
	bool					Isrun;
	bool					Ismove;
	bool					Isjump;

};
extern Player* g_player;