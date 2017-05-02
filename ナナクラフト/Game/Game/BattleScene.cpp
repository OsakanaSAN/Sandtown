#include "stdafx.h"
#include "BattleScene.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "BattlePlayer.h"
#include "Player.h"
#include "Camera.h"
#include "Fade.h"
#include "BattleEnemy.h"
#include "BattleCamera.h"
#include "Map.h"

extern Fade* g_fade;
extern Player* g_player;
extern Camera* g_gameCamera;

BattlePlayer* g_battleplayer = nullptr;
BattleEnemy* g_battleenemy = nullptr;


BattleScene* g_battleScene = NULL;



BattleScene::BattleScene()
{

	g_battleplayer = NewGO<BattlePlayer>(0);
	g_battleenemy = NewGO<BattleEnemy>(0);


}


BattleScene::~BattleScene()
{
	DeleteGO(g_battleplayer);
	DeleteGO(g_battleenemy);

	/*DeleteGO(g_battleCamera);*/
	NewGO<GameScene>(0);

	//DeleteGO(this);
	g_player = NewGO<Player>(0);
	g_player->Loadpos();           //座標を読み込む
	g_gameCamera->ChangeStart();   //カメラの更新を再開するを
	//NewGO<GameScene>(0);
	


	m_sound_bgm_battle2->Stop();
}


bool BattleScene::Start()
{
	

	

	m_sound_bgm_battle2 = NewGO<CSoundSource>(0);
	m_sound_bgm_battle2->Init("Assets/sound/bgm_maoudamashii_fantasy11.wav");
	m_sound_bgm_battle2->Play(true);
	m_sound_bgm_battle2->SetVolume(0.7f);

	Winflg = false;
	Loseflg = false;


	PAttack = false;
	EAttack = false;
	PDamage = false;
	EDamage = false;
	

	SelectQ = false;
	m_ComandBGTexture2.Load("Assets/sprite/co1.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -400,-200 });

	m_ComandBGTexture3.Load("Assets/sprite/co4.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -300,-300 });



	m_HPberTexture.Load("Assets/sprite/HP.png");
	m_HPberSprite.Init(&m_HPberTexture);
	m_HPberSprite.SetPosition({ -500,400 });
	m_HPberSprite.SetSize({ 750,400 });

	m_stateTexture.Load("Assets/sprite/1.png");
	m_stateSprite.Init(&m_stateTexture);
	m_stateSprite.SetPosition({ -900,500 });
	m_stateSprite.SetSize({ 100,100 });

	m_LevelTexture.Load("Assets/sprite/Lv.png");
	m_LevelSprite.Init(&m_LevelTexture);
	m_LevelSprite.SetPosition({ -800,500 });
	m_LevelSprite.SetSize({ 100,100 });


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



	if (GetAsyncKeyState(VK_UP) & 0x8000)
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

		Comand = Attack;

	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && !SelectQ)
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
		
		if (!SelectQ) {
			Comand = Escape;
		}
	}

	switch (Turn) {
	case Pturn://プレイヤーのターン
		PlayerTurn();
		break;
	case Eturn://エネミーのターン
		EnemyTurn();
		break;
	}

	//関数分けして早期リターンとかいれたほうがいい？
	//ダメージモーションが攻撃モーションの後に流れていない
	//攻撃処理のようにbool変数を作って処理すればいける？


}

void BattleScene::Render(CRenderContext&renderContext)
{

	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);


	m_HPberSprite.Draw(renderContext);
	m_LevelSprite.Draw(renderContext);
	m_stateSprite.Draw(renderContext);


}


void BattleScene::PlayerTurn()
{
	if (Turn == Eturn)return;
	if (EAttack)return;
	if (PDamage)return;

	switch (Comand)//選択肢
	{
	case Attack://攻撃

		if (!PAttack&&GetAsyncKeyState('Q') & 0x8000 && g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{

			if (!SelectQ)
			{
				m_sound_bgm_battle = NewGO<CSoundSource>(0);
				m_sound_bgm_battle->Init("Assets/sound/select3.wav");
				m_sound_bgm_battle->Play(false);
				m_sound_bgm_battle->SetVolume(5.0f);

			}

			g_battleplayer->SetAttack(true);//攻撃モーション
			SelectQ = true;
			PAttack = true;

		}
		else if (PAttack && !EDamage&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			g_battleplayer->Particle();
			g_battleenemy->SetDamage(g_battleplayer->GetATK(), true);//ダメージ処理
			EDamage = true;
		}
		else if (PAttack &&EDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			g_battleplayer->ParticleDelete();
			PAttack = false;
			EDamage = false;
			if (g_battleenemy->GetHP() <= 0)
			{
				Winflg = true;//バトルに勝利した
				DeleteGO(this);
				return;
				
				//レベルアップ判定
				//リザルト画面を出す処理その後シーン遷移？
			}
			Turn = Eturn;//敵のターン

		}





		break;

	case Escape://逃げる
		if (SelectQ)return;
		if (GetAsyncKeyState('Q') & 0x8000 && !PAttack)
		{
			if (!SelectQ)
			{
				m_sound_bgm_battle = NewGO<CSoundSource>(0);
				m_sound_bgm_battle->Init("Assets/sound/select3.wav");
				m_sound_bgm_battle->Play(false);
				m_sound_bgm_battle->SetVolume(5.0f);

			}

			//確率で逃げれるようにする？乱数とかで？
			DeleteGO(this);
			return;
		}

		break;
	}




}

void BattleScene::EnemyTurn()
{
	if (Turn == Pturn)return;
	if (PAttack)return;
	if (EDamage)return;


	if (!EAttack&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend()) {

		g_battleenemy->SetAttack(true);//攻撃のアニメーション再生

		EAttack = true;
	}
	else if (EAttack && !PDamage && g_battleplayer->GetAnimend() && g_battleenemy->GetAnimend())
	{
		g_battleplayer->SetDamage(g_battleenemy->GetATK(), true);//ダメージ計算とダメージアニメーション再生

		PDamage = true;
	}
	else if (EAttack &&PDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
	{

		EAttack = false;
		PDamage = false;

		if (g_battleplayer->GetHP() <= 0)
		{
			Loseflg = true;//戦闘に負けた
			DeleteGO(this);
			//リザルト画面を出す処理かシーン遷移？
		}
		SelectQ = false;
		Turn = Pturn;//プレイヤーのターン

	}

}
