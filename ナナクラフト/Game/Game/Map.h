#pragma once
#include "Mapchip.h"


class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start()override;
	void Update();
	CVector3 pos;
	CQuaternion rot;

private:
	int numObject;
	int ChangeObject;
	int NoMoveObject;
	
	bool One = false;


	int         RecvGold = 50;
	float       RecvHP = 100;

	int         RecvGoldJ = 0;
	float       RecvHPJ = 0;

};



