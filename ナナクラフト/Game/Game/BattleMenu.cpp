#include "stdafx.h"
#include "BattleMenu.h"


BattleMenu::BattleMenu()
{

	BakeTexTexture.Load("Assets/UI/ui1.png");
	BakeTexSprite.Init(&BakeTexTexture);
	BakeTexSprite.SetPosition(Bakepos);
	BakeTexSprite.SetSize({ 400.0f,150.0f });

	//プレイヤーアイコン
	PlayerIconTex.Load("Assets/UI/unity.png");
	PlayerIconSprite.Init(&PlayerIconTex);
	PlayerIconSprite.SetPosition({450.0f,-450.0f});
	PlayerIconSprite.SetSize({ 80.0f,80.0f });


	//HPのテキスト文字
	HpSeatTexture[0].Load("Assets/UI/HP.png");
	HpSeatSprite[0].SetPivot({ 0.0f,0.5f });
	HpSeatSprite[0].Init(&HpSeatTexture[0]);
	HpSeatSprite[0].SetPosition({ 500.0f,-450.0f });
	HpSeatSprite[0].SetSize({ 80.0f,50.0f });

	//斜線
	MaxHpSeatTexture[0].Load("Assets/UI/syasen.png");
	MaxHpSeatSprite[0].SetPivot({ 0.0f,0.5f });
	MaxHpSeatSprite[0].Init(&MaxHpSeatTexture[0]);
	MaxHpSeatSprite[0].SetPosition({ 670.0f,-450.0f });
	MaxHpSeatSprite[0].SetSize({ 30.0f,30.0f });

	for (int i = 1;i < 4;i++)
	{

		//HP
		HpSeatTexture[i].Load("Assets/UI/0.png");
		HpSeatSprite[i].SetPosition(Hpseatpos);
		HpSeatSprite[i].Init(&HpSeatTexture[i]);
		HpSeatSprite[i].SetSize({ 30.0f,30.0f });

		//MaxHP
		MaxHpSeatTexture[i].Load("Assets/UI/0.png");
		MaxHpSeatSprite[i].SetPosition(MaxHpseatpos);
		MaxHpSeatSprite[i].Init(&MaxHpSeatTexture[i]);
		MaxHpSeatSprite[i].SetSize({ 30.0f,30.0f });

		Hpseatpos.x += 30;
		MaxHpseatpos.x +=30;

	}
}


BattleMenu::~BattleMenu()
{
}


bool BattleMenu::Start()
{

	return true;
}


void BattleMenu::Update()
{

	MaxPlayerHp();

}

void BattleMenu::Render(CRenderContext& renderContext)
{
	BakeTexSprite.Draw(renderContext);
	PlayerIconSprite.Draw(renderContext);
	for (int i = 0;i < 4;i++)
	{
		MaxHpSeatSprite[i].Draw(renderContext);
		HpSeatSprite[i].Draw(renderContext);
	}

}

void BattleMenu::PlayerHp()
{
	int NextHP[3];
	int ChangHP = HP;


	NextHP[0] = ChangHP / 100;
	sprintf(HpTexName, "Assets/UI/%d.png", NextHP[0]);
	HpSeatTexture[1].Load(HpTexName);

	ChangHP %= 100;

	NextHP[1] = ChangHP / 10;
	sprintf(HpTexName, "Assets/UI/%d.png", NextHP[1]);
	HpSeatTexture[2].Load(HpTexName);

	ChangHP %= 10;
	NextHP[2] = ChangHP;
	sprintf(HpTexName, "Assets/UI/%d.png", NextHP[2]);
	HpSeatTexture[3].Load(HpTexName);

}

void BattleMenu::MaxPlayerHp()
{
	int MaxHP = 500;
	int MaxNextHP[3];
	int MaxChangHP = MaxHP;
	char HpTexName[255];


	MaxNextHP[0] = MaxChangHP / 100;
	sprintf(HpTexName, "Assets/UI/%d.png", MaxNextHP[0]);
	MaxHpSeatTexture[1].Load(HpTexName);

	MaxChangHP %= 100;

	MaxNextHP[1] = MaxChangHP / 10;
	sprintf(HpTexName, "Assets/UI/%d.png", MaxNextHP[1]);
	MaxHpSeatTexture[2].Load(HpTexName);

	MaxChangHP %= 10;
	MaxNextHP[2] = MaxChangHP;
	sprintf(HpTexName, "Assets/UI/%d.png", MaxNextHP[2]);
	MaxHpSeatTexture[3].Load(HpTexName);


}