#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "BattleCamera.h"
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
	void Particle();
	void ParticleDelete();

	CVector3 Getpos()
	{
		return position;
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

private:

	enum ANIME {
		Stand_anim,
		Attack_anim,
		Damage_anim,
	};

	CSkinModel				skinModel;
	CSkinModelData			skinModelData;
	CCharacterController	characterController;

	CAnimation				Animation;
	CParticleEmitter		*m_particle;
	CRandom					m_random;


	CVector3				position = { -3.0f,-0.0f,-45.0f };
	CQuaternion				m_rotation;

	CLight					All;

	int						currentAnimSetNo;
	bool					IsAttack;
	bool					IsStand;
	bool					IsDamage;
	bool					IsAnimend;

	//ゲームシーンから持ってくるステータス？
	int						ATK = 10;//武器ごとに変化？
	int						HP = 30;//ゲームシーンと同じ値に後々する
	int						EXP = 0;//経験値
};
