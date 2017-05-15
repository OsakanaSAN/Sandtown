#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "Camera.h"


class Player : public IGameObject
{
public:

	//ここからメンバ関数。
	Player();
	~Player();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	void Move();
	//ポジションを渡す
	CVector3 Getpos()
	{
		return position;
	}

	//ポジションをセットする
	void Setpos2(CVector3 pos)
	{
		position = pos;
		//ワールド行列の更新。
		skinModel.Update(position, m_rotion, CVector3::One);
		
	}

	void Setpos()
	{
		characterController.SetPosition(Qpos);

	}

	//向きをセット
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
	//ここからメンバ変数。
	CSkinModel				skinModel;					//スキンモデル。
	CSkinModelDataHandle	skinModelData;				//スキンモデルデータ。
	CAnimation              Animation;
	CCharacterController	characterController;		//キャラクタ―コントローラー。
	CVector3				position;	//座標。
	CVector3                Qpos;
	int                     OVER = -100;
	CQuaternion				m_rotion;

	CVector3                Rposition = { 3.0f,-3.0,1.0f };
	CLight                  All;        //プレイヤのライト
	CLight                  PLight;
	
	int                    MaxHp = 100; //最大HP
	int                    PHp = 100;   //今のHP


	CSoundSource*          runsound; //足音


	int						currentAnimSetNo;
	bool					Isrun;
	bool					Ismove;
	bool					Isjump;

};
extern Player* g_player;