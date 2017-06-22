#pragma once
#include "Player.h"
#include "tkEngine/camera/tkSpringCamera.h"
#include "tkEngine/camera/tkCameraCollisionSolver.h"

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
	void PlayerBatlleCamera();
	void EnemyBattleCamera();

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
	CCameraCollisionSolver  cameraCollisionSolver;


	CVector3 pos = { 0.0f,  2.0f,  3.0f };
	CVector3 tag = { 1.0,1.0,1.0 };
	CVector3 BattlePlayerCameraPos = { -1.5f,0.0f,1.0f };
	CVector3 BattleEnemyCameraPos = { -0.0f,52.0f,-3.0f };

	CVector3	Battlepos = { -4.0f,52.0f,-14.0f };
	CVector3	Battletag = {  2.0f,51.0f,-5.0f };

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

