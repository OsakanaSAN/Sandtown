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
	
	bool One = false;

};



