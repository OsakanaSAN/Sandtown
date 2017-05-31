#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/character/tkCharacterController.h"



/*!
 *@brief	�Q�[���V�[���B
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
	//void BattleDate(); //�o�g����ʏI��
	
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

	CCamera camera;								//!<�J�����B
	CLight  light;								//!<���C�g�B
	CSoundSource* bgmSource;					//!<BGM�\�[�X�B

	enum  MapScene
	{
		STOP,
		MACHI,
		DOUKUTU,
		Battle,
		MENU,
		Change,

	};
	

	MapScene      mapscene; //���݂̃}�b�v���ǂ�������
	MapScene         scenes; //�J�ڂ��ꂽ���̔���
	


	int        I, J;

	bool Bato = false; //�o�g����ʑJ�ڔ���
	




};

extern GameScene* g_gameScene;
