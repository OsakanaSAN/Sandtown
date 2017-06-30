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
#include "BattlePlayer.h"
#include "SceneChange.h"
#include "particle.h"
#include "SaveData.h"

GameScene* g_gameScene = NULL;
Player* g_player = nullptr;
Camera* g_gameCamera = nullptr;
Map*    g_map = nullptr;
BattleScene* g_battleScene = nullptr;
HUD*    g_Hud = nullptr;
Menu*   g_menu = nullptr;
Enemy*  g_Enemy = nullptr;
Enemy*  g_Enemy2 = nullptr;
Enemy*  g_Enemy3 = nullptr;
Dungeon* g_Dungeon = nullptr;
particle* g_particle = nullptr;


GameScene::GameScene()
{
	g_gameCamera = NewGO<Camera>(0);
	g_player = NewGO<Player>(0);
	g_Hud = NewGO<HUD>(0);
	g_map = NewGO<Map>(0);
	g_menu = NewGO<Menu>(0);
	NewGO<SaveData>(0);


	mapscene = MACHI;
	scenes = STOP;
}


GameScene::~GameScene()
{
	
	
}

bool GameScene::Start()
{

	if (g_gameCamera->IsActive() && g_player->IsActive() && g_Hud->IsActive()&& g_map->IsActive()) {

		g_fade->StartFadeIn();
		return true;

	}
	return true;
}

void GameScene::Update()
{

	switch (scenes)
	{
	case BattleWait:
		
		g_player->IsMoveSTOP();
		
		m_timer += GameTime().GetFrameDeltaTime();
		
		if (m_timer > 2.0f)
		{
			//g_sound->StopSound();

			scenes = Battle;
			m_timer = 0.0f;
		}
		break;

	case STOP:


		if (Bato == true)
		{
			
			g_sound->StopSound();

			CEngine::Instance().SetcrearEnable(false);
			CEngine::Instance().GetFeedbackblur().SetEnalbe(true);
			g_sound->EnkauntoSound();
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

			if (Maptype == 0) {

				if (g_Dungeon == nullptr)
				{
					//g_map2 = NewGO<Map2>(0);
					g_Dungeon = NewGO<Dungeon>(0);
					g_player = NewGO<Player>(0);

					modelName = "Assets/modelData/ghost.X";
					g_Enemy = NewGO<Enemy>(0);
					g_Enemy->Init(modelName);
					g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
					g_Enemy->LevelSet(1);

					modelName = "Assets/modelData/ghost.X";
					g_Enemy2 = NewGO<Enemy>(0);
					g_Enemy2->Init(modelName);
					g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
					g_Enemy2->LevelSet(1);

					modelName = "Assets/modelData/Bossghost.X";
					g_Enemy3 = NewGO<Enemy>(0);
					g_Enemy3->Init(modelName);
					g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
					g_Enemy3->LevelSet(2);

					g_gameCamera->ChangeStart();

				}

				else
				{
					if (g_Dungeon->IsActive() && g_Enemy->IsActive() && g_Enemy2->IsActive() && g_Enemy3->IsActive() && g_player->IsActive()) {

						g_fade->StartFadeIn();
						scenes = STOP;
						mapscene = DOUKUTU;
					}
					break;

				}
			}
			else if (Maptype == 1)
			{
				if (g_Dungeon == nullptr)
				{

					g_Dungeon = NewGO<Dungeon>(0);
					g_player = NewGO<Player>(0);

					modelName = "Assets/modelData/Bossghost.X";
					g_Enemy = NewGO<Enemy>(0);
					g_Enemy->Init(modelName);
					g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
					g_Enemy->LevelSet(2);

					modelName = "Assets/modelData/Bossghost.X";
					g_Enemy2 = NewGO<Enemy>(0);
					g_Enemy2->Init(modelName);
					g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
					g_Enemy2->LevelSet(2);

					modelName = "Assets/modelData/Bossghost.X";
					g_Enemy3 = NewGO<Enemy>(0);
					g_Enemy3->Init(modelName);
					g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
					g_Enemy3->LevelSet(2);

					g_gameCamera->ChangeStart();
				}
				else
				{
					if (g_Dungeon->IsActive() && g_Enemy->IsActive() && g_Enemy2->IsActive() && g_Enemy3->IsActive() && g_player->IsActive())
					{
						g_fade->StartFadeIn();
						scenes = STOP;
						mapscene = DOUKUTU;

					}
					break;
				}
			}
			else if (Maptype == 2)
			{
				if (g_Dungeon == nullptr)
				{

					g_Dungeon = NewGO<Dungeon>(0);
					g_player = NewGO<Player>(0);

					modelName = "Assets/modelData/Bossghost.X";
					g_Enemy = NewGO<Enemy>(0);
					g_Enemy->Init(modelName);
					g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
					g_Enemy->LevelSet(3);

					modelName = "Assets/modelData/Bossghost.X";
					g_Enemy2 = NewGO<Enemy>(0);
					g_Enemy2->Init(modelName);
					g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
					g_Enemy2->LevelSet(3);

					modelName = "Assets/modelData/Bossghost.X";
					g_Enemy3 = NewGO<Enemy>(0);
					g_Enemy3->Init(modelName);
					g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
					g_Enemy3->LevelSet(3);

					g_gameCamera->ChangeStart();
				}
				else
				{
					if (g_Dungeon->IsActive() && g_Enemy->IsActive() && g_Enemy2->IsActive() && g_Enemy3->IsActive() && g_player->IsActive())
					{
						g_fade->StartFadeIn();
						scenes = STOP;
						mapscene = DOUKUTU;
					}
					break;
				}
			}

			else if (Maptype == 3)
			{
				if (g_Dungeon == nullptr)
				{

					g_Dungeon = NewGO<Dungeon>(0);
					g_player = NewGO<Player>(0);

					modelName = "Assets/modelData/cabetu.X";
					g_Enemy = NewGO<Enemy>(0);
					g_Enemy->Init(modelName);
					g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
					g_Enemy->LevelSet(3);

					modelName = "Assets/modelData/cabetu.X";
					g_Enemy2 = NewGO<Enemy>(0);
					g_Enemy2->Init(modelName);
					g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
					g_Enemy2->LevelSet(3);

					modelName = "Assets/modelData/cabetu.X";
					g_Enemy3 = NewGO<Enemy>(0);
					g_Enemy3->Init(modelName);
					g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
					g_Enemy3->LevelSet(3);

					g_gameCamera->ChangeStart();
				}
				else
				{
					if (g_Dungeon->IsActive() && g_Enemy->IsActive() && g_Enemy2->IsActive() && g_Enemy3->IsActive() && g_player->IsActive())
					{
						g_fade->StartFadeIn();
						scenes = STOP;
						mapscene = DOUKUTU;
					}
					break;
				}
			}
			else if (Maptype == 4)
			{
				if (g_Dungeon == nullptr)
				{

					g_Dungeon = NewGO<Dungeon>(0);
					g_player = NewGO<Player>(0);

					modelName = "Assets/modelData/EnemyKnight.X";
					g_Enemy = NewGO<Enemy>(0);
					g_Enemy->Init(modelName);
					g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
					g_Enemy->LevelSet(4);

					modelName = "Assets/modelData/EnemyKnight.X";
					g_Enemy2 = NewGO<Enemy>(0);
					g_Enemy2->Init(modelName);
					g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
					g_Enemy2->LevelSet(4);

					modelName = "Assets/modelData/EnemyKnight.X";
					g_Enemy3 = NewGO<Enemy>(0);
					g_Enemy3->Init(modelName);
					g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
					g_Enemy3->LevelSet(4);

					g_gameCamera->ChangeStart();
				}
				else
				{
					if (g_Dungeon->IsActive() && g_Enemy->IsActive() && g_Enemy2->IsActive() && g_Enemy3->IsActive() && g_player->IsActive())
					{
						g_fade->StartFadeIn();
						scenes = STOP;
						mapscene = DOUKUTU;
					}
					break;
				}
			}
			else if (Maptype == 5)
			{
				if (g_Dungeon == nullptr)
				{

					g_Dungeon = NewGO<Dungeon>(0);
					g_player = NewGO<Player>(0);

					modelName = "Assets/modelData/usagi.X";
					g_Enemy = NewGO<Enemy>(0);
					g_Enemy->Init(modelName);
					g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
					g_Enemy->LevelSet(3);

					modelName = "Assets/modelData/usagi.X";
					g_Enemy2 = NewGO<Enemy>(0);
					g_Enemy2->Init(modelName);
					g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
					g_Enemy2->LevelSet(3);

					modelName = "Assets/modelData/Bossusagi.X";
					g_Enemy3 = NewGO<Enemy>(0);
					g_Enemy3->Init(modelName);
					g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
					g_Enemy3->LevelSet(4);

					g_gameCamera->ChangeStart();
				}
				else
				{
					if (g_Dungeon->IsActive() && g_Enemy->IsActive() && g_Enemy2->IsActive() && g_Enemy3->IsActive() && g_player->IsActive())
					{
						g_fade->StartFadeIn();
						scenes = STOP;
						mapscene = DOUKUTU;
					}
					break;
				}
			}
			else if (Maptype == 6)
			{
				if (g_Dungeon == nullptr)
				{

					g_Dungeon = NewGO<Dungeon>(0);
					g_player = NewGO<Player>(0);

					modelName = "Assets/modelData/Bossusagi.X";
					g_Enemy = NewGO<Enemy>(0);
					g_Enemy->Init(modelName);
					g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });
					g_Enemy->LevelSet(4);

					modelName = "Assets/modelData/Bossusagi.X";
					g_Enemy2 = NewGO<Enemy>(0);
					g_Enemy2->Init(modelName);
					g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });
					g_Enemy2->LevelSet(4);

					modelName = "Assets/modelData/Bossusagi.X";
					g_Enemy3 = NewGO<Enemy>(0);
					g_Enemy3->Init(modelName);
					g_Enemy3->setPos({ 20.0f, 0.0f, -15.0f });
					g_Enemy3->LevelSet(4);

					g_gameCamera->ChangeStart();
				}
				else
				{
					if (g_Dungeon->IsActive() && g_Enemy->IsActive() && g_Enemy2->IsActive() && g_Enemy3->IsActive() && g_player->IsActive())
					{
						g_fade->StartFadeIn();
						scenes = STOP;
						mapscene = DOUKUTU;
					}
					break;
				}
			}
		}
		
		
		break;

	case MACHI:

		//’¬‚É‘JˆÚ
		while (scenes != STOP)
		{
			if (g_map == nullptr)
			{
			
				if (g_fade->IsExecute() == true){ return; }
				g_player = NewGO<Player>(0);
				g_map = NewGO<Map>(0);
				g_gameCamera->ChangeStart();
				
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

		if(Bato == true)
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
		if (g_player != nullptr) {
			g_player->IsMoveSTOP();
			g_gameCamera->ChangeStop();
		}
		
		//g_player->StopSound();
		
		return; 
	}

	if(mapscene == MACHI)
	{

		DeleteGO(g_map);
		DeleteGO(g_player);
		scenes = DOUKUTU;
		g_map = nullptr;

	}

	else if (mapscene == DOUKUTU)
	{
		if (Maptype == 0)
		{
			DeleteGO(g_Dungeon);
			DeleteGO(g_Enemy);
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;

			g_Dungeon = nullptr;
		}
		else if (Maptype == 1)
		{
			DeleteGO(g_Dungeon);
			DeleteGO(g_Enemy);
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;

			g_Dungeon = nullptr;
		}
		else if (Maptype == 2)
		{
			DeleteGO(g_Dungeon);
			DeleteGO(g_Enemy);
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;

			g_Dungeon = nullptr;
		}
		else if (Maptype == 3)
		{
			DeleteGO(g_Dungeon);
			DeleteGO(g_Enemy);
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;

			g_Dungeon = nullptr;
		}
		else if (Maptype == 4)
		{
			DeleteGO(g_Dungeon);
			DeleteGO(g_Enemy);
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;

			g_Dungeon = nullptr;
		}
		else if (Maptype == 5)
		{
			DeleteGO(g_Dungeon);
			DeleteGO(g_Enemy);
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;

			g_Dungeon = nullptr;
		}
		else if (Maptype == 6)
		{
			DeleteGO(g_Dungeon);
			DeleteGO(g_Enemy);
			DeleteGO(g_Enemy2);
			DeleteGO(g_Enemy3);
			if (g_player != nullptr) {
				DeleteGO(g_player);
			}
			scenes = MACHI;

			g_Dungeon = nullptr;
		}
	}


	g_player = nullptr;

}
void GameScene::MapChange()
{
	g_fade->StartFadeOut();
	g_sound->StopSound();
	scenes = Change;
	
}
