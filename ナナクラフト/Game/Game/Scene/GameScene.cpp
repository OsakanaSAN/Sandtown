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
Enemy*  g_Enemy2 = nullptr;
Enemy*  g_Enemy3 = nullptr;

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
	
	
	
}

void GameScene::Update()
{
	
	


	switch (scenes)
	{

	case STOP:
	

		

		if (/*Pad(0).IsPress(enButtonX) && mapscene == DOUKUTU*/ Bato == true)
		{
				
				DeleteGO(g_player);
				g_player = nullptr;
				//g_Enemy = nullptr;
				g_sound->StopSound();
				g_battleScene = NewGO<BattleScene>(0);
				g_gameCamera->BattleCamera();
				g_gameCamera->ChangeStop();    //�J�����̍X�V���~�߂�
				scenes = Battle;
				Bato = false;

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


		//���A�ɑJ��
	case DOUKUTU:

		while (scenes != STOP)
		{

			if (g_map2 == nullptr)
			{
				g_player = NewGO<Player>(0);
				modelName = "Assets/modelData/usagi.X";
				g_Enemy = NewGO<Enemy>(0);
				g_Enemy->Init(modelName);
				g_Enemy->setPos({ -3.0f, 0.0f, -20.0f });


				modelName = "Assets/modelData/ghost.X";
				g_Enemy2 = NewGO<Enemy>(0);
				g_Enemy2->Init(modelName);
				g_Enemy2->setPos({ -3.0f, 0.0f, -40.0f });

				modelName = "Assets/modelData/cabetu.X";
				g_Enemy3 = NewGO<Enemy>(0);
				g_Enemy3->Init(modelName);
				g_Enemy3->setPos({ 0.0f, 0.0f, -15.0f });
				g_map2 = NewGO<Map2>(0);
				g_fade->StartFadeIn();
				
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

		//���ɑJ��
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
*@brief	�`��֐��B
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


