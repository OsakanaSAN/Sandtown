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


	CSkinModel		skinModel;
	CSkinModelData	skinModelData;

	CAnimation		Animation;
	CVector3		position = { -20.0f,0.0f,0.0f };
	CQuaternion		m_rotation;

	CLight			All;
};
extern Enemy* g_Enemy;

