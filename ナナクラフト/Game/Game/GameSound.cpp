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
	bgmsound->Play(0);

}
void GameSound::MachiSound()
{
	
	bgmsound = NewGO<CSoundSource>(0);
	bgmsound->Init("Assets/sound/Machi.wav");
	bgmsound->SetVolume(0.5);
	bgmsound->Play(0);

}