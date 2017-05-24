#pragma once

class GameSky :public IGameObject
{
public:
	GameSky();
	~GameSky();
	bool Start()override;
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

private:

	CLight               Maplight;
	CSkinModel			 skinModel;		//スキンモデル。
	CSkinModelDataHandle skinModelData;	//スキンモデルデータ
	CVector3             Skypos;
	CQuaternion          SkyRot;
	float                rot_y = 0;
};

