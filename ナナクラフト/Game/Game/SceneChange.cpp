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

