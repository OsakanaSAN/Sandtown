#pragma once
class GameSound :public IGameObject
{
public:
	GameSound();
	~GameSound();
	bool Start()override;
	void Update();
	void TitleSound();
	void MachiSound();
	void DoukutuSound();
	void StopSound();
	
private:

	CSoundSource*      bgmsound;
};

