#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "BattleScene.h"
#include "Fade.h"
#include "GameSound.h"


GameScene* g_gamescene;
GameSound* g_sound;

TitleScene::TitleScene()
{
	g_sound = NewGO<GameSound>(0);
	PushSE = NewGO<CSoundSource>(0);
	PushSE->Init("Assets/sound/Push.wav");
}


TitleScene::~TitleScene()
{
	
	
	g_gameScene = NewGO<GameScene>(0);
	//DeleteGO(PushSE);
	
	
	
}

bool TitleScene::Start()
{

	m_titleBGTexture.Load("Assets/sprite/title2.png");
	m_titleBGSprite.Init(&m_titleBGTexture);
	m_titleBGSprite.SetSize({ 1920,1080 });

	m_titleBGTexture2.Load("Assets/sprite/casol2.png");
	m_titleBGSprite2.Init(&m_titleBGTexture2);
	m_titleBGSprite2.SetPosition({ -500,-350 });
	m_titleBGSprite2.SetSize({ 200,200 });

	/*m_titleBGTexture3.Load("Assets/sprite/START.png");
	m_titleBGSprite3.Init(&m_titleBGTexture3);
	m_titleBGSprite3.SetPosition({ 10,-100 });*/
	
	g_fade->StartFadeIn();

	//タイトルの音楽再生
	g_sound->TitleSound();

	return true;
}

void TitleScene::Update()
{

	float rStick_y = Pad(0).GetRStickYF();

	if (Pad(0).IsPress(enButtonUp) && GAME == NO)
	{
	
		m_titleBGTexture2.Release();
		m_titleBGTexture2.Load("Assets/sprite/casol2.png");
		m_titleBGSprite2.Init(&m_titleBGTexture2);
		m_titleBGSprite2.SetPosition({ -500,-100 });
		m_titleBGSprite2.SetSize({ 200,200 });
		GAME = START;
	}

	if (Pad(0).IsPress(enButtonDown) && GAME == START)
	{
		
		m_titleBGTexture2.Release();
		m_titleBGTexture2.Load("Assets/sprite/casol2.png");
		m_titleBGSprite2.Init(&m_titleBGTexture2);
		m_titleBGSprite2.SetPosition({ -500,-350 });
		m_titleBGSprite2.SetSize({ 200,200 });
		GAME = NO;


	}

	switch (GAME) {
	case START:
		switch (m_state) {
		case eStateWaitFadeIn:
			if (!g_fade->IsExecute()) {
				m_state = eStateRun;
			}
			break;


		case eStateRun:
			if (Pad(0).IsTrigger(enButtonStart)) {
				PushSE->Play(0);
				g_fade->StartFadeOut();
				m_state = eStateWaitFadeOut;
				g_sound->StopSound();
			}
			break;

		case eStateWaitFadeOut:
			if (!g_fade->IsExecute()) {
				DeleteGO(this);
				return;
			}
			break;

		}
		break;
	case NO:
		if (Pad(0).IsTrigger(enButtonStart))
		{
			exit(0);
		}
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	
		m_titleBGSprite.Draw(renderContext);
		m_titleBGSprite2.Draw(renderContext);
		/*m_titleBGSprite3.Draw(renderContext);*/
	
}