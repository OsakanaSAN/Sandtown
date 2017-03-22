#include "stdafx.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Fade.h"
#include "Player.h"
#include "Camera.h"
#include "Map.h"


#define   Y_UP 150
#define   X_POS -650
#define   X2_POS -950

extern Fade* g_fade;
GameScene* g_gameScene = NULL;
Player* g_player;
Camera* g_gameCamera;
Map* g_Map;

GameScene::GameScene()
{
	g_player = NewGO<Player>(0);
	g_gameCamera = NewGO<Camera>(0);
	g_Map = NewGO<Map>(0);

	
}
GameScene::~GameScene()
{
	DeleteGO(g_player);
	//DeleteGO(g_gameCamera);
	NewGO<TitleScene>(0);
	
}

bool GameScene::Start()
{
	
	/*
	//背景表示
	Gametex.Load("Assets/sprite/Title.png");
	GameSprite.Init(&Gametex);
	GameSprite.SetSize({ 1920,1080 });
	

		//ライトを初期化。
		light.SetAmbinetLight(CVector3::One);
		//カメラを初期化。
		camera.SetPosition({ 0.0f, 0.0f, -700.0f });
		camera.SetNear(400.0f);
		camera.SetFar(1000.0f);
		camera.Update();
		*/

	
	if (g_player != nullptr && g_gameCamera != nullptr) {
		g_fade->StartFadeIn();
	}
		return true;

}

void GameScene::Update()
{
	
	 
		//タイトル画面に遷移する。
		switch (sets)
		{
		case in:
			if (Pad(0).IsTrigger(enButtonStart)) {
				g_fade->StartFadeOut();
				sets = out;
			}
			break;
		case out:
			if (!g_fade->IsExecute()) {
				DeleteGO(this);
			}
			break;

		}
	
	
}
/*!
*@brief	描画関数。
*/
void GameScene::Render(CRenderContext& renderContext)
{
	/*
	renderContext.SetRenderState(RS_ZWRITEENABLE, FALSE);
	GameSprite.Draw(renderContext);
	renderContext.SetRenderState(RS_ZWRITEENABLE, TRUE);
	*/
}




