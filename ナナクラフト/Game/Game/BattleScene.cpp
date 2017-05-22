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

BattlePlayer* g_battleplayer = nullptr;
BattleEnemy* g_battleenemy = nullptr;

BattleScene::BattleScene()
{

	g_battleplayer = NewGO<BattlePlayer>(0);
	g_battleenemy = NewGO<BattleEnemy>(0);
	
}


BattleScene::~BattleScene()
{
	
	if (Victory == true) {
		g_sound->StopSound();
		DeleteGO(g_battleplayer);
		DeleteGO(g_battleenemy);
		g_player = NewGO<Player>(0);
		g_player->Loadpos();           //座標を読み込む
		g_gameScene->SceneStop();
		g_gameCamera->ChangeStart();   //カメラの更新を再開するを
		g_sound->DoukutuSound();
	}

	else
	{
		g_Hud->SetMaxHP(500.0f);
		DeleteGO(g_battleenemy);
		g_gameScene->SceneStop();
		g_gameCamera->ChangeStart();   //カメラの更新を再開するを
		g_gameScene->MapChange();
	}

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
	/*PAnimEnd = false;
	EAnimEnd = false;*/

	SelectQ = false;

	m_DamageBGTexture4.Load("Assets/sprite/damage.tga");
	m_DamageBGSprite4.Init(&m_DamageBGTexture4);
	m_DamageBGSprite4.SetPosition({ -200,300 });

	m_ComandBGTexture2.Load("Assets/sprite/co2.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -400,-200 });

	m_ComandBGTexture3.Load("Assets/sprite/co4.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -300,-300 });

	m_CasolBGTexture5.Load("Assets/sprite/Casol.png");
	m_CasolBGSprite5.Init(&m_CasolBGTexture5);
	m_CasolBGSprite5.SetPosition({ -500,-200 });
	m_CasolBGSprite5.SetSize({ 200,200 });

	//g_sound->BattleSound();

	CVector3 lightPos, lightTarget;
	lightTarget.Add(g_battleplayer->Getpos(), g_battleenemy->Getpos());
	lightTarget.Scale(0.5f);
	lightPos = g_battleplayer->Getpos();
	lightPos.y += 5.0f;
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(lightTarget);


	return true;
}


void BattleScene::Update()
{


	CVector3 Pintpos;
	CVector3 Epos = g_battleenemy->Getpos();
	CVector3 Ppos = g_battleplayer->Getpos();

	Pintpos.Add(Ppos, Epos);
	Pintpos.Scale(0.5f);

	CVector3 Cpos = g_gameCamera->BGetPos();

	Pintpos.Subtract(Cpos);
	
	Dof().SetPint(Pintpos.Length()*1000);
	Dof().SetFocalLength(36.0f);

	if (Victory == true) {


		switch (result) {

		case false:



			if (Pad(0).IsPress(enButtonUp))
			{
				
				if (Comand != Attack)
				{
					m_sound_bgm_battle = NewGO<CSoundSource>(0);
					m_sound_bgm_battle->Init("Assets/sound/select.wav");
					m_sound_bgm_battle->Play(false);
					m_sound_bgm_battle->SetVolume(7.0f);
				}


				m_ComandBGTexture2.Load("Assets/sprite/co2.png");
				m_ComandBGSprite2.Init(&m_ComandBGTexture2);
				m_ComandBGSprite3.SetPosition({ -400,-200 });

				m_ComandBGTexture3.Load("Assets/sprite/co4.png");
				m_ComandBGSprite3.Init(&m_ComandBGTexture3);
				m_ComandBGSprite3.SetPosition({ -300,-300 });

				m_CasolBGTexture5.Load("Assets/sprite/Casol.png");
				m_CasolBGSprite5.Init(&m_CasolBGTexture5);
				m_CasolBGSprite5.SetPosition({ -500,-200 });
				m_CasolBGSprite5.SetSize({ 200,200 });

				Comand = Attack;

			}
			else if (Pad(0).IsPress(enButtonDown) && Comand == Attack)
			{
				if (Comand != Escape)
				{
					m_sound_bgm_battle = NewGO<CSoundSource>(0);
					m_sound_bgm_battle->Init("Assets/sound/select.wav");
					m_sound_bgm_battle->Play(false);
					m_sound_bgm_battle->SetVolume(7.0f);
				}

				m_ComandBGTexture3.Load("Assets/sprite/co3.png");
				m_ComandBGSprite3.Init(&m_ComandBGTexture3);
				m_ComandBGSprite3.SetPosition({ -300,-300 });
				m_ComandBGTexture2.Load("Assets/sprite/co1.png");
				m_ComandBGSprite2.Init(&m_ComandBGTexture2);
				m_ComandBGSprite2.SetPosition({ -400,-200 });

				m_CasolBGTexture5.Load("Assets/sprite/Casol.png");
				m_CasolBGSprite5.Init(&m_CasolBGTexture5);
				m_CasolBGSprite5.SetPosition({ -500,-300 });
				m_CasolBGSprite5.SetSize({ 200,200 });

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

void BattleScene::Render(CRenderContext&renderContext)
{

	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);
	m_CasolBGSprite5.Draw(renderContext);

	if (EDamage || PDamage) {//ダメージの表示
		m_DamageBGSprite4.Draw(renderContext);
	}
}


void BattleScene::PlayerTurn()
{
	//if (Turn == Eturn)return;
	if (EAttack)return;
	if (PDamage)return;

	switch (Comand)//選択肢
	{
	case Attack://攻撃

		if (Pad(0).IsPress(enButtonA) && g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
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



			m_DamageBGTexture4.Load("Assets/sprite/damage.tga");
			m_DamageBGSprite4.Init(&m_DamageBGTexture4);
			m_DamageBGSprite4.SetPosition({ -200,300 });
			m_DamageBGSprite4.SetSize({ 200,80 });

			g_battleplayer->Particle();//パーティクル呼び出し
			g_battleenemy->SetDamage(g_battleplayer->GetATK(), true);//ダメージ処理
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

				return;

				/*g_battleenemy->Delete();*/
				//レベルアップ判定
				//リザルト画面を出す処理その後シーン遷移？
			}
			//Turn = Eturn;//敵のターン
			turnCheng = false;

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
	}


}

void BattleScene::EnemyTurn()
{
	//if (Turn == Pturn)return;
	if (PAttack)return;
	if (EDamage)return;


	if (!EAttack&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend()) {

		g_battleenemy->SetAttack(true);//攻撃のアニメーション再生
		m_sound_Attack->Play(0);
		m_sound_Attack->SetVolume(4.0f);

		EAttack = true;
	}
	else if (EAttack && !PDamage && g_battleplayer->GetAnimend() && g_battleenemy->GetAnimend())
	{

		
		

		m_DamageBGTexture4.Load("Assets/sprite/damage.tga");
		m_DamageBGSprite4.Init(&m_DamageBGTexture4);
		m_DamageBGSprite4.SetPosition({ 250,200 });
		m_DamageBGSprite4.SetSize({ 200,80 });

		g_battleplayer->SetDamage(g_battleenemy->GetATK(), true);//ダメージ計算とダメージアニメーション再生
		

		PDamage = true;
	}
	else if (EAttack &&PDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
	{
		m_sound_Attack->Stop();
		EAttack = false;
		PDamage = false;

		if (g_Hud->GetHP() <= 0)
		{

			Loseflg = true;//戦闘に負けた

			/*g_gameScene->BattleDate();*/

			Victory = false;
			Result();

			//リザルト画面を出す処理かシーン遷移？
		}
		SelectQ = false;
		result = false;
		//Turn = Pturn;//プレイヤーのターン
		turnCheng = true;

	}
}

void BattleScene::Result()
{

	DeleteGO(g_battleplayer);

}