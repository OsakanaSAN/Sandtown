#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/character/tkCharacterController.h"



/*!
 *@brief	�Q�[���V�[���B
 */
class GameScene : public IGameObject
{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	GameScene();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~GameScene();
	/*!
	 *@brief	�J�n�֐��B
	 *@details
	 * �������Ȃǂ����̊֐��Ɏ������Ă��������B</br>
	 * ���̊֐���true��Ԃ��Ɩ{�ِ��͈ȍ~�̃t���[���ł͌Ă΂�Ȃ��Ȃ�܂��B</br>
	 * �����ăQ�[���I�u�W�F�N�g�̏�Ԃ������������ɂȂ�Update�֐����Ă΂��悤�ɂȂ�܂��B</br>
	 *@return	true���A���Ă����珉���������B
	 */
	bool Start() override;
	/*!
	 *@brief	�X�V�֐��B
	 */
	void Update() override;
	/*!
	*@brief	�`��֐��B
	*/
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
	
private:
	
	enum set 
	{in,
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

	};
	

	MapScene      mapscene;
	MapScene         scenes;


	CSkinModel testModel[52];	//!<�e�X�g���f���B
	CSkinModelDataHandle testModelDataHandle[52];	//!<�e�X�g���f���f�[�^�n���h���B
	CSprite    GameSprite;
	CTexture   Gametex;
	CVector3   modelpos[52];
	

	int        I, J;
	bool       Chang = true;



	bool Bato = false; //�o�g����ʑJ�ڔ���
	float SceneTime = 0;




};

extern GameScene* g_gameScene;
