#include "stdafx.h"
#include "GameSound.h"


GameSound::GameSound()
{
	
}


GameSound::~GameSound()
{
	if (bgmsound != NULL) {
		//NULL �łȂ���΃T�E���h�\�[�X�̃C���X�^���X����������Ă���̂ō폜����B 
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
		//NULL �łȂ���΃T�E���h�\�[�X�̃C���X�^���X����������Ă���̂ō폜����B 
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