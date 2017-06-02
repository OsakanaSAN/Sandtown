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

	int ste = Alive;


	CCharacterController	characterController;		//キャラクタ―コントローラー。

	float           SearchRaeng = 5.0f;
	float           OutSearch = 5.0f;

	bool            over = false;

	CSkinModel		skinModel;
	CSkinModelData	skinModelData;

	CAnimation		Animation;
	CVector3		position = { -3.0f,0.0f,-30.0f };
	CVector3        BakPosition = { 0,0,0 };       //見失った時に元の座標に戻るためのやつ

	CQuaternion		m_rotation;

	CVector3        subvec;
	float           angle;

	CLight			Enemylight;

	char* enemy;
	bool enemyHit=false;
	CVector3 direction = CVector3::AxisZ;
};
extern Enemy* g_Enemy;

