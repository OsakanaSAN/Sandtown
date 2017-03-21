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
	const CMatrix& GetViewMatrix() const
	{
		return camera.GetViewMatrix();
	}
	const CMatrix& GetProjectionMatrix() const
	{
		return camera.GetProjectionMatrix();
	}

	//ここからメンバ変数。
	CCamera camera;	//カメラ。

	CVector3 pos = { 3.0f,  2.0f,  2.0f };
	CVector3 tag = { 1.0,1.0,1.0 };

	CCharacterController	characterController;
	CVector3 toPosition;
	float angl = 0.0f;
	float angl2 = 0.0f;

};


