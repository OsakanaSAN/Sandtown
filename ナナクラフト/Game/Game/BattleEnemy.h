#pragma once


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

	void Setpos(CVector3 pos)
	{
		position[0] = pos;
	}

	//注目キャラ
	void EnemyCameraSetpos(CVector3 pos)
	{
		ECP = pos;
	}
	CVector3 GetEnemyCameraPos()
	{
		return ECP;
	}

	CVector3* Getpos(int EnemyNo)
	{
		return &position[EnemyNo];
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

	void SetEnemyNo(int No)
	{
		EnemyNo = No;
	}

	int GetEnemyNo()
	{
		return EnemyNo;
	}

	void SetBattlecase(int Bcase)
	{
		Battlecase = Bcase;
	}

	int GetBattlecase()
	{
		return Battlecase;
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

	enum Battlecase
	{
		Single,
		Double,
		Cross,
		Cross2,
	};
	const static int eneNo = 4;
	CSkinModel				skinModel[eneNo];
	CSkinModelDataHandle	skinModelData[eneNo];
	CAnimation				Animation[eneNo];
	CVector3				position[eneNo];
	CQuaternion				m_rotation[eneNo];

	CLight			All;


	bool			IsAttack;
	bool			IsStand;
	bool			IsDamage;
	bool			IsAnimend;

	int				currentAnimSetNo;

	int				EnemyNo = 0;
	////エネミーごとのステータス?
	int				ATK=20;
	int				HP=50;
	int				Exp=20;
	int             EGold=20;

	////////////////////////////////////

	int Battlecase = g_random.GetRandInt() % 4;



	int EnemyCameraChange;

	CVector3 ECP; //注目時の敵
};
extern BattleEnemy* g_battleenemy;
