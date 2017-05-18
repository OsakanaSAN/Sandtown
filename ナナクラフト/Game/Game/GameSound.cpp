#include "stdafx.h"
#include "GameSound.h"


GameSound::GameSound()
{
	
}


GameSound::~GameSound()
{
	if (bgmsound != NULL) {
		//NULL でなければサウンドソースのインスタンスが生成されているので削除する。 
		DeleteGO(bgmsound);
	}

}

bool GameSound::Start()
{

	
	return true;
}

void GameSound::Update()
{

}
void GameSound::StopSound()
{
	if (bgmsound != NULL) {
		//NULL でなければサウンドソースのインスタンスが生成されているので削除する。 
		DeleteGO(bgmsound);
	}

}

void GameSound::TitleSound()
{
	bgmsound = NewGO<CSoundSource>(0);
	bgmsound->Init("Assets/sound/Title.wav");
	bgmsound->Play(1);

}
void GameSound::MachiSound()
{
	
	bgmsound = NewGO<CSoundSource>(0);
	bgmsound->Init("Assets/sound/Machi.wav");
	bgmsound->SetVolume(1.0);
	bgmsound->Play(1);

}
void GameSound::DoukutuSound()
{
	bgmsound = NewGO<CSoundSource>(0);
	bgmsound->Init("Assets/sound/cave.wav");
	bgmsound->SetVolume(0.5);
	bgmsound->Play(1);

}
void GameSound::BattleSound()
{
	bgmsound = NewGO<CSoundSource>(0);
	bgmsound->Init("Assets/sound/battle.wav");
	bgmsound->SetVolume(1.0);
	bgmsound->Play(1);

}
void GameSound::VolumeDown()
{
	bgmsound->SetVolume(0.5f);
}
void GameSound::VolumeNormal()
{
	bgmsound->SetVolume(1.0f);
}