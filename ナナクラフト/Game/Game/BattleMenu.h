#pragma once
class BattleMenu : public IGameObject
{
public:
	BattleMenu();
	~BattleMenu();
	bool Start()override;
	void Update();
	void PostRender(CRenderContext& renderContext);
	//プレイヤーバトル用のHP表示＆計算
	void MaxPlayerHp();
	void PlayerHp();

	void SetHp(int sethp)
	{
		HP = sethp;
		PlayerHp();
	}

	//エネミーバトル用のHP表示＆計算
	void MaxEnemyHp();
	void EnemyHp();

	void SetEnemyHp(int setenemyHp)
	{
		EnemyHP = setenemyHp;
		EnemyHp();

	}
	void SetEnemyMexHp(int setMax)
	{
		EnemyMaxHP = setMax;
		MaxEnemyHp();
	}

	///////////////////////////////////
	//プレイヤーのHP表示するかの判定
	void PlayerZoomSet()
	{
		if (PlayerZoom) { return; }
		PlayerZoom = true;
	}

	void PlayerZoomOut()
	{
		if (!PlayerZoom) { return; }
		PlayerZoom = false;
	}

	/////////////////////////////////////////
	//敵のHP表示するかの判定
	void EnemyZoomSet()
	{
		if (EnemyZoom) { return; }
		EnemyZoom = true;
	}
	void EnemyZoomOut()
	{
		if (!EnemyZoom) { return; }
		EnemyZoom = false;
	}

private:

	////////////////////////////////////////////
	
	CSprite    PlayerIconSprite;
	CTexture   PlayerIconTex;


	//現在のHP
	CSprite     HpSeatSprite[4];
	CTexture    HpSeatTexture[4];
	CVector2    Hpseatpos = { 600.0f,-450.0f };
	int         HP = 100;
	char        HpTexName[255];

	//最大HP
	CSprite     MaxHpSeatSprite[4];
	CTexture    MaxHpSeatTexture[4];
	CVector2    MaxHpseatpos = { 700.0f,-450.0f };

	//現在のエネミーHP
	CSprite     EnemyHpSeatSprite[4];
	CTexture    EnemyHpSeatTexture[4];
	CVector2    EnemyHpseatpos = { 600.0f,-450.0f };
	int         EnemyHP = 100;
	char        EnemyHpTexName[255];

	//最大エネミーHP
	CSprite     EnemyMaxHpSeatSprite[4];
	CTexture    EnemyMaxHpSeatTexture[4];
	CVector2    EnemyMaxHpseatpos = { 700.0f,-450.0f };
	int         EnemyMaxHP;

	//バックシート
	CSprite    BakeTexSprite;
	CTexture   BakeTexTexture;
	CVector2   Bakepos = { 600.0f,-450.0f };

	//バックシート
	CSprite    EnemyBakeTexSprite;
	CTexture   EnemyBakeTexTexture;
	CVector2   EnemyBakepos = { 600.0f,-450.0f };

	////////////////////////////////////////////
	bool PlayerZoom = true;
	bool EnemyZoom = false;
	

};

extern BattleMenu* g_battlemenu;