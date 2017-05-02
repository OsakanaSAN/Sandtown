#include "stdafx.h"
#include "BattleScene.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "BattlePlayer.h"
#include "Fade.h"
#include "BattleEnemy.h"
#include "BattleCamera.h"
#include "Map.h"

extern Fade* g_fade;
BattlePlayer* g_battleplayer;
BattleCamera* g_battleCamera;
BattleEnemy* g_battleenemy;



BattleScene* g_battleScene = NULL;


BattleScene::BattleScene()
{

	g_battleplayer = NewGO<BattlePlayer>(0);
	g_battleCamera = NewGO<BattleCamera>(0);
	g_battleenemy = NewGO<BattleEnemy>(0);


}


BattleScene::~BattleScene()
{
	DeleteGO(g_battleplayer);
	
	DeleteGO(g_battleenemy);
	DeleteGO(g_battleCamera);
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
	

	SelectQ = false;
	m_ComandBGTexture2.Load("Assets/sprite/co1.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -400,-200 });

	m_ComandBGTexture3.Load("Assets/sprite/co4.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -300,-300 });


	m_LevelBGTexture4.Load("Assets/sprite/1.png");
	m_LevelBGSprite4.Init(&m_LevelBGTexture4);
	m_LevelBGSprite4.SetPosition({ 0,0 });
	m_LevelBGSprite4.SetSize({ 500,500 });

	return true;
}


void BattleScene::Update()
{

	//�^�C�g����ʂɑJ�ڂ���B
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

	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && !SelectQ)
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

	

	switch (Turn) {
	case Pturn://�v���C���[�̃^�[��
		PlayerTurn();
		break;
	case Eturn://�G�l�~�[�̃^�[��
		EnemyTurn();
		break;
	}

	//�֐��������đ������^�[���Ƃ����ꂽ�ق��������H
	//�_���[�W���[�V�������U�����[�V�����̌�ɗ���Ă��Ȃ�
	//�U�������̂悤��bool�ϐ�������ď�������΂�����H


}

void BattleScene::Render(CRenderContext&renderContext)
{

	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);
	m_LevelBGSprite4.Draw(renderContext);
}


void BattleScene::PlayerTurn()
{
	if (Turn == Eturn)return;
	if (EAttack)return;
	if (PDamage)return;

	switch (Comand)//�I����
	{
	case Attack://�U��

		if (!PAttack&&GetAsyncKeyState('Q') & 0x8000 && g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
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
				Winflg = true;//�o�g���ɏ�������
				DeleteGO(this);
				return;
				/*g_battleenemy->Delete();*/
				//���x���A�b�v����
				//���U���g��ʂ��o���������̌�V�[���J�ځH
			}
			Turn = Eturn;//�G�̃^�[��

		}





		break;

	case Escape://������
		if (SelectQ)return;
		if (GetAsyncKeyState('Q') & 0x8000 && !PAttack)
		{
			//�m���œ������悤�ɂ���H�����Ƃ��ŁH
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

		if (g_battleplayer->GetHP() <= 0)
		{
			Loseflg = true;//�퓬�ɕ�����
			DeleteGO(this);
			//���U���g��ʂ��o���������V�[���J�ځH
		}
		SelectQ = false;
		Turn = Pturn;//�v���C���[�̃^�[��

	}

}
