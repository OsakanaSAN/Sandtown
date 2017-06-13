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
	void BattleKeep();
	void DamageTex(bool chara);
	
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

	
private:

	CRandom			m_random;

	CSoundSource*	m_sound_bgm_battle;
	CSoundSource*	m_sound_bgm_battle2;
	CSoundSource*	m_sound_Attack;

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
	TURN Turn = Pturn;
	bool turnCheng = true;


	CSprite		m_ComandBGSprite1;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture1;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite2;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture2;		//!<�퓬��ʂ̑I���̃e�N�X�`���B


	CSprite		m_ComandBGSprite3;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture3;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ComandBGSprite4;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture4;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite     m_DamageSeatSprite[3];
	CTexture    m_DamageSeatTexture[3];
	CVector2    m_Damageseatpos = { -240,250 };
	char        m_DamageTexName[255];


	CSprite		m_CasolBGSprite;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_CasolBGTexture;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_ResultBGSprite6;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture6;		//!<���U���g��ʂ̃e�N�X�`���B

	CSprite		m_ResultBGSprite7;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture7;		//!<���U���g��ʂ̃e�N�X�`���B

	CSprite		m_ResultBGSprite8;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture8;		//!<���U���g��ʂ̃e�N�X�`���B

	CSprite		m_ResultBGSprite9;		//!<���U���g��ʂ̃X�v���C�g�B
	CTexture	m_ResultBGTexture9;		//!<���U���g��ʂ̃e�N�X�`���B


	bool		Winflg;
	bool		Loseflg;
	bool		PAttack;
	bool		EAttack;
	bool		PDamage;
	bool		EDamage;
	bool		SelectQ;//
	bool Itemuse = false;

	int         BattlGold = 0;

	float			m_timer = 0;
	bool        IsBattle = false; //�R�}���h��ʂ�\�����邩�̔���
	bool        IsBattleStart = false; //�v���C���[���z�u�ɂ������̔���
	bool        result = false; //result��ʑJ�ڗp
	bool        Victory = true; //���s����p
	bool        EnemyPointCamera = true; //�G�I���J�����̔���
	bool        EnemyZoom = false;

	bool		Resultflg = false;


	int NextDamage[3];

};

extern BattleScene* g_battleScene;

