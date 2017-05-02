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

//<<<<<<< HEAD
//	CSprite		m_LevelBGSprite4;		//!<�퓬��ʂ̑I���̃X�v���C�g�B
//	CTexture	m_LevelBGTexture4;		//!<�퓬��ʂ̑I���̃e�N�X�`���B
//
//=======
	CSprite		m_HPberSprite;
	CTexture	m_HPberTexture;

	CSprite		m_LevelSprite;
	CTexture	m_LevelTexture;

	CSprite		m_stateSprite;
	CTexture	m_stateTexture;


	bool		Winflg;
	bool		Loseflg;
	bool		PAttack;
	bool		EAttack;
	bool		PDamage;
	bool		EDamage;
	bool		SelectQ;
};

extern BattleScene* g_battleScene;

