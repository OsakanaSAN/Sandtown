#pragma once
#include "Mapchip.h"

class Dungeon : public IGameObject
{
public:
	Dungeon();
	~Dungeon();
	bool Start()override;
	void Update();


	void MapSelect(int Map)
	{
		mapCount = Map;

	}
private:
	int numObject;
	int ChangeObject;
	int NoMoveObject;
	int NoRenderObjct;
	int EnemyObjct;
	int mapCount;

};

