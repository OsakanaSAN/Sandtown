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
	int NoRenderObjct;
	int NoMoveObject;

	
};
extern Map2*   g_map2;

