#include "stdafx.h"
#include "SceneChange.h"
#include "Player.h"
#include "Scene\GameScene.h"
#include "Fade.h"
#include "Camera.h"


SceneChange::SceneChange()
{
	
	Maplight.SetAmbinetLight({ 1.0f,1.0f,1.0f });
}


SceneChange::~SceneChange()
{
	PhysicsWorld().RemoveRigidBody(&rigidBody);
}

bool SceneChange::Start()
{
	
	
	return true;
}

void SceneChange::Init(const char* modelName, CVector3 position, CQuaternion rotation)
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
	//skinModel.SetShadowCasterFlag(true);
	//skinModel.SetShadowReceiverFlag(true);
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

	//g_fade->StartFadeIn();

}

void SceneChange::Update()
{
	if (g_player != nullptr) {
		CVector3 Ppos = g_player->Getpos();
		CVector3 Vpos;

		Vpos.x = Ppos.x - SCpos.x;
		Vpos.y = Ppos.y - SCpos.y;
		Vpos.z = Ppos.z - SCpos.z;
		float L = Vpos.Length();

		if (L < 3.0f && Pad(0).IsPress(enButtonA))
		{
			g_fade->StartFadeOut();
			g_gameScene->MapChange();
			
		}
	}


}
void SceneChange::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

