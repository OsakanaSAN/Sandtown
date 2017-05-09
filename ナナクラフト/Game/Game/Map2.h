#pragma once
#include "Mapchip.h"
#include "Mining.h"


class Map2 : public IGameObject
{
public:
	Map2();
	~Map2();
	bool Start()override;
	void Update();
	void AsDete(int G);
private:
	int numObject;
	int ChangeObject;
	Mining* mining[4];
	Mapchip* mapChip[6];
};

