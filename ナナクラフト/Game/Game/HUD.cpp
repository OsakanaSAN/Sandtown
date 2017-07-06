#include "stdafx.h"
#include "HUD.h"
#include "Player.h"
#include "BattleScene.h"
#include "Scene/GameScene.h"
#include "Fade.h"
#include "Menu.h"


HUD::HUD()
{


}

HUD::~HUD()
{
}
void HUD::HudLoad()
{

	ifstream fin("Assets/DATA/Hud.dat");
	if (!fin)
	{
		exit(0);
	}

	fin.precision(3);
	fin >> ATK >> pExp >> Gold >> MaxpHP >> LV >> MaxHP >> NextExp >> nextHP;
	fin.close();
}


bool HUD::Start()
{
	//HudLoad(); //セーブデータロード
	return true;
}

void HUD::Update()
{
	LVUp();
	
}
void HUD::Render(CRenderContext& renderContext)
{
}


//ダメージの判定
void HUD::Damage(int damage)
{
	MaxpHP -= damage;

}
void HUD::LVUp()
{
	if (pExp >= NextExp)
	{
		nextATK = g_random.GetRandInt() % 3 + 1;
		nextHP = g_random.GetRandInt() % 5 + 2;
		++LV;

		MaxHP += nextHP;
		MaxpHP = MaxHP;
		g_menu->setMaxHP(MaxHP);

		ATK += nextATK;
		SetATK(ATK);

		NextExp = NextExp * 2;
		
	}

}
