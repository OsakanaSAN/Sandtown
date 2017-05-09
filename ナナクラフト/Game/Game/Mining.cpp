#include "stdafx.h"
#include "Mining.h"
#include "Scene/GameScene.h"
#include "Camera.h"
#include "HUD.h"
#include "Player.h"
#include "Map2.h"


extern Camera* g_gameCamera;
extern HUD*    g_Hud;
extern Player* g_player;
extern Map2*   g_map2;



Mining::Mining()
{

	//Maplight.SetPointLightColor({ 20.0f,10.0f,1.0f,1.0f });
	Maplight.SetAmbinetLight({ 1.0f,1.0f,1.0f });
	
}


Mining::~Mining()
{
	PhysicsWorld().RemoveRigidBody(&rigidBody);

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
		if (L < 2.0f && GetAsyncKeyState('E')&0x8000)
		{
			g_Hud->SetTex();
			//DeleteGO(this);
			g_map2->AsDete(asnumber);
		}
	}

}

void Mining::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}