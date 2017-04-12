#include "stdafx.h"
#include "Mapchip.h"
#include "Camera.h"

extern Camera* g_gameCamera;

Mapchip::Mapchip()
{
	//Maplight.SetAmbinetLight({ 0.01f, 0.01f, 0.01f }); //ライトの設定
	//Maplight.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	Maplight.SetAmbinetLight(CVector3::One);
	Maplight.SetEmissionLightColor({ 1.0f,1.0f,1.0f });
}


Mapchip::~Mapchip()
{
}

void Mapchip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
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

void Mapchip::Update()
{
	//初期化の時に作成しているので何もしない。
}
void Mapchip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

