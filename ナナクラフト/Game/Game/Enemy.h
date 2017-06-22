#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy:public IGameObject
{
public :
	Enemy();
	~Enemy();
	bool Start()override;
	void Init(char* );
	void Update();
	void Render(CRenderContext&renderContext);
	CVector3 getPos() {
		return position;
	}

	void setPos(CVector3 pos)
	{
		position = pos;
		BakPosition = pos;
	}
	void Tracking();

	void LevelSet(int Level)
	{
		switch (Level)
		{
		case 1:
			Setexp(20);
			SetEATK(40);
			SetHP(50);
			SetGold(530);
			break;
		case 2:
			Setexp(50);
			SetEATK(60);
			SetHP(100);
			SetGold(80);
			break;
		case 3:
			Setexp(80);
			SetEATK(80);
			SetHP(120);
			SetGold(150);
		case 4:
			Setexp(100);
			SetEATK(100);
			SetHP(200);
			SetGold(200);
		}
	}
	char* GetenemyName()
	{
		return enemy;
	}

	bool Getenemyhit()
	{
		return enemyHit;
	}

	void Setenemyhit(bool flg)
	{
		enemyHit = flg;
	}

	int GetEnemyState()
	{
		return ste;
	}

	void SetEnemyState(int state)
	{
		ste = state;
	}

	int GetEHp()const
	{
		return HP;
	}

	void SetHP(int hp)
	{
		HP = hp;
	}


	int GetEATK()const
	{
		return EATK;
	}

	void SetEATK(int atk )
	{
		EATK = atk;
	}

	int GetExp()const
	{
		return Exp;
	}

	void Setexp(int exp)
	{
		Exp = exp;
	}

	int GetEGold()const
	{
		return EGold;
	}

	void SetGold(int gold)
	{
		EGold = gold;
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

	enum HIT
	{
		HIT,
		NO
	};


	int hit = NO;
	int ste = Alive;


	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[�B

	float           SearchRaeng = 5.0f;
	float           OutSearch = 5.0f;

	bool            over = false;

	CSkinModel		skinModel;
	CSkinModelData	skinModelData;

	CAnimation		Animation;
	CVector3		position = { -3.0f,0.0f,-30.0f };
	CVector3        BakPosition = { 0,0,0 };       //�����������Ɍ��̍��W�ɖ߂邽�߂̂��

	CQuaternion		m_rotation;

	CVector3        subvec;
	float           angle;

	CLight			Enemylight;

	char* enemy;
	bool enemyHit=false;

	CVector3 direction = CVector3::AxisZ;

	//�X�e
	int HP;
	int EATK;
	int Exp;
	int EGold;

};
extern Enemy* g_Enemy;

