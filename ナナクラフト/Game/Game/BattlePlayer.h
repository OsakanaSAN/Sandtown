#pragma once
#include "tkEngine/character/tkCharacterController.h"

class BattlePlayer :
	public IGameObject
{
public:
	BattlePlayer();
	~BattlePlayer();
	bool Start()override;
	void Update();
	void Render(CRenderContext&renderContext);
	void AnimationSet();

	CVector3 Getpos()
	{
		return position;
	}
	
	CVector3 Getpos2()
	{
		return BakPositon;
	}

	void SetAttack(bool Attack)
	{
		IsAttack = Attack;
		
	}

	void SetDamage(int ATK, bool Damage)
	{
		HP = HP - ATK;
		IsDamage = Damage;
	}

	int GetHP()
	{
		return HP;
	}

	int GetATK()
	{
		return ATK;
	}

	void SetATK(int atk)
	{
		ATK = atk;
	}

	void SetHP(int hp)
	{
		HP = hp;
	}

	bool GetAnimend()
	{
		return IsAnimend;
	}
private:

	/*enum ANIME {
		Stand_anim,
		Walk_anim,
		Run_anim,
		Jump_anim,
		Dameg_anim,

	};*/
	enum ANIME {
		Stand_anim,
		Dameg_anim,
		Run_anim,
		Attack_anim,
		

	};

	
	CSkinModel				skinModel;
	CSkinModelDataHandle	skinModelData;
	CCharacterController	characterController;

	CAnimation				Animation;

	CVector3				position = { -1.0f,50.0f,-4.5f };

	CVector3                BakPositon = { -2.0f,50.0f,-8.0f };


	CQuaternion				m_rotation;

	CLight					All;

	int						currentAnimSetNo;
	bool					IsAttack;
	bool					IsStand;
	bool					IsDamage = false;
	bool					IsAnimend;

	bool                    IsSetPoint = false;
	bool                    IsStop = true;
	float                   Time = 0;
	
	//ゲームシーンから持ってくるステータス？
	int						ATK=20;//武器ごとに変化？
	int						HP = 500;//ゲームシーンと同じ値に後々する
	int						EXP = 0;//経験値

	CVector3 scale = CVector3::One;
};
extern BattlePlayer* g_battleplayer;