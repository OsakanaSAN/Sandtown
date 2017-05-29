#pragma once
#include "tkEngine/character/tkCharacterController.h"
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

	bool GetAnimend()
	{
		return IsAnimend;
	}
private:

	enum ANIME {
		Stand_anim,
		Walk_anim,
		Attack_anim,
		Jump_anim,
		Dameg_anim,

	};


	CSkinModel				skinModel;
	CSkinModelDataHandle	skinModelData;
	CCharacterController	characterController;

	CAnimation				Animation;
	CParticleEmitter		*m_particle;
	CRandom					m_random;

	CVector3				position = { -3.0f,0.0f,-44.0f };
	CVector3                BakPositon = { -3.0f,0.0f,-46.0f };


	CQuaternion				m_rotation;

	CLight					All;

	int						currentAnimSetNo;
	bool					IsAttack;
	bool					IsStand;
	bool					IsDamage;
	bool					IsAnimend;

	bool                    IsSetPoint = false;
	bool                    IsStop = true;
	float                     Time = 0;

	//ゲームシーンから持ってくるステータス？
	int						ATK = 20;//武器ごとに変化？
	int						HP = 30;//ゲームシーンと同じ値に後々する
	int						EXP = 0;//経験値
};
extern BattlePlayer* g_battleplayer;