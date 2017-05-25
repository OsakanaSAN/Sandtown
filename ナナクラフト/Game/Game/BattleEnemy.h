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


	CSkinModel		skinModel;
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

	////エネミーごとのステータス?
	int				ATK = 10;
	int				HP = 30;
	int				Exp = 15;

	int             EGold = 50;

	int				EnemyID;//ゲームシーンから何のエネミーかの情報を格納

};
