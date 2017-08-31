#pragma once
#include "tkEngine/character/tkCharacterController.h"

class Npc : public IGameObject
{
public:
	Npc();
	~Npc();
	bool Start()override;
	void Update()override;
	void Render(CRenderContext& renderContext);
private:

	CSkinModel				skinModel;					//スキンモデル。
	CSkinModelDataHandle	skinModelData;				//スキンモデルデータ。
	CAnimation              Animation;
	CCharacterController	characterController;		//キャラクタ―コントローラー。
	CVector3				position = { -4.79f, 0.01f, 10.68f };                //座標。
	CLight                  Npclight;
	CQuaternion				m_rotion;
	bool                    IsStand = false;
	bool                    IsWalk = false;

};

