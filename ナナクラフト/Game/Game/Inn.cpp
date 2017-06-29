#include "stdafx.h"
#include "Inn.h"
#include "player.h"
#include "Menu.h"
#include "Fade.h"
#include "Hud.h"

Inn::Inn()
{
	Maplight.SetAmbinetLight({ 0.6f,0.6f,0.6f });

}

Inn::~Inn()
{

	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();

	m_CasolBGTexture.Release();
	m_ComandBGTexture1.Release();
	m_ComandBGTexture2.Release();
	m_ComandBGTexture3.Release();
	m_TextTexture.Release();
}

void Inn::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	Setpos(position);
	Pointpos = position;
	Maplight.SetPointLightPosition(LightPos2);

	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);

	//モデルデータをロード。
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	skinModel.Init(skinModelData.GetBody());
	//デフォルトライトを設定して。
	skinModel.SetLight(&Maplight);
	//skinModel.SetShadowCasterFlag(true);
	//skinModel.SetShadowReceiverFlag(true);
	//ワールド行列を更新する。
	//このオブジェクトは動かないので、初期化で一回だけワールド行列を作成すればおｋ。
	skinModel.Update(position, rotation, CVector3::One);

	//メッシュコライダーの作成。
	meshCollider.CreateFromSkinModel(&skinModel, skinModelData.GetBody()->GetRootBoneWorldMatrix());

	//剛体の作成。
	RigidBodyInfo rbInfo;
	//剛体のコライダーを渡す。
	rbInfo.collider = &meshCollider;
	//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加する。
	PhysicsWorld().AddRigidBody(&rigidBody);

	m_ComandBGTexture1.Load("Assets/sprite/comand.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ -400,-260 });
	m_ComandBGSprite1.SetSize({ 600.0f,350.0f });

	m_ComandBGTexture2.Load("Assets/sprite/hai.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -520,-250 });
	m_ComandBGSprite2.SetSize({ 100.0f,50 });

	m_ComandBGTexture3.Load("Assets/sprite/iie.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -500,-350 });
	m_ComandBGSprite3.SetSize({ 150.0f,50 });

	m_TextTexture.Load("Assets/sprite/Inn.png");
	m_TextSprite.Init(&m_TextTexture);
	m_TextSprite.SetPosition({ -450,-150 });
	m_TextSprite.SetSize({ 400.0f,80 });

	m_CasolBGTexture.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite.Init(&m_CasolBGTexture);
	m_CasolBGSprite.SetPosition({ -650,-350 });
	m_CasolBGSprite.SetSize({ 150,150 });
}

void Inn::Update()
{
	if (!g_fade->IsExecute())
	{
		g_fade->StartFadeIn();
		
		Fadeflg = false;
	}
	//else if (!Fadeflg&&Innflg)
	//{
	//	g_fade->StartFadeIn();
	//}

	if (g_player != nullptr) {

		if (Innflg) { InnSelect(); }

		CVector3 Ppos = g_player->Getpos();
		CVector3 Vpos;

		Vpos.x = Ppos.x - Pointpos.x;
		Vpos.y = Ppos.y - Pointpos.y;
		Vpos.z = Ppos.z - Pointpos.z;
		float L = Vpos.Length();

		if (Pad(0).IsTrigger(enButtonB)&&Innflg)
		{
			g_menu->MenuSceneStop();
			Innflg = false;
		}
		else if (L < 7.0f && Pad(0).IsTrigger(enButtonA))
		{
			Innflg = true;
			innstate = NOSREEP;
			g_player->IsMoveSTOP();

		}

	}

	if (g_player != nullptr&&Innflg)
	{
		g_player->IsMoveSTOP();
	}
}

void Inn::Render(CRenderContext& renderContext)
{

	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());

	if (!Innflg) { return; }
	m_ComandBGSprite1.Draw(renderContext);
	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);
	m_CasolBGSprite.Draw(renderContext);
	m_TextSprite.Draw(renderContext);
}

void Inn::InnSelect()
{
	switch (innstate)
	{
	g_menu->MenuSceneexit();
	case SREEP:
		m_CasolBGSprite.SetPosition({ -650,-250 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			innstate = SREEP;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			innstate = NOSREEP;
		}
		if (Pad(0).IsTrigger(enButtonA)&&!Fadeflg)
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_Hud->RecoveryHP(g_Hud->GetMaxHP());//全回復
			g_menu->setHP(g_Hud->GetHP());
			Fadeflg = true;
			g_fade->StartFadeOut();
			innstate = NOSREEP;
		}

		break;

	case NOSREEP:
		m_CasolBGSprite.SetPosition({ -650,-350 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			innstate = SREEP;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			innstate = NOSREEP;
		}

		if (Pad(0).IsTrigger(enButtonA))
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_menu->MenuSceneStop();
			Innflg = false;
		}

		break;

	default:
		break;
	}
}