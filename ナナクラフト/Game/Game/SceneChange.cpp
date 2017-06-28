#include "stdafx.h"
#include "SceneChange.h"
#include "Player.h"
#include "Scene\GameScene.h"
#include "Fade.h"
#include "Camera.h"
#include "Menu.h"
#include "Dungeon.h"

SceneChange::SceneChange()
{
	
	Maplight.SetAmbinetLight({ 1.0f,1.0f,1.0f });
}


SceneChange::~SceneChange()
{
	
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();

}

bool SceneChange::Start()
{
	ButtonTexture.Load("Assets/UI/Abutton.png");
	ButtonSprite.Init(&ButtonTexture);
	ButtonSprite.SetPosition(ButtonPos);
	ButtonSprite.SetSize({ 70.0, 70.0 });

	m_ComandBGTexture1.Load("Assets/sprite/comand.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ -500,150 });
	m_ComandBGSprite1.SetSize({ 800.0f,650.0f });

	m_ComandBGTexture2.Load("Assets/sprite/�p���[2.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -550,350 });
	m_ComandBGSprite2.SetSize({ 250.0f,80 });

	m_ComandBGTexture3.Load("Assets/sprite/�p���[2.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -550,230 });
	m_ComandBGSprite3.SetSize({ 250.0f,80 });

	m_ComandBGTexture4.Load("Assets/sprite/�p���[2.png");
	m_ComandBGSprite4.Init(&m_ComandBGTexture4);
	m_ComandBGSprite4.SetPosition({ -550,100 });
	m_ComandBGSprite4.SetSize({ 250.0f,80 });

	//m_ComandBGTexture5.Load("Assets/sprite/�p���[2.png");
	//m_ComandBGSprite5.Init(&m_ComandBGTexture5);
	//m_ComandBGSprite5.SetPosition({ -550,0 });
	//m_ComandBGSprite5.SetSize({ 250.0f,80 });

	//m_ComandBGTexture6.Load("Assets/sprite/�p���[2.png");
	//m_ComandBGSprite6.Init(&m_ComandBGTexture5);
	//m_ComandBGSprite6.SetPosition({ -550,-100 });
	//m_ComandBGSprite6.SetSize({ 250.0f,80 });

	//m_ComandBGTexture7.Load("Assets/sprite/�p���[2.png");
	//m_ComandBGSprite7.Init(&m_ComandBGTexture5);
	//m_ComandBGSprite7.SetPosition({ -550,-200 });
	//m_ComandBGSprite7.SetSize({ 250.0f,80 });

	m_CasolBGTexture.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite.Init(&m_CasolBGTexture);
	m_CasolBGSprite.SetPosition({ -800,350 });
	m_CasolBGSprite.SetSize({ 150,150 });

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
	//�f�t�H���g���C�g��ݒ肵��
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

void SceneChange::Update()
{
	
	if (g_player != nullptr) {
		
		if (MapSelectflg)
		{
			MapSelect();
		}
		CVector3 Ppos = g_player->Getpos();
		CVector3 Vpos;

		Vpos.x = Ppos.x - SCpos.x;
		Vpos.y = Ppos.y - SCpos.y;
		Vpos.z = Ppos.z - SCpos.z;
		float L = Vpos.Length();

		if(g_player->Stop())
		{
			Cahange = false;
			return;
		}
		if (L < 3.0f)
		{
			Cahange = true;
			if (Pad(0).IsTrigger(enButtonA))
			{
				if (Out)
				{
					g_gameScene->MapChange();
				}
				MapSelectflg = true;

			}
			if (Pad(0).IsTrigger(enButtonB))
			{
				g_menu->MenuSceneStop();
				MapSelectflg = false;
			}
		}
		else
		{
			MapSelectflg = false;
			Cahange = false;
		}
	}

	if (g_player != nullptr&&MapSelectflg)
	{
		g_player->IsMoveSTOP();
	}
}
void SceneChange::Render(CRenderContext& renderContext)
{
	if (Norend == false){
		skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
	}
	if (Cahange)
	{
		ButtonSprite.Draw(renderContext);
	}
	if (!MapSelectflg) { return;}
	if (Out) { return; }
	m_ComandBGSprite1.Draw(renderContext);
	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);
	m_ComandBGSprite4.Draw(renderContext);
	m_CasolBGSprite.Draw(renderContext);
}

void SceneChange::MapSelect()
{
	g_menu->MenuSceneexit();
	switch (DungeonNo)
	{
	case Dungeon:

		m_CasolBGSprite.SetPosition({ -800,350 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			DungeonNo = DungeonF3;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = DungeonF2;
		}

		
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->MapChange();
			MapSelectflg = false;

		}
		break;

	case DungeonF2:

		m_CasolBGSprite.SetPosition({ -800,230 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{

			DungeonNo = Dungeon;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{

			DungeonNo = DungeonF3;
		}

		if (Pad(0).IsTrigger(enButtonA))
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->MapChange();
			MapSelectflg = false;

		}
		break;
	case DungeonF3:

		m_CasolBGSprite.SetPosition({ -800,100 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			DungeonNo = DungeonF2;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = Dungeon;
		}

		if (Pad(0).IsTrigger(enButtonA))
		{

			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->MapChange();
			MapSelectflg = false;
		}
		break;
	default:
		//g_menu->MenuSceneStop();
		//MapSelectflg = false;
		break;

	}
}

