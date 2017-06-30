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

	//���̃��x����n��
	int GetLV()const
	{
		return LV;
	}

	//�o���lUP
	void SetExp(int Setexp)
	{
		pExp += Setexp;
		LVUp();
		
	}


	//�o���l�擾
	int GetEXP() {
		return pExp;
	}

	//����HP���擾
	float GetHP()const
	{
		return MaxpHP;
	}

	//HP�̉�
	void RecoveryHP(float RecvHP)
	{
		MaxpHP += RecvHP;
		if (MaxpHP > MaxHP)
		{
			MaxpHP = MaxHP;
		}
	}

	//�ő�HP���Z�b�g
	void SetMaxHP(float SetHP)
	{
		MaxpHP = SetHP;
		
	}

	int GetMaxHP()
	{
		return MaxHP;

	}
	//�����Z�b�g
	void SetGold(int gold)
	{
		Gold += gold;
		
	}

	void SubtractGold(int gold)
	{
		Gold -= gold;
	}
	//�����Q�b�g
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
	int           pExp = 0;     //�o���l
	int           NextExp = 20; 
	
	int           Gold = 2000;
	
	int			ATK = 20;//���킲�Ƃɕω��H
	int			nextATK = g_random.GetRandInt() % 5+2;
	
	int			MaxHP = 500;
	int			nextHP = g_random.GetRandInt() % 10+2;
};
extern HUD*    g_Hud;

