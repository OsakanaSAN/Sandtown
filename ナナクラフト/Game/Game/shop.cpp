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
	
	for (int i = 0; i < 3;i++) {

		m_GoldSeatTexture[i].Load("Assets/UI/0.png");
		m_GoldSeatSprite[i].SetPosition(m_Goldseatpos);
		m_GoldSeatSprite[i].Init(&m_GoldSeatTexture[i]);
		m_GoldSeatSprite[i].SetSize({ 80.0f,60.0f });

		m_GoldSeatTexture2[i].Load("Assets/UI/0.png");
		m_GoldSeatSprite2[i].SetPosition(m_Goldseatpos2);
		m_GoldSeatSprite2[i].Init(&m_GoldSeatTexture2[i]);
		m_GoldSeatSprite2[i].SetSize({ 80.0f,60.0f });
		m_Goldseatpos2.x += 80;
		m_Goldseatpos.x += 80;

	}

	for (int i = 0; i < 2;i++) {


		m_GoldSeatTexture3[i].Load("Assets/UI/riru.png");
		m_GoldSeatSprite3[i].SetPosition(m_Goldseatpos3);
		m_GoldSeatSprite3[i].Init(&m_GoldSeatTexture3[i]);
		m_GoldSeatSprite3[i].SetSize({ 120.0f,100.0f });
		m_Goldseatpos3.y -= 120;
	}
	
}

shop::~shop()
{
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	m_ComandBGTexture1.Release();
	m_ComandBGTexture2.Release();
	m_ComandBGTexture3.Release();
	m_CasolBGTexture.Release();
}


void shop::Init(const char* modelName, CVector3 position, CQuaternion rotation)
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
	m_ComandBGSprite1.SetPosition({ -400,130 });
	m_ComandBGSprite1.SetSize({ 1000.0f,800.0f });
	
	m_ComandBGTexture2.Load("Assets/sprite/パワー.png");
	m_ComandBGSprite2.Init(&m_ComandBGTexture2);
	m_ComandBGSprite2.SetPosition({ -550,300 });
	m_ComandBGSprite2.SetSize({ 300.0f,80 });

	m_ComandBGTexture3.Load("Assets/sprite/パワー2.png");
	m_ComandBGSprite3.Init(&m_ComandBGTexture3);
	m_ComandBGSprite3.SetPosition({ -550,180 });
	m_ComandBGSprite3.SetSize({ 300.0f,100 });

	m_CasolBGTexture.Load("Assets/sprite/casol2.png");
	m_CasolBGSprite.Init(&m_CasolBGTexture);
	m_CasolBGSprite.SetPosition({ -800,300 });
	m_CasolBGSprite.SetSize({ 200,200 });

	GetGoldTex(nedan1);

	GetGoldTex2(nedan2);
}

void shop::Update()
{


	
	switch(weaponState)
	{
		
		case Weapon1:
		
		g_menu->MenuSceneStop();
		m_CasolBGSprite.SetPosition({ -800,300 });
		m_CasolBGSprite.SetSize({ 200,200 });

		weaponState = Weapon1;

		if (Pad(0).IsPress(enButtonUp))
		{
			weaponState = Weapon1;
		}
		else if (Pad(0).IsPress(enButtonDown))
		{

			weaponState = Weapon2;
		}

		if (g_Hud->GetGold() < nedan1) { break; }

		if (Pad(0).IsTrigger(enButtonA))
		{
			g_Hud->ATKUp(10);
			g_Hud->SubtractGold(nedan1);
			g_menu->GoldChangTex();
		}

		break;
		
		case Weapon2:
		
			g_menu->MenuSceneStop();
			m_CasolBGSprite.SetPosition({ -800,200 });
			m_CasolBGSprite.SetSize({ 200,200 });
			weaponState = Weapon2;

			if (Pad(0).IsTrigger(enButtonUp))
			{

				weaponState = Weapon1;
			}
			else if (Pad(0).IsTrigger(enButtonDown))
			{

				weaponState = Weapon2;
			}

			if (g_Hud->GetGold() < nedan2) { break; }

			if (Pad(0).IsTrigger(enButtonA))
			{

				g_Hud->ATKUp(30);
				g_Hud->SubtractGold(nedan2);
				g_menu->GoldChangTex();
			}

			break;
		
		default:
		break;
	}



	if (g_player != nullptr) {

		CVector3 Ppos = g_player->Getpos();
		CVector3 Vpos;

		Vpos.x = Ppos.x - Pointpos.x;
		Vpos.y = Ppos.y - Pointpos.y;
		Vpos.z = Ppos.z - Pointpos.z;
		float L = Vpos.Length();

		/*if (g_menu->GetSceneState()!=0)
		{
		return;
		}*/
		if (Pad(0).IsTrigger(enButtonB))
		{
			g_player->IsMoveSTART();
			weaponState = -1;
			//g_menu->MenuSceneItem();
			Shopflg = false;
		}
		if (L < 7.0f && Pad(0).IsTrigger(enButtonA))
		{
			Shopflg = true;
			weaponState = Weapon1;
			g_player->IsMoveSTOP();

		}
	}
}


void shop::Render(CRenderContext& renderContext)
{
	if(weaponState >= Weapon1)
	{
		m_ComandBGSprite1.Draw(renderContext);
		m_ComandBGSprite2.Draw(renderContext);
		m_ComandBGSprite3.Draw(renderContext);
		m_CasolBGSprite.Draw(renderContext);
		for (int i = 0;i < 3;i++) {
			m_GoldSeatSprite[i].Draw(renderContext);
			m_GoldSeatSprite2[i].Draw(renderContext);
			
		}

		for (int i = 0;i < 2;i++)
		{
			m_GoldSeatSprite3[i].Draw(renderContext);
		}
	}
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}


void shop::GetGoldTex(int GetGold)
{
	int NextGold[3];

	NextGold[0] = GetGold / 100;

	sprintf(m_GoldTexName, "Assets/UI/%d.png", NextGold[0]);
	m_GoldSeatTexture[0].Release();
	m_GoldSeatTexture[0].Load(m_GoldTexName);

	GetGold %= 100;

	NextGold[1] = GetGold / 10;

	sprintf(m_GoldTexName, "Assets/UI/%d.png", NextGold[1]);
	m_GoldSeatTexture[1].Release();
	m_GoldSeatTexture[1].Load(m_GoldTexName);

	GetGold %= 10;
	NextGold[2] = GetGold;

	sprintf(m_GoldTexName, "Assets/UI/%d.png",NextGold[2]);
	m_GoldSeatTexture[2].Release();
	m_GoldSeatTexture[2].Load(m_GoldTexName);

}


void shop::GetGoldTex2(int GetGold)
{

	int NextGold[3];

	NextGold[0] = GetGold / 100;

	sprintf(m_GoldTexName2, "Assets/UI/%d.png", NextGold[0]);
	m_GoldSeatTexture2[0].Release();
	m_GoldSeatTexture2[0].Load(m_GoldTexName2);

	GetGold %= 100;

	NextGold[1] = GetGold / 10;

	sprintf(m_GoldTexName2, "Assets/UI/%d.png", NextGold[1]);
	m_GoldSeatTexture2[1].Release();
	m_GoldSeatTexture2[1].Load(m_GoldTexName2);

	GetGold %= 10;
	NextGold[2] = GetGold;

	sprintf(m_GoldTexName2, "Assets/UI/%d.png", NextGold[2]);
	m_GoldSeatTexture2[2].Release();
	m_GoldSeatTexture2[2].Load(m_GoldTexName2);

}