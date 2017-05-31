#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/character/tkCharacterController.h"



/*!
 *@brief	ゲームシーン。
 */
class GameScene : public IGameObject
{
public:
	
	GameScene();
	
	~GameScene();
	
	bool Start() override;
	
	void Update() override;
	
	void Render(CRenderContext& renderContext);

	void DeteScene();

	CLight& GetLite()
	{
		return light;
	}
	void SceneStop()
	{
		scenes = STOP;
	}
	void MapChange();
	//void BattleDate(); //バトル画面終了
	
	void Batoset(bool setBato)
	{
		Bato = setBato;
	}
	
	char* GetEnemy()
	{
		return modelName;
	}


private:
	

	char* modelName;

	enum set 
	{
		in,
		out,

	};
	set sets = in;

	CCamera camera;								//!<カメラ。
	CLight  light;								//!<ライト。
	CSoundSource* bgmSource;					//!<BGMソース。

	enum  MapScene
	{
		STOP,
		MACHI,
		DOUKUTU,
		Battle,
		MENU,
		Change,

	};
	

	MapScene      mapscene; //現在のマップがどこか判定
	MapScene         scenes; //遷移されたかの判定
	


	int        I, J;

	bool Bato = false; //バトル画面遷移判定
	




};

extern GameScene* g_gameScene;
