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

	void Result();

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
	bool turnCheng = true;


	CSprite		m_ComandBGSprite2;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture2;		//!<戦闘画面の選択のテクスチャ。


	CSprite		m_ComandBGSprite3;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture3;		//!<戦闘画面の選択のテクスチャ。


	bool		Winflg;
	bool		Loseflg;
	bool		PAttack;
	bool		EAttack;
	bool		PDamage;
	bool		EDamage;
	/*bool		PAnimEnd;
	bool		EAnimEnd;*/
	bool		SelectQ;//

	int         BattlGold = 0;

	bool        result = false;
	bool        Victory = true;
};

extern BattleScene* g_battleScene;

