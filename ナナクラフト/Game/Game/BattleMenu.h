#pragma once
class BattleMenu : public IGameObject
{
public:
	BattleMenu();
	~BattleMenu();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
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


	//バックシート
	CSprite    BakeTexSprite;
	CTexture   BakeTexTexture;
	CVector2   Bakepos = { 600.0f,-450.0f };


	////////////////////////////////////////////
	

};

