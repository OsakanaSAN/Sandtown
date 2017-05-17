#include "stdafx.h"
#include "Mapchip.h"
#include "Camera.h"
#include "Scene/GameScene.h"
#include "Fade.h"
#include "GameSound.h"
#include "Player.h"

Mapchip::Mapchip()
{
	Maplight.SetAmbinetLight({ 0.5f, 0.5f, 0.5f }); //ライトの設定
	Lightpos = g_player->Getpos();
	Maplight.SetPointLightPosition(Lightpos);
	Maplight.SetPointLightColor({ 1.0f,1.0f,1.0f,1.0f });


	skinModel.SetShadowReceiverFlag(true);//レシーバーが影が落とされるほう
	skinModel.SetShadowCasterFlag(true);


	Maplight.SetDiffuseLightDirection(0, { -1.0f,-1.0f,-1.0f });//ディフューズのカラーとディレクションを設定影が落とされるほう
	Maplight.SetDiffuseLightColor(0, { 0.3f, 0.3f, 0.3f, 0.5f });//ディフューズのカラー
	
}


Mapchip::~Mapchip()
{
	PhysicsWorld().RemoveRigidBody(&rigidBody);

}

void Mapchip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
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

void Mapchip::Update()
{
	//初期化の時に作成しているので何もしない。
	if (g_player != NULL)
	{
		Maplight.SetPointLightPosition(g_player->Getpos());
	}

	

}
void Mapchip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}
void Mapchip::SoundOnMachi()
{
	g_sound->MachiSound();
}
void Mapchip::SoundOnDoukutu()
{
	g_sound->DoukutuSound();
}

