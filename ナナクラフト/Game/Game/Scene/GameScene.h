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

	
	CLight& GetLite()
	{
		return light;
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


	
	CTexture* 				texture[52];			//!<�e�N�X�`���B
	enum EnCardType {
		enCardType_Heart,		//!<�n�[�g�B
		enCardType_Dia,			//!<�_�C���B
		enCardType_Spade,		//!<�X�y�[�h�B
		enCardType_Clover,		//!<�N���[�o�[�B
		enCardType_Joker,		//!<�W���[�J�[�B
	};
	int                     no = 10;
	EnCardType				type = enCardType_Clover;				//!<�J�[�h�̎�ށB


	CSkinModel testModel[52];	//!<�e�X�g���f���B
	CSkinModelDataHandle testModelDataHandle[52];	//!<�e�X�g���f���f�[�^�n���h���B
	CSprite    GameSprite;
	CTexture   Gametex;
	CVector3   modelpos[52];
	

	int        I, J;




};

extern GameScene* g_gameScene;
