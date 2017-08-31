#include "stdafx.h"
#include "Npc.h"
#include "Camera.h"


enum {

	Stand_anim,
	Walk_anim,
	Run_anim,
	Jump_anim,

};


Npc::Npc()
{
	Npclight.SetAmbinetLight({ 1.5f,1.0f,1.0f });
}


Npc::~Npc()
{
}


bool Npc::Start()
{

	skinModelData.LoadModelData("Assets/modelData/Unity.X", &Animation);
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&Npclight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);


	m_rotion.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(0.0f));
	Animation.PlayAnimation(Stand_anim, 0.1f);
	
	


	//�L�����N�^�R���g���[���̏������B
	characterController.Init(0.5f, 1.0f, position);


	return true;
}



void Npc::Update()
{

	
	if (!IsStand)
	{
		
		Animation.PlayAnimation(Stand_anim, 0.05f);
		Animation.SetAnimationSpeedRate(1);
		IsStand = true;

	}




	//�A�j���[�V�����̍X�V
	Animation.Update(1.0f / 60.0f);
	characterController.Execute(0.03f);
	//���[���h�s��̍X�V�B
	skinModel.Update(position, m_rotion, CVector3::One);
	

}

void Npc::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}