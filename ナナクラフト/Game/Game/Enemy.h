#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Enemy:public IGameObject
{
public :
	Enemy();
	~Enemy();
	bool Start()override;
	void Update();
	void Render(CRenderContext&renderContext);
	CVector3 getPos() {
		return position;
	}
	void Tracking();

private:

	enum ANIME {
		Stand_anim,
		Attack_anim,
		Damage_anim,
	};


	CCharacterController	characterController;		//キャラクタ―コントローラー。

	float           SearchRaeng = 8.0f;
	float           OutSearch = 8.0f;

	bool            over = false;

	CSkinModel		skinModel;
	CSkinModelData	skinModelData;

	CAnimation		Animation;
	CVector3		position = { -3.0f,1.0f,-30.0f };
	CQuaternion		m_rotation;

	CVector3        subvec;
	float           angle;

	CLight			Enemylight;
};
extern Enemy* g_Enemy;

