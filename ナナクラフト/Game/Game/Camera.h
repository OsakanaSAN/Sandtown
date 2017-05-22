#pragma once
#include "Player.h"

class Camera : public IGameObject
{

public:

	

	//ここからメンバ関数。
	Camera();
	~Camera();
	bool Start()override;
	void Update();
	
	void TpsCamera();
	void BattleCamera();
	void PlayerBatlleCamera(CVector3 ta);

	const CMatrix& GetViewMatrix() const
	{
		return camera.GetViewMatrix();
	}
	const CMatrix& GetProjectionMatrix() const
	{
		return camera.GetProjectionMatrix();
	}
	const CCamera& GetCamera()const
	{
		return camera;
	}
	void ChangeStop()
	{
		scene = STOP;
	}
	void ChangeStart()
	{
		scene = START;
	}
	CVector3 BGetPos()
	{
		 return Battlepos;
	}

	CVector3 GetPos()
	{
		return pos;
	}

private:
	CCamera camera;	//カメラ。

	CVector3 pos = { 1.0f,  2.0f,  3.0f };
	CVector3 tag = { 1.0,1.0,1.0 };
	CVector3 BattlePlayerCameraPos = { 1.0f,0.0f,1.0f };

	CVector3	Battlepos = { -5.0f,1.9f,-47.0f };
	CVector3	Battletag = { 2.0f,-2.0f,-35.0f };

	CVector3 Gamepos;
	CVector3 V;


	CCharacterController	characterController;
	CVector3 toPosition;
	float angl = 0.0f;
	float angl2 = 0.0f;

	enum SECNE
	{
		START,
		STOP,

	};
	
	SECNE   scene = START;

};
extern Camera* g_gameCamera;

