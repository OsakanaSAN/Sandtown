#pragma once


/*!
 *@brief	�^�C�g���V�[���B
 */
class TitleScene :
	public IGameObject
{
public:
	
	
	TitleScene();
	
	~TitleScene();
	bool Start() override;
	
	/*!
	 *@brief	�X�V�֐��B
	 */
	void Update() override;
	/*!
	*@brief	�x���`��֐��B
	@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	*@param[in]		renderContext		�����_�����O�R���e�L�X�g�B
	*/
	void PostRender( CRenderContext& renderContext ) override;
private:
	enum EState {
		eStateWaitFadeIn,	//!<�t�F�[�h�C���҂��B
		eStateRun,			//!<���s���B
		eStateWaitFadeOut,	//!<�t�F�[�h�A�E�g�҂��B
	};

	enum Select {
		NO,
		START,
		BREAK,
	};
	Select GAME = START;

	CSoundSource* bgmSource = NULL;

	CSprite		m_titleBGSprite;		//!<�^�C�g����ʂ̔w�i�̃X�v���C�g�B
	CTexture	m_titleBGTexture;		//!<�^�C�g����ʂ̔w�i�̃e�N�X�`���B

	
	CSprite		m_titleBGSprite2;		//!<�^�C�g����ʂ̔w�i�̃X�v���C�g�B
	CTexture	m_titleBGTexture2;		//!<�^�C�g����ʂ̔w�i�̃e�N�X�`���B

	//START
	CSprite		m_titleBGSprite3;		//!<�^�C�g����ʂ̔w�i�̃X�v���C�g�B
	CTexture	m_titleBGTexture3;		//!<�^�C�g����ʂ̔w�i�̃e�N�X�`���B

	EState      m_state = eStateRun;

	CFont       font;
	char       text[256];

	CSoundSource* PushSE = NULL;
	int count = 0;

	
	

	
};

