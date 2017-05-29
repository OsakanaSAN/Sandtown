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

	CSkinModel				skinModel;					//�X�L�����f���B
	CSkinModelDataHandle	skinModelData;				//�X�L�����f���f�[�^�B
	CAnimation              Animation;
	CCharacterController	characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				position = { -4.79f, 0.01f, 10.68f };                //���W�B
	CLight                  Npclight;
	CQuaternion				m_rotion;
	bool                    IsStand = false;
	bool                    IsWalk = false;

};

