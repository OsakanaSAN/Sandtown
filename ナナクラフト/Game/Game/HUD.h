#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class HUD : public IGameObject
{
public:
	HUD();
	~HUD();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	void Damage(int Attak);
	void HudLoad();

	int GetNextHp()
	{
		return nextHP;
	}

	//今のレベルを渡す
	int GetLV()const
	{
		return LV;
	}

	//経験値UP
	void SetExp(int Setexp)
	{
		pExp += Setexp;
		LVUp();
		
	}


	//経験値取得
	int GetEXP() {
		return pExp;
	}

	//今のHPを取得
	float GetHP()const
	{
		return MaxpHP;
	}

	//HPの回復
	void RecoveryHP(float RecvHP)
	{
		MaxpHP += RecvHP;
		if (MaxpHP > MaxHP)
		{
			MaxpHP = MaxHP;
		}
	}

	//最大HPをセット
	void SetMaxHP(float SetHP)
	{
		MaxpHP = SetHP;
		
	}

	int GetMaxHP()
	{
		return MaxHP;

	}
	//お金セット
	void SetGold(int gold)
	{
		Gold += gold;
		
	}

	void SubtractGold(int gold)
	{
		Gold -= gold;
	}
	//お金ゲット
	int GetGold()
	{
		return Gold;
	}

	int GetATK()
	{
		return ATK;
	}

	void SetATK(int atk)
	{
		ATK = atk;
	}
	void ATKUp(int Atk)
	{
		ATK += Atk;
	}

	int GetNextExp()
	{
		return NextExp;
	}
	void LVUp();

private:

	int           LV = 1;
	char          iName[256];
	float         nextexp = 0;
	float         MaxpHP = 500.0f;
	int           pExp = 0;     //経験値
	int           NextExp = 20; 
	
	int           Gold = 2000;
	
	int			ATK = 20;//武器ごとに変化？
	int			nextATK = g_random.GetRandInt() % 5+2;
	
	int			MaxHP = 500;
	int			nextHP = g_random.GetRandInt() % 10+2;
};
extern HUD*    g_Hud;

