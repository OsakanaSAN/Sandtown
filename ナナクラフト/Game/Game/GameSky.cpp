#include "stdafx.h"
#include "GameSky.h"
#include "Camera.h"


GameSky::GameSky()
{
}


GameSky::~GameSky()
{
}

bool GameSky::Start()
{
	return true;
}

void GameSky::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	Skypos = position;
	SkyRot = rotation;
	Maplight.SetAmbinetLight({ 1.2f, 1.2f, 1.2f });
	//ファイルパスを作成する。
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルデータをロード。ww
	skinModelData.LoadModelData(filePath, NULL);
	//CSkinModelを初期化。
	skinModel.Init(skinModelData.GetBody());
	//デフォルトライトを設定して。
	skinModel.SetLight(&Maplight);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	//ワールド行列を更新する。
	//このオブジェクトは動かないので、初期化で一回だけワールド行列を作成すればおｋ。
	skinModel.Update(Skypos, SkyRot, CVector3::One);

}
void GameSky::Update()
{

	rot_y += 0.02f;
	if (rot_y == 360)
	{
		rot_y = 0;
	}

	SkyRot.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(rot_y));

	skinModel.Update(Skypos, SkyRot, CVector3::One);

}

void GameSky::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}