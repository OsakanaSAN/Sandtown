#include "stdafx.h"
#include "GameSky.h"
#include "Camera.h"


GameSky::GameSky()
{
}


GameSky::~GameSky()
{
}

bool GameSky::Start()
{
	return true;
}

void GameSky::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	Skypos = position;
	SkyRot = rotation;
	Maplight.SetAmbinetLight({ 1.2f, 1.2f, 1.2f });
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f���f�[�^�����[�h�Bww
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModel���������B
	skinModel.Init(skinModelData.GetBody());
	//�f�t�H���g���C�g��ݒ肵�āB
	skinModel.SetLight(&Maplight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	//���[���h�s����X�V����B
	//���̃I�u�W�F�N�g�͓����Ȃ��̂ŁA�������ň�񂾂����[���h�s����쐬����΂����B
	skinModel.Update(Skypos, SkyRot, CVector3::One);

}
void GameSky::Update()
{

	rot_y += 0.02f;
	if (rot_y == 360)
	{
		rot_y = 0;
	}

	SkyRot.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(rot_y));

	skinModel.Update(Skypos, SkyRot, CVector3::One);

}

void GameSky::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}