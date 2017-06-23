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
	
	bool Winresult()//ゲームシーンに渡すやつ？
	{
		return Winflg;
	}

	bool Loseresult()//ゲームシーンに渡すやつ？
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


	CSprite		m_ComandBGSprite1;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture1;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite2;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture2;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite3;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture3;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite4;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture4;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_CasolBGSprite;		//!<戦闘画面の選択のスプライト。
	CTexture	m_CasolBGTexture;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ResultBGSprite1;		//!<リザルト画面のスプライト。
	CTexture	m_ResultBGTexture1;		//!<リザルト画面のテクスチャ。

	CSprite		m_ResultBGSprite2;		//!<リザルト画面のスプライト。
	CTexture	m_ResultBGTexture2;		//!<リザルト画面のテクスチャ。

	CSprite		m_ResultBGSprite3;		//!<リザルト画面のスプライト。
	CTexture	m_ResultBGTexture3;		//!<リザルト画面のテクスチャ。

	CSprite		m_ResultBGSprite4;		//!<リザルト画面のスプライト。
	CTexture	m_ResultBGTexture4;		//!<リザルト画面のテクスチャ。

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

	bool	IsBattle = false; //コマンド画面を表示するかの判定
	bool	IsBattleStart = false; //プレイヤーが配置についたかの判定
	bool	result = false; //result画面遷移用
	bool	Victory = true; //勝敗判定用
	bool	EnemyPointCamera = true; //敵選択カメラの判定
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

	int		Bcase;//敵の配置状態の種類
	
	CVector3 BCamerapos = { 2.0f, 50.2f, -3.5f };//敵の配置ごとのカメラの位置
	bool Resultflg2 = true;
	int Prandom = 0;
	int Erandom = 0;
	float ResultTime = 0; //result画面が終わる時間

};

extern BattleScene* g_battleScene;

