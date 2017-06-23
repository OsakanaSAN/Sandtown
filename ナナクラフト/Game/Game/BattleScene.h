#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/character/tkCharacterController.h"



class BattleScene :
	public IGameObject
{
public:
	BattleScene();
	~BattleScene();

	bool Start() override;

	void Update() override;

	void PostRender(CRenderContext&renderContext);

	void BattleResult();
	void PlayerTurn();
	void EnemyTurn();
	void EnemyTurn1();
	void EnemyTurn2();
	void EnemyTurn3();
	void BattleKeep();
	void DamageTex(bool chara);
	void GetGoldTex(int GetGold);
	void GetExpTex(int GetExp);
	void Defeat();
	
	bool Winresult()//�Q�[���V�[���ɓn����H
	{
		return Winflg;
	}

	bool Loseresult()//�Q�[���V�[���ɓn����H
	{
		return Loseflg;
	}
	void IsBattleStrat()
	{
		IsBattleStart = true;
	}

	int GetBcase()
	{
		return Bcase;
	}
	
private:

	CRandom			m_random;
	CSoundSource*	m_sound_bgm_battle;
	CSoundSource*	m_sound_bgm_battle2;
	CSoundSource*	m_sound_Attack;

	void SetPrandom(int rand)
	{
		Prandom = rand;
	}

	void SetErandom(int rand)
	{
		Erandom = rand;
	}

	enum set
	{
		damage,
		out,

	};
	set sets = damage;

	enum BattleComand
	{
		Keep,
		Attack,
		Escape,
		Result,
		Item,
		INVENTORY
	};
	BattleComand Comand = Keep;

	enum TURN
	{
		Pturn,
		Eturn,
	};
	TURN	Turn = Pturn;
	bool	turnCheng = true;


	CSprite		m_ComandBGSprite1;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture1;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite2;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture2;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite3;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture3;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite4;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture4;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_CasolBGSprite;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_CasolBGTexture;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ResultBGSprite1;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture1;		//!<���U���g��ʂ̃e�N�X�`���B

	CSprite		m_ResultBGSprite2;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture2;		//!<���U���g��ʂ̃e�N�X�`���B

	CSprite		m_ResultBGSprite3;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture3;		//!<���U���g��ʂ̃e�N�X�`���B

	CSprite		m_ResultBGSprite4;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture4;		//!<���U���g��ʂ̃e�N�X�`���B

	CSprite     m_DamageSeatSprite[3];
	CTexture    m_DamageSeatTexture[3];
	CVector2    m_Damageseatpos = { -240,250 };
	char        m_DamageTexName[255];
	int			NextDamage[3];

	CSprite     m_GoldSeatSprite[3];
	CTexture    m_GoldSeatTexture[3];
	CVector2    m_Goldseatpos = { -250,0 };
	char        m_GoldTexName[255];
	int			NextGold[3];

	CSprite     m_ExpSeatSprite[3];
	CTexture    m_ExpSeatTexture[3];
	CVector2    m_Expseatpos = { -250,-200 };
	char        m_ExpTexName[255];
	int			NextExp[3];

	bool	Resultflg2 = true;
	bool	Winflg = false;
	bool	Loseflg = false;
	bool	PAttack = false;
	bool	EAttack = false;
	bool	PDamage = false;
	bool	EDamage = false;
	bool	SelectQ = false;
	bool	Itemuse = false;

	bool	IsBattle = false; //�R�}���h��ʂ�\�����邩�̔���
	bool	IsBattleStart = false; //�v���C���[���z�u�ɂ������̔���
	bool	result = false; //result��ʑJ�ڗp
	bool	Victory = true; //���s����p
	bool	EnemyPointCamera = true; //�G�I���J�����̔���
	bool	EnemyZoom = false;
	bool	Resultflg = false;

	int		DefTime = 0;
	int		GetEXP[2] = { 0,0 };
	int		BattlGold = 0;

	float	m_timer = 0;
	
	int		Prandom = 0;
	int		Erandom = 0;

	bool	Eneturn = false;
	bool	Eneturn1 = false;
	bool	Eneturn2 = false;
	bool	Eneturn3 = false;
	bool	EnemyturnEnd = true;

	int		Bcase;//�G�̔z�u��Ԃ̎��
	
	CVector3 BCamerapos = { 2.0f, 50.2f, -3.5f };//�G�̔z�u���Ƃ̃J�����̈ʒu
	bool Resultflg2 = true;
	int Prandom = 0;
	int Erandom = 0;
	float ResultTime = 0; //result��ʂ��I��鎞��

};

extern BattleScene* g_battleScene;

