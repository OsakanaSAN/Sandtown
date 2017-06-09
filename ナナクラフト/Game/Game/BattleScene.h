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

	void BattleKeep();

private:


	CSoundSource*	m_sound_bgm_battle;
	CSoundSource*	m_sound_bgm_battle2;
	CSoundSource*	m_sound_Attack;

	enum set
	{
		in,
		out,

	};
	set sets = in;

	enum BattleComand
	{
		Keep,
		Attack,
		Escape,
		Result
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

	CSprite		m_DamageBGSprite4;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_DamageBGTexture4;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	CSprite		m_CasolBGSprite5;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_CasolBGTexture5;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

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

	int         BattlGold = 0;

	float			m_timer = 0;
	bool        IsBattle = false; //�R�}���h��ʂ�\�����邩�̔���
	bool        IsBattleStart = false; //�v���C���[���z�u�ɂ������̔���
	bool        result = false; //result��ʑJ�ڗp
	bool        Victory = true; //���s����p
	bool        EnemyPointCamera = true; //�G�I���J�����̔���
	bool        EnemyZoom = false;
	bool		Resultflg = false;

};

extern BattleScene* g_battleScene;

