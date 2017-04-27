#pragma once
#include "Mapchip.h"


class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start()override;
	void Update();

};



