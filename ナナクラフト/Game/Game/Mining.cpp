#include "stdafx.h"
#include "Mining.h"
#include "Scene/GameScene.h"
#include "Camera.h"
#include "HUD.h"
#include "Player.h"
#include "Menu.h"

extern CRandom g_random;

Mining::Mining()
{

	Maplight.SetAmbinetLight({ 0.8f,0.8f,0.8f });
	
}


Mining::~Mining()
{
	
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	
	//IconSeatTexture.Release();
}

void Mining::Init(const char* modelName, CVector3 position, CQuaternion rotation)
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

	ButtonTexture.Load("Assets/UI/Xbutton.png");
	ButtonSprite.Init(&ButtonTexture);
	ButtonSprite.SetPosition(ButtonPos);
	ButtonSprite.SetSize({ 70.0, 70.0 });


}


void Mining::Update()
{

	if (g_player != nullptr) {

		CVector3 Ppos = g_player->Getpos();
		CVector3 Vpos;

		Vpos.x = Ppos.x - Pointpos.x;
		Vpos.y = Ppos.y - Pointpos.y;
		Vpos.z = Ppos.z - Pointpos.z;
		float L = Vpos.Length();
		if (g_player->Stop())
		{
			minigs = false;
			return;
		}
		if (L < 2.0f && minigcount < 3) {
			minigs = true;

			if (Pad(0).IsTrigger(enButtonX) && S_timer == 0 && m_timer == 0)
			{
				minigs = false;
				if (ItemRender == NoGet) {
					ItemRender = Get;
					m_sound_bgm_battle = NewGO<CSoundSource>(0);
					m_sound_bgm_battle->Init("Assets/sound/select.wav");
					m_sound_bgm_battle->Play(false);
					m_sound_bgm_battle->SetVolume(7.0f);

					IconSeatTexture.Load("Assets/Item/Item4.png");
					IconSeatSprite.Init(&IconSeatTexture);
					IconSeatSprite.SetPosition(Iconseatpos);
					IconSeatSprite.SetSize({ 100.f,100.0f });
					IconSeatSprite.SetAlpha(1.0f);

					
				}


			}

		}
		else
		{
			minigs = false;
		}


		if (ItemRender == Get)
		{
			minigs = false;
			S_timer += GameTime().GetFrameDeltaTime();

		}

		if (S_timer > 0.5)
		{
			m_timer += GameTime().GetFrameDeltaTime();

			if (m_timer < FADE_TIME_ITEM)
			{
				minigs = false;
				float t = m_timer / FADE_TIME_ITEM;
				IconSeatSprite.SetAlpha(max(1.0f - t, 0.0f));
			}

			else if (m_timer > 0.5f) {
				minigs = false;
				g_menu->InventoryChangTex(4);
				minigcount++;
				m_timer = 0.0f;
				S_timer = 0;
				ItemRender = NoGet;

			}
		}

	}

}

void Mining::Render(CRenderContext& renderContext)
{

	
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
	if (minigs)
	{
		ButtonSprite.Draw(renderContext);
	}

	if (ItemRender == Get)
	{
		IconSeatSprite.Draw(renderContext);
	}
}