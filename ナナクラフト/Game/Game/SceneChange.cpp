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

	m_ComandBGTexture1.Release();
	m_ComandBGTexture2.Release();
	m_ComandBGTexture3.Release();
	m_ComandBGTexture4.Release();
	m_CasolBGTexture.Release();
}

bool SceneChange::Start()
{
	ButtonTexture.Load("Assets/UI/Abutton.png");
	ButtonSprite.Init(&ButtonTexture);
	ButtonSprite.SetPosition(ButtonPos);
	ButtonSprite.SetSize({ 70.0, 70.0 });

	m_ComandBGTexture1.Load("Assets/UI/ui1.png");
	m_ComandBGSprite1.Init(&m_ComandBGTexture1);
	m_ComandBGSprite1.SetPosition({ -500,0 });
	m_ComandBGSprite1.SetSize({ 750.0f,1000.0f });

	m_ComandBGTexture2.Load("Assets/sprite/dungeon1.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -550,350 });
	m_ComandBGSprite2.SetSize({ 280.0f,80 });

	m_ComandBGTexture3.Load("Assets/sprite/dungeon2.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -550,250 });
	m_ComandBGSprite3.SetSize({ 280.0f,80 });

	m_ComandBGTexture4.Load("Assets/sprite/dungeon3.png");
	m_ComandBGSprite4.Init(&m_ComandBGTexture4);
	m_ComandBGSprite4.SetPosition({ -550,150 });
	m_ComandBGSprite4.SetSize({ 280.0f,80 });

	m_ComandBGTexture5.Load("Assets/sprite/dungeon1.png");
	m_ComandBGSprite5.Init(&m_ComandBGTexture5);
	m_ComandBGSprite5.SetPosition({ -550,50 });
	m_ComandBGSprite5.SetSize({ 280.0f,80 });

	m_ComandBGTexture6.Load("Assets/sprite/dungeon1.png");
	m_ComandBGSprite6.Init(&m_ComandBGTexture6);
	m_ComandBGSprite6.SetPosition({ -550,-50 });
	m_ComandBGSprite6.SetSize({ 280.0f,80 });

	m_ComandBGTexture7.Load("Assets/sprite/dungeon1.png");
	m_ComandBGSprite7.Init(&m_ComandBGTexture7);
	m_ComandBGSprite7.SetPosition({ -550,-150 });
	m_ComandBGSprite7.SetSize({ 280.0f,80 });

	m_ComandBGTexture8.Load("Assets/sprite/dungeon1.png");
	m_ComandBGSprite8.Init(&m_ComandBGTexture8);
	m_ComandBGSprite8.SetPosition({ -550,-250 });
	m_ComandBGSprite8.SetSize({ 280.0f,80 });

	m_CasolBGTexture.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite.Init(&m_CasolBGTexture);
	m_CasolBGSprite.SetPosition({ -800,350 });
	m_CasolBGSprite.SetSize({ 150,150 });

	return true;
}

void SceneChange::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{

	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	skinModel.Init(skinModelData.GetBody());
	//デフォルトライトを設定して
	skinModel.SetLight(&Maplight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
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

		/*if(g_player->Stop())
		{
			Cahange = false;
			return;
		}*/
		if (L < 3.0f)
		{
			if (!
				
				Cahange) {
				RendButton = true;
			}
			//Cahange = true;
			if (Pad(0).IsTrigger(enButtonA) && !Cahange)
			{
				if (Out && !Cahange)
				{
					g_gameScene->MapChange();
					Cahange = true;
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
			RendButton = false;
		}
	}
	

	if (g_player != nullptr&&MapSelectflg)
	{
		g_gameCamera->ChangeStop();
		g_player->IsMoveSTOP();
	}
}

///////////////////////////////////
//描画
void SceneChange::Render(CRenderContext& renderContext)
{
	if (Norend == false){
		skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
	}
	if (RendButton)
	{
		ButtonSprite.Draw(renderContext);
	}
	if (!MapSelectflg) { return;}
	if (Out) { return; }
	m_ComandBGSprite1.Draw(renderContext);
	m_ComandBGSprite2.Draw(renderContext);
	m_ComandBGSprite3.Draw(renderContext);
	m_ComandBGSprite4.Draw(renderContext);
	m_ComandBGSprite5.Draw(renderContext);
	m_ComandBGSprite6.Draw(renderContext);
	m_ComandBGSprite7.Draw(renderContext);
	m_ComandBGSprite8.Draw(renderContext);
	m_CasolBGSprite.Draw(renderContext);
}


//////////////////////////////////////
//マップの分岐処理
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
			DungeonNo = DungeonF7;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = DungeonF2;
		}


		if (Pad(0).IsTrigger(enButtonA) && !Cahange)
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->SetMaptype(DungeonNo);//ゲームシーンにマップ番号を渡す
			g_gameScene->MapChange();
			MapSelectflg = false;
			Cahange = true;
		}
		break;

	case DungeonF2:

		m_CasolBGSprite.SetPosition({ -800,250 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{

			DungeonNo = Dungeon;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{

			DungeonNo = DungeonF3;
		}

		if (Pad(0).IsTrigger(enButtonA) && !Cahange)
		{
			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->SetMaptype(DungeonNo);//ゲームシーンにマップ番号を渡す
			g_gameScene->MapChange();
			MapSelectflg = false;
			Cahange = true;
		}
		break;
	case DungeonF3:

		m_CasolBGSprite.SetPosition({ -800,150 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			DungeonNo = DungeonF2;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = DungeonF4;
		}

		if (Pad(0).IsTrigger(enButtonA) && !Cahange)
		{

			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->SetMaptype(DungeonNo);//ゲームシーンにマップ番号を渡す
			g_gameScene->MapChange();
			MapSelectflg = false;
			Cahange = true;
		}
		break;
	case DungeonF4:

		m_CasolBGSprite.SetPosition({ -800,50 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			DungeonNo = DungeonF3;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = DungeonF5;
		}

		if (Pad(0).IsTrigger(enButtonA) && !Cahange)
		{

			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->SetMaptype(DungeonNo);//ゲームシーンにマップ番号を渡す
			g_gameScene->MapChange();
			MapSelectflg = false;
			Cahange = true;
		}
		break;
	case DungeonF5:

		m_CasolBGSprite.SetPosition({ -800,-50 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			DungeonNo = DungeonF4;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = DungeonF6;
		}

		if (Pad(0).IsTrigger(enButtonA) && !Cahange)
		{

			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->SetMaptype(DungeonNo);//ゲームシーンにマップ番号を渡す
			g_gameScene->MapChange();
			MapSelectflg = false;
			Cahange = true;
		}
		break;
	case DungeonF6:

		m_CasolBGSprite.SetPosition({ -800,-150 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			DungeonNo = DungeonF5;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = DungeonF7;
		}

		if (Pad(0).IsTrigger(enButtonA) && !Cahange)
		{

			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->SetMaptype(DungeonNo);//ゲームシーンにマップ番号を渡す
			g_gameScene->MapChange();
			MapSelectflg = false;
			Cahange = true;
		}
		break;
	case DungeonF7:

		m_CasolBGSprite.SetPosition({ -800,-250 });
		m_CasolBGSprite.SetSize({ 150,150 });

		if (Pad(0).IsTrigger(enButtonUp))
		{
			DungeonNo = DungeonF6;
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			DungeonNo = Dungeon;
		}

		if (Pad(0).IsTrigger(enButtonA) && !Cahange)
		{

			m_sound_select = NewGO<CSoundSource>(0);
			m_sound_select->Init("Assets/sound/select3.wav");
			m_sound_select->Play(false);
			m_sound_select->SetVolume(4.0f);

			g_gameScene->SetMaptype(DungeonNo);//ゲームシーンにマップ番号を渡す
			g_gameScene->MapChange();
			MapSelectflg = false;
			Cahange = true;
		}
		break;
	default:
		//g_menu->MenuSceneStop();
		//MapSelectflg = false;
		break;

	}
}

