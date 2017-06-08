#include "stdafx.h"
#include "shop.h"
#include "Scene/GameScene.h"
#include "Camera.h"
#include "HUD.h"
#include "Player.h"
#include "BattlePlayer.h"
#include "Map2.h"
#include "Menu.h"



shop::shop()
{
	Maplight.SetAmbinetLight({ 0.6f,0.6f,0.6f });
	
}

shop::~shop()
{
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	m_ComandBGTexture1.Release();
	m_ComandBGTexture2.Release();
	m_ComandBGTexture3.Release();
	m_CasolBGTexture5.Release();
}


void shop::Init(const char* modelName, CVector3 position, CQuaternion rotation)
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
	
	m_ComandBGTexture1.Load("Assets/sprite/comand.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ -500,130 });
	m_ComandBGSprite1.SetSize({ 800.0f,800.0f });
	
	m_ComandBGTexture2.Load("Assets/sprite/kougeki.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -600,300 });
	m_ComandBGSprite2.SetSize({ 150.0f,50 });

	m_ComandBGTexture3.Load("Assets/sprite/nigeru.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -600,200 });
	m_ComandBGSprite3.SetSize({ 150.0f,50 });

	m_CasolBGTexture5.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite5.Init(&m_CasolBGTexture5);
	m_CasolBGSprite5.SetPosition({ -800,200 });
	m_CasolBGSprite5.SetSize({ 200,200 });
}

void shop::Update()
{
	if (g_player != nullptr) {

		CVector3 Ppos = g_player->Getpos();
		CVector3 Vpos;

		Vpos.x = Ppos.x - Pointpos.x;
		Vpos.y = Ppos.y - Pointpos.y;
		Vpos.z = Ppos.z - Pointpos.z;
		float L = Vpos.Length();


		if (Pad(0).IsPress(enButtonB))
		{
			g_player->IsMoveSTART();
			state = A;
			shopflg = false;
		}
		if (L < 7.0f && Pad(0).IsPress(enButtonA))
		{
			state = C;
			g_player->IsMoveSTOP();
			shopflg = true;

		}
	}
	if (shopflg) {
		if (Pad(0).IsPress(enButtonUp))
		{
			
			m_CasolBGSprite5.SetPosition({ -800,200 });
			m_CasolBGSprite5.SetSize({ 200,200 });
			
			state = C;
		}
		else if (Pad(0).IsPress(enButtonDown))
		{
			
			m_CasolBGSprite5.SetPosition({ -800,300 });
			m_CasolBGSprite5.SetSize({ 200,200 });
			
			state = D;
		}
	}

		switch (state)
		{
		case C:
			if (g_Hud->GetGold() < 100) { return; }
			if (Pad(0).IsPress(enButtonA))
			{
				
				g_Hud->SetATK(g_Hud->GetATK() + 20);
				g_Hud->Shiharai(100);
				g_menu->GoldChangTex();
			}
			break;
		case D:
			if (g_Hud->GetGold() < 300) { return; }
			if (Pad(0).IsPress(enButtonA))
			{
				
				g_Hud->SetATK(g_Hud->GetATK() + 50);
				g_Hud->Shiharai(300);
				g_menu->GoldChangTex();
			}
			break;

		}
	
	
}

void shop::Render(CRenderContext& renderContext)
{
	if(state == C|| state == D)
	{
		m_ComandBGSprite1.Draw(renderContext);
		m_ComandBGSprite2.Draw(renderContext);
		m_ComandBGSprite3.Draw(renderContext);
		m_CasolBGSprite5.Draw(renderContext);
	}
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}