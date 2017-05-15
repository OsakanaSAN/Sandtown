#pragma once
class Menu :public IGameObject
{
public:
	Menu();
	~Menu();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	void HpChangTex();
	void MaxHpChangTex();
	void LvChangTex();
	void GoldChangTex();

	void setHP(int setHp)
	{
		HP = setHp;
		HpChangTex();
	}
	void setLV(int setLv)
	{
		LV = setLv;
		LvChangTex();
	}
	void SetGold(int SetGold)
	{
		GoldChang = SetGold;
	}



private:
	CSprite     BackSeatSprite;  //2番後ろ
	CTexture    BackSeatTexture;

	CSprite     BackSeatSprite2;  //2番後ろ
	CTexture    BackSeatTexture2;

	/////////////////////////////////////////////

	//現在のHP
	CSprite     HpSeatSprite[4];
	CTexture    HpSeatTexture[4];
	CVector2    Hpseatpos = { -180.0f,0.0f };
	int         HP = 100;
	char        HpTexName[255];
	
	///////////////////////////////////////////////

	//最大HP
	CSprite     MaxHpSeatSprite[4];
	CTexture    MaxHpSeatTexture[4];
	CVector2    MaxHpseatpos = {0.0f,0.0f};
	int         MaxHP = 500;

	////////////////////////////////////////////////

	//キャラアイコン
	CSprite     IconSeatSprite;
	CTexture    IconSeatTexture;
	CVector2    Iconseatpos = { -490.0f,0.0f };

	////////////////////////////////////////////////

	//レベル表示
	CSprite     LvSeatSprite;
	CTexture    LvSeatTexture;
	CVector2    LvSeatpos = { -350.0f,150.0f };

	CSprite     LvSeatSprite2;
	CTexture    LvSeatTexture2;
	CVector2    LvSeatpos2 = { -180.0f,150.0f };
	int         LV = 1;
	char        LvTexName[255];

	/////////////////////////////////////////////////

	//ゴールド

	CSprite     GoldSeatSprite[4];
	CTexture    GoldSeatTexture[4];
	CVector2    GoldSeatpos = {-180.0f,-100.0f};
	int         GoldChang = 0;

	char        GoldName[255];


	//////////////////////////////////////////////////

	
	

};

