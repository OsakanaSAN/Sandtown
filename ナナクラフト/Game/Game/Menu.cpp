#include "stdafx.h"
#include "Menu.h"
#include "Camera.h"
#include "Scene/GameScene.h"
#include "Player.h"
#include "GameSound.h"
#include "HUD.h"
#include "BattleMenu.h"
#include "BattlePlayer.h"

extern CRandom g_random;

Menu::Menu()
{

	BackSeatTexture2.Load("Assets/UI/ui1.png");
	BackSeatSprite2.SetPivot({ 0.0f,1.0f });
	BackSeatSprite2.Init(&BackSeatTexture2);
	BackSeatSprite2.SetPosition({ -600.0f,200.0f });
	BackSeatSprite2.SetSize({ 800.0f,400.0f });

	//ゴールドのテキスト文字
	GoldSeatTexture[0].Load("Assets/UI/riru.png");
	GoldSeatSprite[0].SetPivot({ 0.0f,1.0f });
	GoldSeatSprite[0].Init(&GoldSeatTexture[0]);
	GoldSeatSprite[0].SetPosition({-50.0f,-90.0f});
	GoldSeatSprite[0].SetSize({ 100.0f,50.0f });

	//HPのテキスト文字
	HpSeatTexture[0].Load("Assets/UI/HP.png");
	HpSeatSprite[0].SetPivot({ 0.0f,0.5f });
	HpSeatSprite[0].Init(&HpSeatTexture[0]);
	HpSeatSprite[0].SetPosition({ -350.0f,0.0f });
	HpSeatSprite[0].SetSize({ 100.0f,80.0f });

	//LVのテキスト文字
	LvSeatTexture.Load("Assets/UI/Lv.png");
	LvSeatSprite.SetPivot({ 0.0f,1.0f });
	LvSeatSprite.Init(&LvSeatTexture);
	LvSeatSprite.SetPosition(LvSeatpos);
	LvSeatSprite.SetSize({ 100.0f,80.0f });
	
	//LV(数字)
	LvSeatTexture2.Load("Assets/UI/1.png");
	LvSeatSprite2.SetPivot({ 0.0f,1.0f });
	LvSeatSprite2.Init(&LvSeatTexture2);
	LvSeatSprite2.SetPosition(LvSeatpos2);
	LvSeatSprite2.SetSize({ 50.0f,80.0f });

	//斜線
	MaxHpSeatTexture[0].Load("Assets/UI/syasen.png");
	MaxHpSeatSprite[0].SetPivot({ 0.0f,0.5f });
	MaxHpSeatSprite[0].Init(&MaxHpSeatTexture[0]);
	MaxHpSeatSprite[0].SetPosition({ -60.0f,0.0f });
	MaxHpSeatSprite[0].SetSize({ 50.0f,50.0f });
	
	//アイコン
	IconSeatTexture.Load("Assets/UI/unity.png");
	IconSeatSprite.SetPivot({ 0.5f,0.5f });
	IconSeatSprite.Init(&IconSeatTexture);
	IconSeatSprite.SetPosition(Iconseatpos);
	IconSeatSprite.SetSize({ 200.0f,200.0f });

	//数字
	for (int i = 1; i < 4;i++) {

		//HP
		HpSeatTexture[i].Load("Assets/UI/0.png");
		HpSeatSprite[i].SetPosition(Hpseatpos);
		HpSeatSprite[i].Init(&HpSeatTexture[i]);
		HpSeatSprite[i].SetSize({ 50.0f,50.0f });

		//MaxHP
		MaxHpSeatTexture[i].Load("Assets/UI/0.png");
		MaxHpSeatSprite[i].SetPosition(MaxHpseatpos);
		MaxHpSeatSprite[i].Init(&MaxHpSeatTexture[i]);
		MaxHpSeatSprite[i].SetSize({ 50.0f,50.0f });

		//Gold
		GoldSeatTexture[i].Load("Assets/UI/0.png");
		GoldSeatSprite[i].SetPosition(GoldSeatpos);
		GoldSeatSprite[i].Init(&GoldSeatTexture[i]);
		GoldSeatSprite[i].SetSize({ 50.0f,50.0f });


		Hpseatpos.x += 50;
		MaxHpseatpos.x += 50;
		GoldSeatpos.x += 50;
	}


	


}


Menu::~Menu()
{
	
	

}


bool Menu::Start()
{
	//背景
	BackSeatTexture.Load("Assets/UI/ui1.png");
	BackSeatSprite.Init(&BackSeatTexture);
	BackSeatSprite.SetSize({ 1920.0f,1080.0f });

	

	for (int J = 0;J < 5;J++)
	{
		for (int I = 0;I < 6;I++)
		{
			//インベントリ

			InventorySeatTexture[J][I].Load("Assets/UI/ui1.png");

			InventorySeatSprite[J][I].SetPosition(InventoryPos);
			InventorySeatSprite[J][I].Init(&InventorySeatTexture[J][I]);
			InventorySeatSprite[J][I].SetSize({ 100.0f,100.0f });
			InventoryPos.x += 100;
		}

		InventoryPos.y -= 100;
		InventoryPos.x -= 600;

	}

	HpChangTex();
	MaxHpChangTex();
	GoldChangTex();
	
	

	return true;
}

void Menu::Update()
{
	switch (setMenu) {
	case STOP:
		break;

	case MENU:
		HpChangTex();
		MaxHpChangTex();
		GoldChangTex();

		if (Pad(0).IsPress(enButtonA))
		{

			MenuSceneStop();
		}

		else if (Pad(0).IsPress(enButtonDown) && setMenu == MENU)
		{
			setMenu = INVENTORY;
		}
		break;

	case INVENTORY:

		if (Pad(0).IsPress(enButtonUp) && setMenu == INVENTORY)
		{
			setMenu = MENU;
		}

		if (Pad(0).IsPress(enButtonA) && setMenu == INVENTORY)
		{
			UseItem();

		}

		break;
		case BATTLEINVENTORY:

			if (Pad(0).IsPress(enButtonA) && setMenu == INVENTORY)
			{
				UseItem();

			}
		break;
	}

}

void Menu::Render(CRenderContext& renderContext)
{
	
	switch (setMenu) {

	case STOP:
		break;

	case MENU:
		BackSeatSprite.Draw(renderContext);

		BackSeatSprite2.Draw(renderContext);
		IconSeatSprite.Draw(renderContext);
		LvSeatSprite.Draw(renderContext);
		LvSeatSprite2.Draw(renderContext);

		for (int i = 0;i < 4;i++)
		{
			HpSeatSprite[i].Draw(renderContext);
			MaxHpSeatSprite[i].Draw(renderContext);
			GoldSeatSprite[i].Draw(renderContext);
		}
		break;
	case INVENTORY:

		BackSeatSprite.Draw(renderContext);
		for (int J = 0;J < 5;J++)
		{
			for (int I = 0;I < 6;I++)
			{
				InventorySeatSprite[J][I].Draw(renderContext);


			}

		}

		break;

	case BATTLEINVENTORY:

		BackSeatSprite.Draw(renderContext);
		for (int J = 0;J < 5;J++)
		{
			for (int I = 0;I < 6;I++)
			{
				InventorySeatSprite[J][I].Draw(renderContext);


			}

		}
		break;

	}
}

void Menu::HpChangTex()
{
	
	int NextHP[3];
	int ChangHP = HP;
	

	NextHP[0] = ChangHP / 100;
	sprintf(HpTexName, "Assets/UI/%d.png", NextHP[0]);
	HpSeatTexture[1].Release();
	HpSeatTexture[1].Load(HpTexName);

	ChangHP %= 100;

	NextHP[1] = ChangHP / 10;
	sprintf(HpTexName, "Assets/UI/%d.png", NextHP[1]);
	HpSeatTexture[2].Release();
	HpSeatTexture[2].Load(HpTexName);

	ChangHP %= 10;
	NextHP[2] = ChangHP;
	sprintf(HpTexName, "Assets/UI/%d.png", NextHP[2]);
	HpSeatTexture[3].Release();
	HpSeatTexture[3].Load(HpTexName);


}

void Menu::MaxHpChangTex()
{

	int MaxNextHP[3];
	int MaxChangHP = MaxHP;


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
void Menu::LvChangTex()
{

	sprintf(LvTexName, "Assets/UI/%d.png", LV);
	LvSeatTexture2.Load(LvTexName);

}

void Menu::GoldChangTex()
{

	int NextGold[3];
	int NextGoldChang = GoldChang;

	NextGold[0] = NextGoldChang / 100;
	sprintf(GoldName, "Assets/UI/%d.png", NextGold[0]);
	GoldSeatTexture[1].Release();
	GoldSeatTexture[1].Load(GoldName);

	NextGoldChang %= 100;

	NextGold[1] = NextGoldChang / 10;
	sprintf(GoldName, "Assets/UI/%d.png", NextGold[1]);
	GoldSeatTexture[2].Release();
	GoldSeatTexture[2].Load(GoldName);

	NextGoldChang %= 10;
	NextGold[2] = NextGoldChang;
	sprintf(GoldName, "Assets/UI/%d.png", NextGold[2]);
	GoldSeatTexture[3].Release();
	GoldSeatTexture[3].Load(GoldName);


}
void Menu::InventoryChangTex(int Item)
{
	InventoryPack[InventoryPackNumber] = Item;
	InventoryPackNumber++;

	if (InventoryY < 5) {
		sprintf(InvebtoryName, "Assets/Item/Item%d.png", Item);
		InventorySeatTexture[InventoryY][InventoryX].Release();
		InventorySeatTexture[InventoryY][InventoryX].Load(InvebtoryName);
		InventorySeatSprite[InventoryY][InventoryX].Init(&InventorySeatTexture[InventoryY][InventoryX]);
		InventorySeatSprite[InventoryY][InventoryX].SetSize({ 100.0f, 100.0f });

		InventoryX++;
		if (InventoryX >= 6)
		{
			InventoryX = 0;
			InventoryY++;
		}
	}



}

void Menu::MenuSceneStop()
{

	g_gameCamera->ChangeStart();
	g_gameScene->SceneStop();
	if (g_player != nullptr)
	{
		g_player->IsMoveSTART();
	}
	g_sound->VolumeNormal();

	setMenu = STOP;

}
void Menu::BattleMenuStop()
{
	setMenu = STOP;
}

void Menu::MenuSceneexit()
{


	setMenu = STOP;

}

bool Menu::UseItem()
{

	if (g_Hud->GetHP() >= 500) { return false; } //HPの上限に達していたら帰る
	if (InventoryPackNumber <= 0) { return false; } //使うことができるアイテムが無ければ帰る



	for (int count = 0;count < InventoryPackNumber;count++) {

		if (InventoryPack[count] == 3)
		{
			for (count;count < InventoryPackNumber;count++)
			{
				int box = InventoryPack[count + 1];
				InventoryPack[count + 1] = 0;
				InventoryPack[count] = box;


			}

			g_Hud->RecoveryHP(100); //100回復
			setHP(g_Hud->GetHP());
			g_battlemenu->SetHp(g_Hud->GetHP());


			if (g_battleplayer != nullptr) {
				CVector3 Bpos = g_battleplayer->Getpos();
				Bpos.z = Bpos.z - 0.9f;
				g_battleplayer->Particle(Bpos, 1);//回復パーティクルの呼び出し
			}
			break;
		}
	}

	return true;

		
}