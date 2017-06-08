#pragma once

class HUD : public IGameObject
{
public:
	HUD();
	~HUD();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	void Damage(int Attak);


	int GetNextHp()
	{
		return nextHP;
	}

	//今のレベルを渡す
	int GetLV()const
	{
		return LV;
	}

	//経験値の取得
	void SetExp(int Setexp)
	{
		pExp += Setexp;
		
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
		if (MaxpHP > 500)
		{
			MaxpHP = 500;
		}
	}

	//最大HPをセット
	void SetMaxHP(float SetHP)
	{
		MaxpHP = SetHP;
		
	}

	//お金セット
	void SetGold(int gold)
	{
		Gold += gold;
		
	}

	void Shiharai(int gold)
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

	void LVUp();


private:


	int           LV = 1;
	char          iName[256];
	float         nextHP = 10;
	float         nextexp = 0;
	float         MaxpHP = 500.0f;
	int           pExp = 0;     //経験値
	int           NextExp = 20; 
	
	int           Gold = 300;
	
	int			  ATK = 20;//武器ごとに変化？
};
extern HUD*    g_Hud;

