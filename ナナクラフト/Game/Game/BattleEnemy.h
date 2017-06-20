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
	void EnemyParticle(CVector3 target);
	void EnemyParticleDelete();

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
	CVector3		position = { -2.0f,0.0f,0.0f };
	CQuaternion		m_rotation;

	CLight			All;


	bool			IsAttack;
	bool			IsStand;
	bool			IsDamage;
	bool			IsAnimend;

	int				currentAnimSetNo;

	////エネミーごとのステータス?
	int				ATK=20;
	int				HP=50;
	int				Exp=20;
	int             EGold=20;

	////////////////////////////////////
	//パーティクル系
	CParticleEmitter		*m_particle;
	CRandom					m_random;


};
extern BattleEnemy* g_battleenemy;
