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
		g_gameScene->SceneStop();
		g_player = NewGO<Player>(0);
		g_player->Loadpos();//���W��ǂݍ���
		g_gameCamera->ChangeStart();   //�J�����̍X�V���ĊJ�����
		g_sound->DoukutuSound();
	}
	else
	{
		g_Hud->SetMaxHP(500.0f);
		DeleteGO(g_battleenemy);
		g_gameScene->SceneStop();
		//g_player = NewGO<Player>(0);
		g_gameCamera->ChangeStart();   //�J�����̍X�V���ĊJ�����
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
	m_ComandBGTexture2.Load("Assets/sprite/co2.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -400,-200 });

	m_ComandBGTexture3.Load("Assets/sprite/co4.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -300,-300 });

	g_sound->BattleSound();

	return true;
}


void BattleScene::Update()
{
	if (Victory == true) {


		switch (result) {

		case false:



			if (Pad(0).IsPress(enButtonUp))
			{
				m_ComandBGTexture2.Load("Assets/sprite/co2.png");
				m_ComandBGSprite2.Init(&m_ComandBGTexture2);
				m_ComandBGSprite3.SetPosition({ -400,-200 });

				m_ComandBGTexture3.Load("Assets/sprite/co4.png");
				m_ComandBGSprite3.Init(&m_ComandBGTexture3);
				m_ComandBGSprite3.SetPosition({ -300,-300 });

				Comand = Attack;

			}


			if (Pad(0).IsPress(enButtonDown) && Comand == Attack)
			{
				m_ComandBGTexture3.Load("Assets/sprite/co3.png");
				m_ComandBGSprite3.Init(&m_ComandBGTexture3);
				m_ComandBGSprite3.SetPosition({ -300,-300 });
				m_ComandBGTexture2.Load("Assets/sprite/co1.png");
				m_ComandBGSprite2.Init(&m_ComandBGTexture2);
				m_ComandBGSprite2.SetPosition({ -400,-200 });
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
			g_gameScene->BattleDate();
		}

	}



}

void BattleScene::Render(CRenderContext&renderContext)
{

	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);

}


void BattleScene::PlayerTurn()
{
	//if (Turn == Eturn)return;
	if (EAttack)return;
	if (PDamage)return;

	switch (Comand)//�I����
	{
	case Attack://�U��

		if (Pad(0).IsPress(enButtonA) && g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			result = true;
			g_battleplayer->SetAttack(true);//�U�����[�V����
			SelectQ = true;
			PAttack = true;
			

		}
		else if (PAttack && !EDamage&&g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			g_battleenemy->SetDamage(g_battleplayer->GetATK(), true);//�_���[�W����
			EDamage = true;
		}
		else if (PAttack &&EDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{

			PAttack = false;
			EDamage = false;
			if (g_battleenemy->GetHP() <= 0)
			{
				
				g_Hud->SetGold(g_battleenemy->GetEGold());
				g_Hud->SetExp(g_battleenemy->GetExp());
				Winflg = true;//�o�g���ɏ�������
				g_gameScene->BattleDate();
				return;
				/*g_battleenemy->Delete();*/
				//���x���A�b�v����
				//���U���g��ʂ��o���������̌�V�[���J�ځH
			}
			//Turn = Eturn;//�G�̃^�[��
			turnCheng = false;

		}





		break;

	case Escape://������

		//if (SelectQ)return;
		if (Pad(0).IsPress(enButtonA))
		{
			//�m���œ������悤�ɂ���H�����Ƃ��ŁH
			g_gameScene->BattleDate();
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

		g_battleenemy->SetAttack(true);//�U���̃A�j���[�V�����Đ�

		EAttack = true;
	}
	else if (EAttack && !PDamage && g_battleplayer->GetAnimend() && g_battleenemy->GetAnimend())
	{
		g_battleplayer->SetDamage(g_battleenemy->GetATK(), true);//�_���[�W�v�Z�ƃ_���[�W�A�j���[�V�����Đ�

		PDamage = true;
	}
	else if (EAttack &&PDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
	{

		EAttack = false;
		PDamage = false;

		if (g_Hud->GetHP() <= 0)
		{

			Loseflg = true;//�퓬�ɕ�����
			//g_gameScene->BattleDate();
			Victory = false;
			Result();
			//���U���g��ʂ��o���������V�[���J�ځH
		}
		SelectQ = false;
		result = false;
		//Turn = Pturn;//�v���C���[�̃^�[��
		turnCheng = true;

	}

}

void BattleScene::Result()
{

	DeleteGO(g_battleplayer);

}