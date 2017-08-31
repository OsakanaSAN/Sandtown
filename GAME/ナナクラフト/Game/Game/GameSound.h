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
	void BattleSound();
	void EnkauntoSound();
	void StopSound();
	void VolumeDown();
	void VolumeNormal();
	
private:

	CSoundSource*      bgmsound;
	CSoundSource*      EncSound;
};
extern GameSound* g_sound;
