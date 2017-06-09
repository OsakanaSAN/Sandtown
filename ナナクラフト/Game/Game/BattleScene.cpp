#include "stdafx.h"
#include "BattleScene.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "BattlePlayer.h"
#include "Player.h"
#include "Camera.h"
#include "HUD.h"
#include "Fade.h"
#include "BattleEnemy.h"
#include "GameSound.h"
#include "Menu.h"
#include "BattleMenu.h"

BattlePlayer* g_battleplayer = nullptr;
BattleEnemy* g_battleenemy = nullptr;
BattleMenu* g_battlemenu;

BattleScene::BattleScene()
{

	g_battleplayer = NewGO<BattlePlayer>(0);
	g_battleenemy = NewGO<BattleEnemy>(0);
	g_battlemenu = NewGO<BattleMenu>(0);

	
	
}


BattleScene::~BattleScene()
{
	
	if (Victory == true) {
		g_sound->StopSound();
		DeleteGO(g_battlemenu);
		DeleteGO(g_battleplayer);
		DeleteGO(g_battleenemy);
		g_player = NewGO<Player>(0);
		g_player->Loadpos();           //座標を読み込む
		g_gameScene->SceneStop();
		g_gameCamera->ChangeStart();   //カメラの更新を再開するを
		g_sound->DoukutuSound();
		g_menu->GoldChangTex();
		g_menu->HpChangTex();
		g_menu->LvChangTex();
		
	}

	else
	{
		g_Hud->SetMaxHP(500.0f);
		DeleteGO(g_battleenemy);
		g_gameScene->SceneStop();
		g_gameCamera->ChangeStart();   //カメラの更新を再開するを
		g_gameScene->MapChange();
	}


	m_CasolBGTexture.Release();
	m_ComandBGTexture1.Release();
	m_ComandBGTexture2.Release();
	m_ComandBGTexture3.Release();
	m_ComandBGTexture4.Release();

}


bool BattleScene::Start()
{
	BattlGold = g_battleenemy->GetEGold();

	Winflg = false;
	Loseflg = false;
	PAttack = false;
	EAttack = false;
	PDamage = false;
	EDamage = false;
	SelectQ = false;


	m_ComandBGTexture1.Load("Assets/sprite/comand.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ -300,-350 });
	m_ComandBGSprite1.SetSize({ 200.0f,300.0f });

	m_ComandBGTexture2.Load("Assets/sprite/kougeki.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -300,-250 });
	m_ComandBGSprite2.SetSize({ 150.0f,50 });

	m_ComandBGTexture3.Load("Assets/sprite/nigeru.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -300,-450 });
	m_ComandBGSprite3.SetSize({ 150.0f,50 });

	m_ComandBGTexture4.Load("Assets/sprite/Item.png");
	m_ComandBGSprite4.Init(&m_ComandBGTexture4);
	m_ComandBGSprite4.SetPosition({ -300,-350 });
	m_ComandBGSprite4.SetSize({ 150.0f,50 });

	for (int i = 1; i < 4;i++) {

			m_DamageSeatTexture[i].Load("Assets/sprite/damagi0.png");
			m_DamageSeatSprite[i].SetPosition(m_Damageseatpos);
			m_DamageSeatSprite[i].Init(&m_DamageSeatTexture[i]);
			m_DamageSeatSprite[i].SetSize({ 50.0f,50.0f });
			m_Damageseatpos.x += 50;
	}
	m_CasolBGTexture.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite.Init(&m_CasolBGTexture);
	m_CasolBGSprite.SetPosition({ -500,-250 });
	m_CasolBGSprite.SetSize({ 200,200 });

	

	g_sound->BattleSound();

	CVector3 lightPos, lightTarget;
	lightTarget.Add(g_battleplayer->Getpos(), g_battleenemy->Getpos());
	lightTarget.Scale(0.5f);
	lightPos = g_battleplayer->Getpos();
	lightPos.y += 5.0f;
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(lightTarget);

	CEngine::Instance().GetFeedbackblur().SetEnalbe(false);
	CEngine::Instance().SetcrearEnable(true);

	g_battlemenu->SetHp(g_Hud->GetHP());
	g_battlemenu->SetEnemyHp(g_battleenemy->GetHP());
	g_battlemenu->SetEnemyMexHp(g_battleenemy->GetHP());

	m_random.Init((unsigned long)time(NULL));
	return true;
}


void BattleScene::Update()
{
	
	//CVector3 Pintpos = g_battleplayer->Getpos();
	///*CVector3 Epos = g_battleenemy->Getpos();
	//CVector3 Ppos = g_battleplayer->Getpos();

	//Pintpos.Add(Ppos, Epos);
	//Pintpos.Scale(0.5f);*/

	//CVector3 Cpos = g_gameCamera->BGetPos();

	//Pintpos.Subtract(Cpos);
	//
	//Dof().SetPint(Pintpos.Length()*1000);
	//Dof().SetFocalLength(40.0f);

	

	if (!IsBattleStart) { return; }


	if (Victory == true) {
		switch (result) {
			
		case false:

			g_gameCamera->PlayerBatlleCamera();
			
			IsBattle = false;
			EnemyPointCamera = true;

			if (Pad(0).IsTrigger(enButtonUp) && Comand == Item)
			{
				g_battlemenu->EnemyZoomOut();
				g_battlemenu->PlayerZoomSet();
				EnemyZoom = false;

				
				if (Comand != Keep)
				{
					m_sound_bgm_battle = NewGO<CSoundSource>(0);
					m_sound_bgm_battle->Init("Assets/sound/select.wav");
					m_sound_bgm_battle->Play(false);
					m_sound_bgm_battle->SetVolume(7.0f);
					
				}


				m_CasolBGSprite.SetPosition({ -500,-250 });
				m_CasolBGSprite.SetSize({ 200,200 });

				Comand = Keep;

			}
			else if (Pad(0).IsPress(enButtonDown) && Pad(0).IsPress(enButtonUp))
			{

			}
			else if (Pad(0).IsTrigger(enButtonDown) && Comand ==Keep|| Pad(0).IsTrigger(enButtonUp) && Comand == Escape)
			{
				
					m_sound_bgm_battle = NewGO<CSoundSource>(0);
					m_sound_bgm_battle->Init("Assets/sound/select.wav");
					m_sound_bgm_battle->Play(false);
					m_sound_bgm_battle->SetVolume(7.0f);
				

				m_CasolBGSprite.SetPosition({ -500,-350 });
				m_CasolBGSprite.SetSize({ 200,200 });

				Comand = Item;
			}
			else if (Pad(0).IsTrigger(enButtonDown) && Comand == Item)
			{
				
					m_sound_bgm_battle = NewGO<CSoundSource>(0);
					m_sound_bgm_battle->Init("Assets/sound/select.wav");
					m_sound_bgm_battle->Play(false);
					m_sound_bgm_battle->SetVolume(7.0f);


				m_CasolBGSprite.SetPosition({ -500,-450 });
				m_CasolBGSprite.SetSize({ 200,200 });

				Comand = Escape;
			}

			if (turnCheng)
			{
				PlayerTurn();
			}

			break;

		case true:

			if (turnCheng == true)
			{
				PlayerTurn();
				if (Itemuse)//アイテム使ったターン
				{
					g_battleplayer->ParticleDelete();//パーティクル消去
					Itemuse = false;
				}
				
			}
			else if (turnCheng == false) {
				EnemyTurn();
			}

			break;

		}
	}
	else if(Victory == false)
	{

		if (Pad(0).IsPress(enButtonRB1))
		{
			DeleteGO(g_battleScene);
		}

	}


}

void BattleScene::PostRender(CRenderContext&renderContext)
{
	
	if (EDamage || PDamage) {//ダメージの表示
		for (int i = 0;i < 4;i++)
		{

			//m_DamageSeatSprite[i].Draw(renderContext);
		}
	}

	if (EnemyZoom) { return; }
	if (IsBattle) { return; }
	if (!IsBattleStart) { return; }
	if (Comand == INVENTORY) { return; }

	m_ComandBGSprite1.Draw(renderContext);
	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);
	m_ComandBGSprite4.Draw(renderContext);
	m_CasolBGSprite.Draw(renderContext);

}


void BattleScene::PlayerTurn()
{

	if (EAttack)return;
	if (PDamage)return;

	switch (Comand)//選択肢
	{
		
	case Keep:

		BattleKeep();
		break;

	case Attack://攻撃

		if (!IsBattle)
		{
			g_gameCamera->EnemyBattleCamera();
			
		}

		if (Pad(0).IsTrigger(enButtonA) && g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			g_battlemenu->EnemyZoomOut();
			g_battlemenu->PlayerZoomSet();

			EnemyZoom = false;
			IsBattle = true; //コマンド不可視化
			g_gameCamera->BattleCamera();

			if (!SelectQ)
			{
				m_sound_bgm_battle = NewGO<CSoundSource>(0);
				m_sound_bgm_battle->Init("Assets/sound/select3.wav");
				m_sound_bgm_battle->Play(false);
				m_sound_bgm_battle->SetVolume(4.0f);

			}

			result = true;
			g_battleplayer->SetAttack(true);//攻撃モーション
			SelectQ = true;
			PAttack = true;
			
			

		}
		else if (PAttack && !EDamage&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			m_sound_Attack = NewGO<CSoundSource>(0);
			m_sound_Attack->Init("Assets/sound/Attack.wav");
			m_sound_Attack->Play(false);
			m_sound_Attack->SetVolume(4.0f);

			/*for (int i = 1; i < 4;i++) {


				m_DamageSeatTexture[i].Load("Assets/sprite/damage0.png");
				m_DamageSeatSprite[i].Init(&m_DamageSeatTexture[i]);
				m_DamageSeatSprite[i].SetPosition({ -240,250 });
				m_DamageSeatSprite[i].SetSize({ 200,80 });
			}*/
			//DamageTex();
		

			g_battleplayer->Particle(g_battleenemy->Getpos(),0);//攻撃パーティクル呼び出し
			g_battleenemy->SetDamage(g_battleplayer->GetATK(), true);//ダメージ処理
			g_battlemenu->SetEnemyHp(g_battleenemy->GetHP());//敵の体力DOWN
			EDamage = true;
		
		}
		else if (PAttack &&EDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			g_battleplayer->ParticleDelete();//パーティクル消去
			m_sound_Attack->Stop();
			PAttack = false;
			EDamage = false;
			if (g_battleenemy->GetHP() <= 0)
			{

				g_Hud->SetGold(g_battleenemy->GetEGold());
				g_Hud->SetExp(g_battleenemy->GetExp());
				Winflg = true;//バトルに勝利した

				/*g_gameScene->BattleDate();*/
				DeleteGO(this);

				g_menu->InventoryChangTex(3);

				return;

				/*g_battleenemy->Delete();*/
				//レベルアップ判定
				//リザルト画面を出す処理その後シーン遷移？
			}
			//Turn = Eturn;//敵のターン
			turnCheng = false;
			Comand = Keep;

		}

		break;

	case Escape://逃げる

		//if (SelectQ)return;
		if (Pad(0).IsPress(enButtonA))
		{
			
			//確率で逃げれるようにする？乱数とかで？
			DeleteGO(this);
			//Result();
			return;
		}

		break;

	case Item:
		
		if (Pad(0).IsTrigger(enButtonA))
		{

			Comand = INVENTORY;
	
		}
		break;
	case INVENTORY:


		g_menu->MenuSceneItem();
		if (Pad(0).IsTrigger(enButtonA))//アイテムの使用
		{
			Itemuse = g_menu->UseItem();
			g_menu->MenuSceneexit();
			Comand = Item;
			
		}
		if (Pad(0).IsPress(enButtonB))
		{

			g_menu->MenuSceneexit();
			Comand = Item;
		}
		break;
	}

}

void BattleScene::EnemyTurn()
{

	if (PAttack)return;
	if (EDamage)return;

	if (!EAttack&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend()) {

		g_battleenemy->SetAttack(true);//攻撃のアニメーション再生

		EAttack = true;
	}
	else if (EAttack && !PDamage && g_battleplayer->GetAnimend() && g_battleenemy->GetAnimend())
	{
		//m_sound_Attack = NewGO<CSoundSource>(0);
		//m_sound_Attack->Init("Assets/sound/Attack.wav");
		m_sound_Attack->Play(false);
		m_sound_Attack->SetVolume(4.0f);
		//for (int i = 1; i < 4;i++) {


		//	m_DamageSeatTexture[i].Load("Assets/sprite/damage0.png");
		//	m_DamageSeatSprite[i].Init(&m_DamageBGTexture[i]);
		//	m_DamageSeatSprite[i].SetPosition({ 150,100 });
		//	m_DamageSeatSprite[i].SetSize({ 200,80 });
		//}
		//DamageTex();

		g_battleplayer->Particle(g_battleplayer->Getpos(),0);//攻撃パーティクル呼び出し
		
		g_battleplayer->SetDamage(g_battleenemy->GetATK(), true);//ダメージ計算とダメージアニメーション再生
		
		g_battlemenu->SetHp(g_Hud->GetHP());

		PDamage = true;

		
	}
	else if (EAttack &&PDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
	{
		g_battleplayer->ParticleDelete();//パーティクル消去
		m_sound_Attack->Stop();
		EAttack = false;
		PDamage = false;

		if (g_Hud->GetHP() <= 0)
		{

			Loseflg = true;//戦闘に負けた

			/*g_gameScene->BattleDate();*/

			Victory = false;
			DeleteGO(g_battleScene);

			//リザルト画面を出す処理かシーン遷移？
		}
		SelectQ = false;
		result = false;
		//Turn = Pturn;//プレイヤーのターン
		turnCheng = true;

	}
}



void BattleScene::BattleKeep()
{
	if (Pad(0).IsPress(enButtonA))
	{

		g_battlemenu->EnemyZoomSet();
		g_battlemenu->PlayerZoomOut();
		m_sound_bgm_battle = NewGO<CSoundSource>(0);
		m_sound_bgm_battle->Init("Assets/sound/select3.wav");
		m_sound_bgm_battle->Play(false);
		m_sound_bgm_battle->SetVolume(4.0f);
		EnemyZoom = true;

		Comand = Attack;

	}

}

void BattleScene::DamageTex()
{
	int NextDamage[3];
	int Damage=g_battleenemy->GetATK();


	NextDamage[0] = Damage / 100;
	sprintf(m_DamageTexName, "Assets/sprite/damagi%d.png", NextDamage[0]);
	m_DamageSeatTexture[1].Release();
	m_DamageSeatTexture[1].Load(m_DamageTexName);

	Damage %= 100;

	NextDamage[1] = Damage / 10;
	sprintf(m_DamageTexName, "Assets/sprite/damagi%d.png", NextDamage[1]);
	m_DamageSeatTexture[2].Release();
	m_DamageSeatTexture[2].Load(m_DamageTexName);

	Damage %= 10;
	NextDamage[2] = Damage;
	sprintf(m_DamageTexName, "Assets/sprite/damagi%d.png", NextDamage[2]);
	m_DamageSeatTexture[3].Release();
	m_DamageSeatTexture[3].Load(m_DamageTexName);

	
}