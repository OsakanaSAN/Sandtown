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

	
	for (int i = 0; i < 3;i++) {

		m_DamageSeatTexture[i].Load("Assets/sprite/damagi0.png");
		m_DamageSeatSprite[i].SetPosition(m_Damageseatpos);
		m_DamageSeatSprite[i].Init(&m_DamageSeatTexture[i]);
		m_DamageSeatSprite[i].SetSize({ 100.0f,80.0f });
		m_Damageseatpos.x += 50;
	}
}


BattleScene::~BattleScene()
{
	
		if (Victory == true) {

			g_sound->StopSound();
			DeleteGO(g_battlemenu);
			DeleteGO(g_battleplayer);
			if (g_battlemenu != nullptr)
			{
				DeleteGO(g_battleenemy);
			}
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
	GetEXP[0] = g_Hud->GetLV();

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

	
	m_CasolBGTexture.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite.Init(&m_CasolBGTexture);
	m_CasolBGSprite.SetPosition({ -500,-250 });
	m_CasolBGSprite.SetSize({ 200,200 });

	m_ResultBGTexture6.Load("Assets/sprite/Result.png");
	m_ResultBGSprite6.Init(&m_ResultBGTexture6);


	m_ResultBGTexture7.Load("Assets/sprite/lvup.png");
	m_ResultBGSprite7.Init(&m_ResultBGTexture7);


	


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

	m_sound_Attack = NewGO<CSoundSource>(0);
	m_sound_Attack->Init("Assets/sound/Attack.wav");

	DamageTex(true);
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

	//DamageTex(true);

	if (!IsBattleStart) { return; }


	if (Victory == true) {

		switch (result) {

		case false:

			g_gameCamera->PlayerBatlleCamera();

			IsBattle = false;
			EnemyPointCamera = true;

			//攻撃

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

			else if (Pad(0).IsTrigger(enButtonDown) && Pad(0).IsTrigger(enButtonUp))
			{

			}

			//矢印→アイテム

			else if (Pad(0).IsTrigger(enButtonDown) && Comand == Keep || Pad(0).IsTrigger(enButtonUp) && Comand == Escape)
			{

				m_sound_bgm_battle = NewGO<CSoundSource>(0);
				m_sound_bgm_battle->Init("Assets/sound/select.wav");
				m_sound_bgm_battle->Play(false);
				m_sound_bgm_battle->SetVolume(7.0f);


				m_CasolBGSprite.SetPosition({ -500,-350 });
				m_CasolBGSprite.SetSize({ 200,200 });

				Comand = Item;
			}
			//逃げる

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


				if (turnCheng == false) {

					EnemyTurn();
					
				}

				break;

			}
		}
	}
	else if (Victory == false)
	{
		

		Defeat();
		/*if (Pad(0).IsPress(enButtonRB1))
		{
			DeleteGO(g_battleScene);
		}*/
	}
		

	
}

void BattleScene::PostRender(CRenderContext&renderContext)
{

	if (Comand == Result) {
		m_ComandBGSprite1.Draw(renderContext);
		if (GetEXP[0] < GetEXP[1]) {
			m_ResultBGSprite7.Draw(renderContext);
		}
		m_ResultBGSprite6.Draw(renderContext);
	
	}

	if (EDamage || PDamage) {//ダメージの表示
	
	
			if (NextDamage[0] != 0)
			{
				m_DamageSeatSprite[0].Draw(renderContext);
			}
			if (NextDamage[1] != 0|| NextDamage[0] != 0)
			{
				m_DamageSeatSprite[1].Draw(renderContext);
			}
			
			m_DamageSeatSprite[2].Draw(renderContext);
		
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



/////////////////////////////////////////////////////////////////////
//プレイヤーのターン
void BattleScene::PlayerTurn()
{
	
	if (EAttack)return;
	if (PDamage)return;


	DamageTex(false);
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

		else if (PAttack && !EDamage &&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{

			m_sound_Attack->Play(false);
			m_sound_Attack->SetVolume(4.0f);
			
			CVector2 PDamagepos = { -380,300 };
			for (int i = 0; i < 3;i++) {

				//m_DamageSeatTexture[i].Load("Assets/sprite/damage0.png");
				m_DamageSeatSprite[i].Init(&m_DamageSeatTexture[i]);
				m_DamageSeatSprite[i].SetPosition(PDamagepos);
				m_DamageSeatSprite[i].SetSize({100,80 });
				PDamagepos.x +=80;
			}
			

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


				Comand = Result;


				g_Hud->SetGold(g_battleenemy->GetEGold());
				g_Hud->SetExp(g_battleenemy->GetExp());
				Winflg = true;//バトルに勝利した
				DeleteGO(g_battleenemy);
				g_battleenemy = nullptr;
				g_menu->InventoryChangTex(3);
				BattleResult();
				return;


				/*g_battleenemy->Delete();*/
			}

			else
			{
				//Turn = Eturn;//敵のターン
				turnCheng = false;
				Comand = Keep;
			}

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
			int escape =  g_random.GetRandInt() % 10 + 1;
			if(escape %2==0)
			{
				result = true;
				turnCheng = false;
				g_gameCamera->BattleCamera();
				IsBattle = true; //コマンド不可視化
				return;

			}
			else
			{
				//確率で逃げれるようにする？乱数とかで？
				DeleteGO(this);
				//Result();
				return;
			}
		}

		break;
	case Result:

		if (Pad(0).IsTrigger(enButtonA))
		{

			Comand = Keep;
			DeleteGO(this);

		};

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
		if (Pad(0).IsPress(enButtonB))//インベントリをとじる
		{
		
			g_menu->MenuSceneexit();

			Comand = Item;
		}
		break;
	}
	

}


///////////////////////////////////////////////////////////////////////////////////////////
//敵のターン
void BattleScene::EnemyTurn()
{
	
	if (PAttack)return;
	if (EDamage)return;
	DamageTex(true);

	if (g_battleenemy->GetAnimend() == false)return;


	if (!EAttack&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend()) {
			g_battleenemy->SetAttack(true);//攻撃のアニメーション再生


		EAttack = true;
	}
	else if (EAttack && !PDamage && g_battleplayer->GetAnimend() && g_battleenemy->GetAnimend())
	{
		
		m_sound_Attack->Play(false);
		m_sound_Attack->SetVolume(4.0f);
		
		
		CVector2 EDamagepos= { 50,0 };
		for (int i = 0; i < 3;i++) {


			//m_DamageSeatTexture[i].Load("Assets/sprite/damage0.png");
			m_DamageSeatSprite[i].Init(&m_DamageSeatTexture[i]);
			m_DamageSeatSprite[i].SetPosition(EDamagepos);
			m_DamageSeatSprite[i].SetSize({ 100,80 });

			EDamagepos.x +=100.0f;
		}
		
		
		g_battleplayer->Particle(g_battleplayer->Getpos(),0);//攻撃パーティクル呼び出し
		

		g_battlemenu->SetHp(g_Hud->GetHP());


		
		g_battleplayer->SetDamage(g_battleenemy->GetATK(), true);//ダメージ計算とダメージアニメーション再生

		PDamage = true;


		
	}

	else if (EAttack && PDamage && g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
	{

		g_battleenemy->EnemyParticleDelete();//パーティクル消去
		g_battleplayer->ParticleDelete();//パーティクル消去
		//g_battleenemy->EnemyParticleDelete();//パーティクル消去

		m_sound_Attack->Stop();

		EAttack = false;
		PDamage = false;

		if (g_Hud->GetHP() <= 0)
		{

			Loseflg = true;//戦闘に負けた

			

			Victory = false;
			Comand = Result;
			
			//DeleteGO(g_battleScene);

			//リザルト画面を出す処理かシーン遷移？
		}

		SelectQ = false;
		result = false;

		turnCheng = true;
		return;

	}
}

void BattleScene::Defeat()
{

	if (Pad(0).IsTrigger(enButtonA))
	{
		DeleteGO(g_battleScene);
	}

}

void BattleScene::BattleResult()
{
	
	GetEXP[1] = g_Hud->GetLV();

	if (GetEXP[0] < GetEXP[1]) {
		m_ResultBGTexture7.Load("Assets/sprite/lvup.png");
		m_ResultBGSprite7.Init(&m_ResultBGTexture7);
		m_ResultBGSprite7.SetPosition({ 0,100 });
		//m_ResultBGSprite7.SetSize({ 100.0f,100.0f });

	}

	m_ComandBGTexture1.Load("Assets/sprite/comand.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ 0,0 });
	m_ComandBGSprite1.SetSize({ 700.0f,900.0f });


	m_ResultBGTexture6.Load("Assets/sprite/Result.png");
	m_ResultBGSprite6.Init(&m_ResultBGTexture6);
	m_ResultBGSprite6.SetPosition({ 0,250 });
	m_ResultBGSprite6.SetSize({ 300.0f,200.0f });




}

void BattleScene::BattleKeep()
{
	////////////////////////////////
	//敵に注目
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

void BattleScene::DamageTex(bool chara)
{
	
	int Damage = g_battleenemy->GetATK();
	if (chara)
	{
		Damage = g_battleenemy->GetATK();
	}
	else if(!chara)
	{
		Damage = g_battleplayer->GetATK();
	}

	
	NextDamage[0] = Damage / 100;
	
	sprintf(m_DamageTexName, "Assets/sprite/damagi%d.png", NextDamage[0]);
	//m_DamageSeatTexture[1].Release();
	m_DamageSeatTexture[0].Load(m_DamageTexName);

	Damage %= 100;

	NextDamage[1] = Damage / 10;
	
	sprintf(m_DamageTexName, "Assets/sprite/damagi%d.png", NextDamage[1]);
	//m_DamageSeatTexture[2].Release();
	m_DamageSeatTexture[1].Load(m_DamageTexName);

	Damage %= 10;
	NextDamage[2] = Damage;
	
	sprintf(m_DamageTexName, "Assets/sprite/damagi%d.png", NextDamage[2]);
	//m_DamageSeatTexture[2].Release();
	m_DamageSeatTexture[2].Load(m_DamageTexName);
	

	
}