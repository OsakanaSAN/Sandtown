#include "stdafx.h"
#include "Mapchip.h"
#include "Camera.h"
#include "Scene/GameScene.h"
#include "Fade.h"
#include "GameSound.h"
#include "Player.h"

Mapchip::Mapchip()
{
	Maplight.SetAmbinetLight({ 0.5f, 0.5f, 0.5f }); //���C�g�̐ݒ�
	Lightpos = g_player->Getpos();
	Maplight.SetPointLightPosition(Lightpos);
	Maplight.SetPointLightColor({ 1.0f,1.0f,1.0f,1.0f });


	skinModel.SetShadowReceiverFlag(true);//���V�[�o�[���e�����Ƃ����ق�
	skinModel.SetShadowCasterFlag(true);


	Maplight.SetDiffuseLightDirection(0, { -1.0f,-1.0f,-1.0f });//�f�B�t���[�Y�̃J���[�ƃf�B���N�V������ݒ�e�����Ƃ����ق�
	Maplight.SetDiffuseLightColor(0, { 0.3f, 0.3f, 0.3f, 0.5f });//�f�B�t���[�Y�̃J���[
	
}


Mapchip::~Mapchip()
{
	PhysicsWorld().RemoveRigidBody(&rigidBody);

}

void Mapchip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f���f�[�^�����[�h�B
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModel���������B
	skinModel.Init(skinModelData.GetBody());
	//�f�t�H���g���C�g��ݒ肵�āB
	skinModel.SetLight(&Maplight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	//���[���h�s����X�V����B
	//���̃I�u�W�F�N�g�͓����Ȃ��̂ŁA�������ň�񂾂����[���h�s����쐬����΂����B
	skinModel.Update(position, rotation, CVector3::One);

	//���b�V���R���C�_�[�̍쐬�B
	meshCollider.CreateFromSkinModel(&skinModel, skinModelData.GetBody()->GetRootBoneWorldMatrix());

	//���̂̍쐬�B
	RigidBodyInfo rbInfo;
	//���̂̃R���C�_�[��n���B
	rbInfo.collider = &meshCollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&rigidBody);

	
	
}

void Mapchip::Update()
{
	//�������̎��ɍ쐬���Ă���̂ŉ������Ȃ��B
	if (g_player != NULL)
	{
		Maplight.SetPointLightPosition(g_player->Getpos());
	}

	

}
void Mapchip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}
void Mapchip::SoundOnMachi()
{
	g_sound->MachiSound();
}
void Mapchip::SoundOnDoukutu()
{
	g_sound->DoukutuSound();
}

