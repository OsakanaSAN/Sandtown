#include "stdafx.h"
#include "Torch.h"
#include "Scene/GameScene.h"
#include "Camera.h"


extern Camera* g_gameCamera;



Torch::Torch() 
{

	Maplight.SetPointLightColor({ 20.0f,10.0f,1.0f,1.0f });
	Maplight.SetAmbinetLight({ 1.0f,1.0f,1.0f });
}


Torch::~Torch()
{
	PhysicsWorld().RemoveRigidBody(&rigidBody);
}

void Torch::Init(const char* modelName, CVector3 position, CQuaternion rotation)
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
	skinModel.Init(&skinModelData);
	//デフォルトライトを設定して。
	skinModel.SetLight(&Maplight);
	//skinModel.SetShadowCasterFlag(true);
	//skinModel.SetShadowReceiverFlag(true);
	//ワールド行列を更新する。
	//このオブジェクトは動かないので、初期化で一回だけワールド行列を作成すればおｋ。
	skinModel.Update(position, rotation, CVector3::One);

	//メッシュコライダーの作成。
	meshCollider.CreateFromSkinModel(&skinModel, skinModelData.GetRootBoneWorldMatrix());

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

void Torch::Update()
{
	

}

void Torch::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}