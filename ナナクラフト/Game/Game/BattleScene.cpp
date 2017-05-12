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

extern Fade* g_fade;
extern Player* g_player;
extern Camera* g_gameCamera;

BattlePlayer* g_battleplayer = nullptr;
BattleEnemy* g_battleenemy = nullptr;

//BattleScene* g_battleScene = NULL;


BattleScene::BattleScene()
{

	g_battleplayer = NewGO<BattlePlayer>(0);
	g_battleenemy = NewGO<BattleEnemy>(0);

}


BattleScene::~BattleScene()
{
	DeleteGO(g_battleplayer);

	DeleteGO(g_battleenemy);
	g_player = NewGO<Player>(0);
	g_player->Loadpos();           //���W��ǂݍ���
	g_gameCamera->ChangeStart();   //�J�����̍X�V���ĊJ�����
	//NewGO<GameScene>(0);
	

}


bool BattleScene::Start()
{
	

	Winflg = false;
	Loseflg = false;


	PAttack = false;
	EAttack = false;
	PDamage = false;
	EDamage = false;
	/*PAnimEnd = false;
	EAnimEnd = false;*/

	SelectQ = false;

	m_ComandBGTexture1.Load("Assets/UI/HP.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ -400,-250 });
	m_ComandBGSprite1.SetSize({ 500,300 });

	m_ComandBGTexture2.Load("Assets/sprite/co1.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -300,-200 });

	m_ComandBGTexture3.Load("Assets/sprite/co4.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -300,-300 });

	m_DamageBGTexture4.Load("Assets/sprite/damage.tga");
	m_DamageBGSprite4.Init(&m_DamageBGTexture4);
	m_DamageBGSprite4.SetPosition({ -200,300 });

	m_CasolBGTexture5.Load("Assets/sprite/Casol.png");
	m_CasolBGSprite5.Init(&m_CasolBGTexture5);
	m_CasolBGSprite5.SetPosition({ -500,-200 });
	m_CasolBGSprite5.SetSize({ 200,200 });

	CVector3 lightPos, lightTarget;
	lightTarget.Add(g_battleplayer->Getpos(), g_battleenemy->Getpos());
	lightTarget.Scale(0.5f);
	lightPos = g_battleplayer->Getpos();
	lightPos.y += 5.0f;
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(g_battleplayer->Getpos());

	
	return true;
}


void BattleScene::Update()
{

	CVector3 Pintpos = g_battleplayer->Getpos();

	CVector3 Cpos = g_gameCamera->BGetPos();

	Pintpos.Subtract(Cpos);


	Dof().SetPint(Pintpos.Length() * 1000.0f);
	Dof().SetFocalLength(36.0f);


	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{

		if (Comand != Attack)
		{
			
			m_sound_bgm_battle = NewGO<CSoundSource>(0);
			m_sound_bgm_battle->Init("Assets/sound/select.wav");
			m_sound_bgm_battle->Stop();
			m_sound_bgm_battle->Play(false);
			m_sound_bgm_battle->SetVolume(7.0f);
		
		}

		m_ComandBGTexture2.Load("Assets/sprite/co2.png");
		m_ComandBGSprite2.Init(&m_ComandBGTexture2);
		m_ComandBGSprite3.SetPosition({ -300,-200 });

		m_ComandBGTexture3.Load("Assets/sprite/co4.png");
		m_ComandBGSprite3.Init(&m_ComandBGTexture3);
		m_ComandBGSprite3.SetPosition({ -300,-300 });

		m_CasolBGTexture5.Load("Assets/sprite/Casol.png");
		m_CasolBGSprite5.Init(&m_CasolBGTexture5);
		m_CasolBGSprite5.SetPosition({ -500,-200 });
		m_CasolBGSprite5.SetSize({ 200,200 });

		Comand = Attack;

	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && !SelectQ)
	{
		if (Comand != Escape)
		{
			
			m_sound_bgm_battle = NewGO<CSoundSource>(0);
			m_sound_bgm_battle->Init("Assets/sound/select.wav");
			m_sound_bgm_battle->Stop();
			m_sound_bgm_battle->Play(false);
			m_sound_bgm_battle->SetVolume(7.0f);
		
		}

		m_ComandBGTexture3.Load("Assets/sprite/co3.png");
		m_ComandBGSprite3.Init(&m_ComandBGTexture3);
		m_ComandBGSprite3.SetPosition({ -300,-300 });

		m_ComandBGTexture2.Load("Assets/sprite/co1.png");
		m_ComandBGSprite2.Init(&m_ComandBGTexture2);
		m_ComandBGSprite2.SetPosition({ -300,-200 });

		m_CasolBGTexture5.Load("Assets/sprite/Casol.png");
		m_CasolBGSprite5.Init(&m_CasolBGTexture5);
		m_CasolBGSprite5.SetPosition({ -500,-300 });
		m_CasolBGSprite5.SetSize({ 200,200 });

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

void BattleScene::PostRender(CRenderContext&renderContext)
{
	m_ComandBGSprite1.Draw(renderContext);
	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);
	m_CasolBGSprite5.Draw(renderContext);
	if (EDamage || PDamage) {//�_���[�W�̕\��
		m_DamageBGSprite4.Draw(renderContext);
	}
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
			if (!SelectQ)
			{
				m_sound_bgm_battle = NewGO<CSoundSource>(0);
				m_sound_bgm_battle->Init("Assets/sound/select3.wav");
				m_sound_bgm_battle->Play(false);
				m_sound_bgm_battle->SetVolume(4.0f);

			}

			g_battleplayer->SetAttack(true);//�U�����[�V����
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

			g_battleplayer->Particle();//�p�[�e�B�N���Ăяo��
			g_battleenemy->SetDamage(g_battleplayer->GetATK(), true);//�_���[�W����



			EDamage = true;


		}
		else if (PAttack &&EDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
		{
			g_battleplayer->ParticleDelete();//�p�[�e�B�N������
			m_sound_Attack->Stop();
			PAttack = false;
			EDamage = false;
			
			if (g_battleenemy->GetHP() <= 0)
			{
				Winflg = true;//�o�g���ɏ�������
				DeleteGO(this);

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
			m_sound_bgm_battle = NewGO<CSoundSource>(0);
			m_sound_bgm_battle->Init("Assets/sound/select.wav");
			m_sound_bgm_battle->Play(false);
			//�m���œ������悤�ɂ���H�����Ƃ��ŁH
			DeleteGO(this);

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
		m_sound_Attack = NewGO<CSoundSource>(0);
		m_sound_Attack->Init("Assets/sound/Attack.wav");
		m_sound_Attack->Play(false);
		m_sound_Attack->SetVolume(4.0f);

		m_DamageBGTexture4.Load("Assets/sprite/damage.tga");
		m_DamageBGSprite4.Init(&m_DamageBGTexture4);
		m_DamageBGSprite4.SetPosition({ 250,200 });
		m_DamageBGSprite4.SetSize({ 200,80 });

		g_battleplayer->SetDamage(g_battleenemy->GetATK(), true);//�_���[�W�v�Z�ƃ_���[�W�A�j���[�V�����Đ�

		PDamage = true;




	}
	else if (EAttack &&PDamage&& g_battleenemy->GetAnimend() && g_battleplayer->GetAnimend())
	{

		m_sound_Attack->Stop();
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