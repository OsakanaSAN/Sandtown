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
	CVector3 Getpos()
	{
		return position;
	}

	void Setpos()
	{
		characterController.SetPosition(Qpos);

	}

	void AngleSet();
	void AnimetionSet();

	void OVERset(int a)
	{
		OVER = a;
	}


private:
	enum ANIME {
		RUN,
		STAND,
	};



	//ここからメンバ変数。
	CSkinModel				skinModel;					//スキンモデル。
	CSkinModelData			skinModelData;				//スキンモデルデータ。
	CAnimation              Animation;
	CCharacterController	characterController;		//キャラクタ―コントローラー。
	CVector3				position = { 0.0f,0.0f,0.0f };	//座標。
	CVector3                Qpos;

	int                     OVER = -100;
	CQuaternion				m_rotion;

	CVector3                Rposition = { 3.0f,-3.0,1.0f };
	CLight                  All;        //プレイヤのライト
	float					angle = 90;

	int						currentAnimSetNo;
	bool					Isrun;
	bool					Ismove;
	bool					Isjump;
};