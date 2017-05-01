#pragma once
#include "Mapchip.h"
#include "Torch.h"


class Map2 : public IGameObject
{
public:
	Map2();
	~Map2();
	bool Start()override;
	void Update();

private:
	int numObject;
	Torch* torch;
	Mapchip* mapChip;
};

