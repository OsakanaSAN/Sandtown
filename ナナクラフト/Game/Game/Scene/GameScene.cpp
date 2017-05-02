#include "stdafx.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "BattleScene.h"
#include "Fade.h"
#include "Player.h"
#include "Camera.h"
#include "Map.h"
#include "Map2.h"
//#include "HUD.h"



#define   Y_UP 150
#define   X_POS -650
#define   X2_POS -950

extern Fade* g_fade;
GameScene* g_gameScene = NULL;

Player* g_player = nullptr;
Camera* g_gameCamera = nullptr;
Map*    g_map = nullptr;
Map2*   g_map2 = nullptr;
BattleScene* g_battleScene = nullptr;
//HUD*    g_Hud = nullptr;

GameScene::GameScene()
{

	//g_Hud = NewGO<HUD>(0);
	g_map = NewGO<Map>(0);
	g_player = NewGO<Player>(0);
	g_gameCamera = NewGO<Camera>(0);
	
	mapscene = MACHI;
	scenes = STOP;

	
}
GameScene::~GameScene()
{

	DeleteGO(g_player);
	DeleteGO(g_map);
	DeleteGO(g_gameCamera);
	NewGO<BattleScene>(0);
	
}

bool GameScene::Start()
{
	

	
	if (g_player != nullptr && g_gameCamera != nullptr) {
		g_fade->StartFadeIn();
	}
		return true;

}

void GameScene::Update()
{

	switch (scenes)
	{
	case STOP:
		//É^ÉCÉgÉãâÊñ Ç…ëJà⁄Ç∑ÇÈÅB

		
			if (GetAsyncKeyState('R') & 0x8000)
			{
				//g_fade->StartFadeOut();
				DeleteGO(g_player);
				
				g_battleScene = NewGO<BattleScene>(0);
				g_gameCamera->BattleCamera();
				g_gameCamera->ChangeStop();    //ÉJÉÅÉâÇÃçXêVÇé~ÇﬂÇÈ
			}
		if (mapscene == Battle)
		{
			if (g_battleScene != nullptr  )
			{

				g_player = nullptr;
				//g_fade->StartFadeIn();
				mapscene = DOUKUTU;
			}

		}

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
				DeteScene();
				sets = in;
			}
			break;

		}


		break;


		//ì¥åAÇ…ëJà⁄
	case DOUKUTU:

		while (scenes != STOP)
		{

			if (g_map2 == nullptr)
			{
				g_map2 = NewGO<Map2>(0);
				g_player = NewGO<Player>(0);
			}

			else
			{
				g_fade->StartFadeIn();
				scenes = STOP;
				mapscene = DOUKUTU;
				break;

			}



		}


	case MACHI:

		//í¨Ç…ëJà⁄
		while (scenes != STOP)
		{
			if (g_map == nullptr)
			{
				g_map = NewGO<Map>(0);
				g_player = NewGO<Player>(0);
			}

			else
			{
				g_fade->StartFadeIn();
				scenes = STOP;
				mapscene = MACHI;
				break;

			}



		}
	}

}
/*!
*@brief	ï`âÊä÷êîÅB
*/
void GameScene::Render(CRenderContext& renderContext)
{

}

void GameScene::DeteScene()
{


	if(mapscene == MACHI)
	{
		DeleteGO(g_map);
		DeleteGO(g_player);
		scenes = DOUKUTU;
		g_map = nullptr;



	}

	else if (mapscene == DOUKUTU)
	{
		DeleteGO(g_map2);
		DeleteGO(g_player);
		scenes = MACHI;
		g_map2 = nullptr;
	}

	

	g_player = nullptr;

}


