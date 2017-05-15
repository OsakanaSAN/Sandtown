#include "stdafx.h"
#include "BattleScene.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "BattlePlayer.h"
//#include "Camera.h"
#include "BattleMap.h"
#include "Fade.h"
#include "BattleEnemy.h"
#include "BattleCamera.h"

extern Fade* g_fade;
BattlePlayer* g_battleplayer;
BattleCamera* g_battleCamera;
BattleEnemy* g_battleenemy;
BattleMap* g_battlemap;

BattleScene* g_battleScene = NULL;


BattleScene::BattleScene()
{
	g_battlemap = NewGO<BattleMap>(0);
	g_battleplayer = NewGO<BattlePlayer>(0);
	g_battleCamera = NewGO<BattleCamera>(0);
	g_battleenemy = NewGO<BattleEnemy>(0);

}


BattleScene::~BattleScene()
{
	DeleteGO(g_battleplayer);
	DeleteGO(g_battlemap);
	DeleteGO(g_battleenemy);
	DeleteGO(g_battleCamera);
	DeleteGO(this);
	NewGO<GameScene>(0);

}


bool BattleScene::Start()
{
	if (g_battleplayer != nullptr && g_battleCamera != nullptr) {
		g_fade->StartFadeIn();
	}
	
	Winflg = false;
	Loseflg = false;
	

	PAttack = false;
	EAttack = false;
	PDamage = false;
	EDamage = false;
	/*PAnimEnd = false;
	EAnimEnd = false;*/

	SelectQ = false;
	m_ComandBGTexture2.Load("Assets/sprite/co1.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -400,-200 });

	m_ComandBGTexture3.Load("Assets/sprite/co4.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -300,-300 });

	return true;
}


void BattleScene::Update()
{
	
	//タイトル画面に遷移する。
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
			DeleteGO(this);
		}
		break;

	}

	
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_ComandBGTexture2.Load("Assets/sprite/co2.png");
		m_ComandBGSprite2.Init(&m_ComandBGTexture2);
		m_ComandBGSprite3.SetPosition({ -400,-200 });

		m_ComandBGTexture3.Load("Assets/sprite/co4.png");
		m_ComandBGSprite3.Init(&m_ComandBGTexture3);
		m_ComandBGSprite3.SetPosition({ -300,-300 });

		Comand = Attack;

	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000&&!SelectQ)
	{
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

	/*PAttack = g_battleplayer->GetAttack();
	EAttack = g_battleenemy->GetAttack();
	PDamage = g_battleplayer->GetDamage();
	EDamage = g_battleenemy->GetDamage();
	PAnimEnd = g_battleplayer->GetAnimend();
	EAnimEnd = g_battleenemy->GetAnimend();*/

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
				g_battleplayer->SetAttack(true);//攻撃モーション
				SelectQ = true;
				PAttack = true;

			}
			else if(PAttack&&!EDamage&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
			{
				g_battleenemy->SetDamage(g_battleplayer->GetATK(), true);//ダメージ処理
				EDamage = true;
			}
			else if(PAttack &&EDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
			{

				PAttack= false;
				EDamage= false;
				if (g_battleenemy->GetHP() <= 0)
				{
					Winflg = true;//バトルに勝利した
					DeleteGO(this);
					return;
					/*g_battleenemy->Delete();*/
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
				//確率で逃げれるようにする？乱数とかで？
				DeleteGO(this);
				return;
			}

			break;
		}
		
		
	

}

void BattleScene::EnemyTurn()
{
	if(Turn == Pturn)return;
	if(PAttack)return;
	if(EDamage)return;
	

	if (!EAttack&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend()) {

		g_battleenemy->SetAttack(true);//攻撃のアニメーション再生
		
		EAttack = true;
	}
	else if (EAttack&&!PDamage && g_battleplayer->GetAnimend() && g_battleenemy->GetAnimend())
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