#include "stdafx.h"
#include "Inn.h"
#include "player.h"
#include "Menu.h"


Inn::Inn()
{
	Maplight.SetAmbinetLight({ 0.6f,0.6f,0.6f });

}


Inn::~Inn()
{

	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();

	m_CasolBGTexture.Release();
}

void Inn::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	Setpos(position);
	Pointpos = position;
	Maplight.SetPointLightPosition(LightPos2);

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


	m_CasolBGTexture.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite.Init(&m_CasolBGTexture);
	m_CasolBGSprite.SetPosition({ -800,300 });
	m_CasolBGSprite.SetSize({ 200,200 });

	m_ComandBGTexture1.Load("Assets/sprite/comand.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ -400,130 });
	m_ComandBGSprite1.SetSize({ 1000.0f,800.0f });

}

void Inn::Update()
{
	if (Innflg) {

		InnSelect();
	}

	if (g_player != nullptr) {

		CVector3 Ppos = g_player->Getpos();
		CVector3 Vpos;

		Vpos.x = Ppos.x - Pointpos.x;
		Vpos.y = Ppos.y - Pointpos.y;
		Vpos.z = Ppos.z - Pointpos.z;
		float L = Vpos.Length();

		if (Pad(0).IsTrigger(enButtonB))
		{
			g_menu->MenuSceneStop();
			innstate = NOSREEP;
			Innflg = false;
		}
		if (L < 7.0f && Pad(0).IsTrigger(enButtonA))
		{
			Innflg = true;
			innstate = SREEP;
			g_player->IsMoveSTOP();

		}
	}

}


void Inn::Render(CRenderContext& renderContext)
{

	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

void Inn::InnSelect()
{
	switch (innstate)
	{

	case SREEP:

		g_menu->MenuSceneexit();
		m_CasolBGSprite.SetPosition({ -800,300 });
		m_CasolBGSprite.SetSize({ 200,200 });

		innstate = SREEP;

		if (Pad(0).IsPress(enButtonUp))
		{
			innstate = SREEP;
		}
		else if (Pad(0).IsPress(enButtonDown))
		{

			innstate = SREEP;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

		}

		break;

	case NOSREEP:

		g_menu->MenuSceneexit();
		m_CasolBGSprite.SetPosition({ -800,200 });
		m_CasolBGSprite.SetSize({ 200,200 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			innstate = SREEP;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{

			innstate = SREEP;
		}


		if (Pad(0).IsTrigger(enButtonA))
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

		}

		break;

	default:
		break;
	}
}