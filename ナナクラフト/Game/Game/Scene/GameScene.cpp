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
#include "Menu.h"
#include "Enemy.h"
#include "Npc.h"



#define   Y_UP 150
#define   X_POS -650
#define   X2_POS -950

GameScene* g_gameScene = NULL;
Player* g_player = nullptr;
Camera* g_gameCamera = nullptr;
Map*    g_map = nullptr;
Map2*   g_map2 = nullptr;
BattleScene* g_battleScene = nullptr;
HUD*    g_Hud = nullptr;
Menu*   g_menu = nullptr;
Enemy*  g_Enemy = nullptr;



GameScene::GameScene()
{
	g_gameCamera = NewGO<Camera>(0);
	g_player = NewGO<Player>(0);
	g_Hud = NewGO<HUD>(0);
	g_map = NewGO<Map>(0);
	g_menu = NewGO<Menu>(0);
	NewGO<Npc>(0);
	mapscene = MACHI;
	scenes = STOP;
	
}



GameScene::~GameScene()
{
	
	
}

bool GameScene::Start()
{
	
	
	if (g_gameCamera->IsStart() && g_player->IsStart() && g_Hud->IsStart() && g_map->IsStart()) {
		g_fade->StartFadeIn();
		return true;

	}
	
	/*ShadowMap().SetLightPosition(g_gameCamera->GetPos());
	
	ShadowMap().SetLightTarget(g_player->Getpos());*/
	
}

void GameScene::Update()
{
	

	//ƒ^ƒCƒgƒ‹‰æ–Ê‚É‘JˆÚ‚·‚éB



	switch (scenes)
	{

	case STOP:

		

		if (Pad(0).IsPress(enButtonX) && mapscene == DOUKUTU)
		{
				
				DeleteGO(g_player);
				DeleteGO(g_Enemy);
				g_player = nullptr;
				g_Enemy = nullptr;
				g_sound->StopSound();
				g_battleScene = NewGO<BattleScene>(0);
				g_gameCamera->BattleCamera();
				g_gameCamera->ChangeStop();    //ƒJƒƒ‰‚ÌXV‚ðŽ~‚ß‚é
				scenes = Battle;

		}

		else if (Pad(0).IsPress(enButtonY))
		{
			//g_menu->InventoryChangTex();
			g_menu->MenuScene();
			g_menu->setHP(g_Hud->GetHP());
			g_menu->setLV(g_Hud->GetLV());
			g_menu->SetGold(g_Hud->GetGold());
			g_sound->VolumeDown();
			g_player->StopSound();
			scenes = MENU;
			g_gameCamera->ChangeStop();
			g_player->IsMoveSTOP();

		}

		else if (Pad(0).IsPress(enButtonStart)&&Pad(0).IsPress(enButtonSelect))
		{
			exit(0);
		}



		break;


		//“´ŒA‚É‘JˆÚ
	case DOUKUTU:

		while (scenes != STOP)
		{

			if (g_map2 == nullptr)
			{
				g_player = NewGO<Player>(0);
				g_Enemy = NewGO<Enemy>(0);
				g_map2 = NewGO<Map2>(0);
				
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

		//’¬‚É‘JˆÚ
		while (scenes != STOP)
		{
			if (g_map == nullptr)
			{
				g_player = NewGO<Player>(0);
				g_map = NewGO<Map>(0);
				
			}

			else
			{
				g_fade->StartFadeIn();
				scenes = STOP;
				mapscene = MACHI;
				break;
			}

		}

	case Battle:


		break;


	case MENU:


		break;
	}
	
}
/*!
*@brief	•`‰æŠÖ”B
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
			DeleteGO(g_Enemy);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;
			g_map2 = nullptr;
		
	}


	g_player = nullptr;

}
void GameScene::MapChange()
{
	while (Chang == true) {

		switch (sets)
		{
		case in:
			
				//g_fade->StartFadeOut();
				sets = out;
				g_sound->StopSound();

			break;

		case out:

				DeteScene();
				sets = in;
				Chang = false;

			
			break;

		}
	}

	Chang = true;
}


