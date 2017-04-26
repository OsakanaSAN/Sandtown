#pragma once
class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start()override;
	void Update();

};

