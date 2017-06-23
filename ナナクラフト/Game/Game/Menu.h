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
	void InventoryChangTex(int Item);
	void MenuSceneexit();
	void NoItem(int Nonumber);
	bool UseItem();

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

	void SetItem(int SetItem)
	{
		ItemNuber[Number] = SetItem;
		Number++;
	}
	
	void MenuScene()
	{
		setMenu = MENU;
	}

	void MenuSceneItem()
	{
		setMenu = BATTLEINVENTORY;
	}
	void MenuSceneStop();
	void BattleMenuStop();

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

	//インベントリ
	enum MENUCHANG {
		STOP,
		MENU,
		INVENTORY,
		BATTLEINVENTORY,

	};
	
	MENUCHANG        setMenu = STOP;
	CSprite          InventorySeatSprite[5][6];
	CTexture         InventorySeatTexture[5][6];
	CVector2         InventoryPos = { -300.0f,250.0f };
	char             InvebtoryName[255];
	int              InventoryX = 0;
	int              InventoryY = 0;
	int              NoInventX = 0;
	int              NoInventY = 0;
	int              ItemNuber[30];
	int              Number = 0;
	int              InventoryPack[30];
    int              InventoryPackNumber = 0;

	/////////////////////////////////////////////////////

};

extern Menu* g_menu;