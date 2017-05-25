#include "stdafx.h"
#include "Scene/TitleScene.h"
#include "Scene\GameScene.h"
#include "Fade.h"
#include "Camera.h"
#include "Player.h"
#include "Menu.h"
#include "BattleMenu.h"



Fade*   g_fade = nullptr;
CRandom g_random;



/*!
 * @brief	tkEngineの初期化。
 */
void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//コマンドバッファのサイズのテーブル。
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//レンダリングコンテキストは一本
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	initParam.frameBufferHeight = 1080;
	initParam.frameBufferWidth = 1920;

	//Bloom
	initParam.graphicsConfig.bloomConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.Init();
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfig.shadowRenderConfig.numShadowMap = 3;
	initParam.graphicsConfig.shadowRenderConfig.isDisableSoftShadow = true;
	
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = false;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;

	

	//DOF
	initParam.graphicsConfig.dofConfig.isEnable = false;
	//AA
	initParam.graphicsConfig.aaConfig.isEnable = true;
	//乱数初期化。
	g_random.Init((unsigned long)time(NULL));


	Engine().Init(initParam);	//初期化。
	
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(40.0f);
	
}
//class CMemoryLeakTest : public IGameObject{
//public:
//	bool Start()
//	{
//		return true;
//	}
//	void Update() {
//		CSkinModelDataHandle modelData;
//		CSkinModel model;
//		modelData.LoadModelData("Assets/modelData/Unity.X", NULL);
//		model.Init(modelData.GetBody());
//		SkinModelDataResources().Release();
//	}
//	
//};

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	//tkEngineの初期化。
	InitTkEngine( hInst );
	

	g_fade = NewGO<Fade>(1);

	////タイトルシーンの作成。

	NewGO<TitleScene>(0);
	//NewGO<BattleMenu>(0);

	//NewGO<TitleScene>(0);


	//NewGO<Menu>(0);

	//NewGO<BattleMenu>(0);


	
	Engine().RunGameLoop();		//ゲームループを実行。

	return 0;
}