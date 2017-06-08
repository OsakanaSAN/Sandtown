#pragma once
#include "BattleCamera.h"

class BattleEnemy :
	public IGameObject
{
public:
	BattleEnemy();
	~BattleEnemy();

	bool Start()override;
	void Update();
	void Render(CRenderContext&renderContext);
	void AnimationSet();

	void Delete();

	CVector3 Getpos()
	{
		return position;
	}

	void SetAttack(bool Acs)
	{
		IsAttack = Acs;
	}

	void SetDamage(int ATK, bool Damage)
	{
		HP = HP - ATK;
		IsDamage = Damage;
	}

	int GetHP() const
	{
		return HP;
	}

	int GetATK()
	{
		return ATK;
	}

	bool GetAnimend()
	{
		return IsAnimend;
	}

	/*bool GetAttack()
	{
	return IsAttack;
	}

	bool GetDamage()
	{
	return IsDamage;
	}*/

	int GetEGold()const
	{
		return EGold;
	}
	int GetExp()const
	{
		return Exp;
	}

private:

	enum ANIME {
		Stand_anim,
		Attack_anim,
		Damage_anim,
	};

	enum State {
		Alive,
		Dead
	};
	CSkinModel				skinModel;
	CSkinModelDataHandle	skinModelData;
	CAnimation		Animation;
	CVector3		position = { -2.0f,0.0f,-38.0f };
	CQuaternion		m_rotation;

	CLight			All;

	bool			IsAttack;
	bool			IsStand;
	
	bool			IsDamage;
	bool			IsAnimend;

	int				currentAnimSetNo;

	////�G�l�~�[���Ƃ̃X�e�[�^�X?
	int				ATK;
	int				HP;
	int				Exp;
	int             EGold;


};
extern BattleEnemy* g_battleenemy;
