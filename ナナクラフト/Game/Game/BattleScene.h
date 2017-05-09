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

	void Render(CRenderContext&renderContext);


	

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
		Attack,
		Escape,
	};
	BattleComand Comand = Attack;


	enum TURN
	{
		Pturn,
		Eturn,
	};
	TURN Turn = Pturn;


	CSprite		m_ComandBGSprite2;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture2;		//!<�퓬��ʂ̑I���̃e�N�X�`���B


	CSprite		m_ComandBGSprite3;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_ComandBGTexture3;		//!<�퓬��ʂ̑I���̃e�N�X�`���B


	CSprite		m_DamageBGSprite4;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
	CTexture	m_DamageBGTexture4;		//!<�퓬��ʂ̑I���̃e�N�X�`���B

	bool		Winflg;
	bool		Loseflg;
	bool		PAttack;
	bool		EAttack;
	bool		PDamage;
	bool		EDamage;
	bool		SelectQ;//

	bool Upflg = false;
	bool Downflg = false;
};

extern BattleScene* g_battleScene;

