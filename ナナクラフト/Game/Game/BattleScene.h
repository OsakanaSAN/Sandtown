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
	bool Winresult()//ゲームシーンに渡すやつ？
	{
		return Winflg;
	}

	bool Loseresult()//ゲームシーンに渡すやつ？
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


	CSprite		m_ComandBGSprite2;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture2;		//!<戦闘画面の選択のテクスチャ。


	CSprite		m_ComandBGSprite3;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture3;		//!<戦闘画面の選択のテクスチャ。

//<<<<<<< HEAD
//	CSprite		m_LevelBGSprite4;		//!<戦闘画面の選択のスプライト。
//	CTexture	m_LevelBGTexture4;		//!<戦闘画面の選択のテクスチャ。
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

