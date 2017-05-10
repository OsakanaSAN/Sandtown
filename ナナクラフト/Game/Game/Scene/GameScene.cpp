#include "stdafx.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "BattleScene.h"
#include "Fade.h"
#include "Player.h"
#include "Camera.h"
#include "Map.h"
#include "Map2.h"
#include "HUD.h"
#include "GameSound.h"



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
HUD*    g_Hud = nullptr;
extern GameSound* g_sound;

GameScene::GameScene()
{

	g_Hud = NewGO<HUD>(0);
	g_gameCamera = NewGO<Camera>(0);
	g_player = NewGO<Player>(0);
	g_map = NewGO<Map>(0);
	

	
	
	
	mapscene = MACHI;
	scenes = STOP;

	

	
}
GameScene::~GameScene()
{
	
	
}

bool GameScene::Start()
{
	

	
		return true;

}

void GameScene::Update()
{
	switch (scenes)
	{
	case STOP:
		//É^ÉCÉgÉãâÊñ Ç…ëJà⁄Ç∑ÇÈÅB

		if (GetAsyncKeyState('R') & 0x8000 && mapscene == DOUKUTU)
		{
				
				DeleteGO(g_player);
				g_player = nullptr;
				
				g_battleScene = NewGO<BattleScene>(0);
				g_gameCamera->BattleCamera();
				g_gameCamera->ChangeStop();    //ÉJÉÅÉâÇÃçXêVÇé~ÇﬂÇÈ
				scenes = Battle;
		}

		switch (sets)
		{
		case in:
			if (Pad(0).IsTrigger(enButtonStart)) {
				g_fade->StartFadeOut();
				sets = out;
				g_sound->StopSound();
				
				
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
				g_player = NewGO<Player>(0);
				g_map2 = NewGO<Map2>(0);
				
			}

			else
			{
				
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
				g_player = NewGO<Player>(0);
				g_map = NewGO<Map>(0);
				
			}

			else
			{
				scenes = STOP;
				mapscene = MACHI;
				break;

			}



		}

	case Battle:


		break;



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


