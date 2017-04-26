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



private:
	CCamera camera;	//カメラ。

	CVector3 pos = { 1.0f,  2.0f,  3.0f };
	CVector3 tag = { 1.0,1.0,1.0 };
	CVector3 Gamepos;
	CVector3 V;


	CCharacterController	characterController;
	CVector3 toPosition;
	float angl = 0.0f;
	float angl2 = 0.0f;


	


};


