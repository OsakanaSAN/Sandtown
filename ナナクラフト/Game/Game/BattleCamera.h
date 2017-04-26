#pragma once
#include "BattlePlayer.h"

class BattleCamera :
	public IGameObject
{
public:
	BattleCamera();
	~BattleCamera();

	bool Start()override;
	void Update();



	const CMatrix& GetViewMatrix() const
	{
		return Bcamera.GetViewMatrix();
	}
	const CMatrix& GetProjectionMatrix() const
	{
		return Bcamera.GetProjectionMatrix();
	}
	const CCamera& GetCamera()const
	{
		return Bcamera;
	}



private:
	CCamera		Bcamera;	//ÉJÉÅÉâÅB

	CVector3	pos = { -5.0f,1.9f,-47.0f };
	CVector3	tag = { 2.0f,-2.0f,-35.0f };
	/*CVector3	Gamepos;
	CVector3	V;*/


	/*CCharacterController	characterController;
	CVector3				toPosition;
	float					angl = 0.0f;
	float					angl2 = 0.0f;*/

	int						MapID;


};

