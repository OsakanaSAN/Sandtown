#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "BattleScene.h"
#include "Fade.h"


extern Fade* g_fade;
GameScene* g_gamescene;

TitleScene::TitleScene()
{
	
}


TitleScene::~TitleScene()
{
	
	//NewGO<BattleScene>(0);
	g_gameScene = NewGO<GameScene>(0);
	
}

bool TitleScene::Start()
{

	m_titleBGTexture.Load("Assets/sprite/Title.png");
	m_titleBGSprite.Init(&m_titleBGTexture);
	m_titleBGSprite.SetSize({ 1920,1080 });

	m_titleBGTexture2.Load("Assets/sprite/END2.png");
	m_titleBGSprite2.Init(&m_titleBGTexture2);
	

	m_titleBGTexture3.Load("Assets/sprite/START.png");
	m_titleBGSprite3.Init(&m_titleBGTexture3);
	m_titleBGSprite3.SetPosition({ 10,-100 });
	
	g_fade->StartFadeIn();

	return true;
}

void TitleScene::Update()
{

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_titleBGTexture3.Release();
		m_titleBGTexture3.Load("Assets/sprite/START2.png");
		m_titleBGSprite3.Init(&m_titleBGTexture3);
		m_titleBGTexture2.Release();
		m_titleBGTexture2.Load("Assets/sprite/END.png");
		m_titleBGSprite2.Init(&m_titleBGTexture2);
		//m_titleBGSprite2.SetPosition({ 10,-100 });

		GAME = START;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_titleBGTexture2.Release();
		m_titleBGTexture2.Load("Assets/sprite/END2.png");
		m_titleBGSprite2.Init(&m_titleBGTexture2);

		m_titleBGTexture3.Release();
		m_titleBGTexture3.Load("Assets/sprite/START.png");
		m_titleBGSprite3.Init(&m_titleBGTexture3);
		m_titleBGSprite3.SetPosition({ 10,-100 });

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
			if (GetAsyncKeyState('Q') & 0x8000) {
				g_fade->StartFadeOut();
				m_state = eStateWaitFadeOut;
			}
			break;

		case eStateWaitFadeOut:
			if (!g_fade->IsExecute()) {
				//フェード終わった。
				//ゲームシーンに遷移。
				//DeleteGO(bgmSource);
				//自分を削除。
				DeleteGO(this);
				return;
			}
			break;

		}
		break;
	case NO:
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			exit(0);
		}
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	
		m_titleBGSprite.Draw(renderContext);
		m_titleBGSprite2.Draw(renderContext);
		m_titleBGSprite3.Draw(renderContext);
	
}