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
#include "tkEngine/graphics/tkCamera.h"
#include "Dungeon.h"


GameScene* g_gameScene = NULL;
Player* g_player = nullptr;
Camera* g_gameCamera = nullptr;
Map*    g_map = nullptr;
Map2*   g_map2 = nullptr;
BattleScene* g_battleScene = nullptr;
HUD*    g_Hud = nullptr;
Menu*   g_menu = nullptr;
Enemy*  g_Enemy = nullptr;
Enemy*  g_Enemy2 = nullptr;
Enemy*  g_Enemy3 = nullptr;
Dungeon* g_Dungeon = nullptr;

GameScene::GameScene()
{
	g_gameCamera = NewGO<Camera>(0);
	g_player = NewGO<Player>(0);
	g_Hud = NewGO<HUD>(0);
	//g_map = NewGO<Map>(0);
	g_Dungeon = NewGO<Dungeon>(0);

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
	
	
	//if (g_gameCamera->IsStart() && g_player->IsStart() && g_Hud->IsStart() && g_map->IsStart()) {

		g_fade->StartFadeIn();
		return true;

	//}
	
	
	
}

void GameScene::Update()
{
	

	switch (scenes)
	{
	case BattleWait:
		
		g_player->IsMoveSTOP();
		m_timer += GameTime().GetFrameDeltaTime();
		
		if (m_timer > 3.0f)
		{
			
			scenes = Battle;
			m_timer = 0.0f;
		}
		break;

	case STOP:


		if (Bato == true)
		{
			

			CEngine::Instance().SetcrearEnable(false);
			CEngine::Instance().GetFeedbackblur().SetEnalbe(true);

			scenes = BattleWait;
			

		}
		
		else if (Pad(0).IsPress(enButtonY))
		{
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
				g_gameCamera->ChangeStart();

				g_player = NewGO<Player>(0);
				modelName = "Assets/modelData/ghost.X";
				g_Enemy = NewGO<Enemy>(0);
				g_Enemy->Init(modelName);
				g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
				g_Enemy->Setexp(20);
				g_Enemy->SetEATK(20);
				g_Enemy->SetHP(50);
				g_Enemy->SetGold(20);

				modelName = "Assets/modelData/ghost.X";
				g_Enemy2 = NewGO<Enemy>(0);
				g_Enemy2->Init(modelName);
				g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
				g_Enemy2->Setexp(20);
				g_Enemy2->SetEATK(60);
				g_Enemy2->SetHP(40);
				g_Enemy2->SetGold(20);


				modelName = "Assets/modelData/Bossghost.X";
				g_Enemy3 = NewGO<Enemy>(0);
				g_Enemy3->Init(modelName);
				g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
				g_fade->StartFadeIn();
				g_Enemy3->Setexp(20);
				g_Enemy3->SetEATK(80);
				g_Enemy3->SetHP(90);
				g_Enemy3->SetGold(20);
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
		break;

	case MACHI:

		//’¬‚É‘JˆÚ
		while (scenes != STOP)
		{
			if (g_map == nullptr)
			{
				g_gameCamera->ChangeStart();
				if (g_fade->IsExecute() == true) { return; }
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
		break;
	case Battle:
		if (Bato == true)
		{
			
			DeleteGO(g_player);
			g_player = nullptr;
			//g_Enemy = nullptr;
			g_sound->StopSound();
			g_battleScene = NewGO<BattleScene>(0);
			g_gameCamera->BattleCamera();
			g_gameCamera->ChangeStop();	//ƒJƒƒ‰‚ÌXV‚ðŽ~‚ß‚é
			
			
			Bato = false;
		}
		break;


	case MENU:


		break;

	case Change:


		DeteScene();
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

	if (g_fade->IsExecute() == true)
	{
		g_player->IsMoveSTOP();
		g_player->StopSound();
		g_gameCamera->ChangeStop();
		return; }

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
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
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
	g_fade->StartFadeOut();
	g_sound->StopSound();
	scenes = Change;
	
	

}


