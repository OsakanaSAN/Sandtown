#pragma once

class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start() override;

	void Update() override;

	void PostRender(CRenderContext& renderContext)override;

	bool IsExecute() const
	{
		return m_isExecute;
	}

	void StartFadeOut()
	{
		m_timer = 0.0f;
		SetActiveFlag(true);
		m_isExecute = true;
		m_state = eFadeOut;

	}
	void StartFadeIn()
	{
		if (m_sprite.GetAlpha() > 0.0f) {
			m_timer = 0.0f;
			SetActiveFlag(true);
			m_isExecute = true;
			m_state = eFadeIn;
		}
	}


private:
	//��ԁB
	enum EnState {
		eFadeOut,		//!<�t�F�[�h�A�E�g�B
		eFadeIn,		//!<�t�F�[�h�C���B
	};

	enum Load
	{
		UP,
		DOWN,
	};

	int cabetu = UP;
	const float FADE_TIME = 0.3f;		//!<�t�F�[�h�A�E�g�̎��ԁB(�P�ʁF�b)

	CSprite		m_sprite;				//!�u���b�N�A�E�g�p�̃X�v���C�g�B
	CTexture	m_texture;				//!<�u���b�N�A�E�g�p�̃e�N�X�`���B

	CSprite		m_sprite2;				//!�u���b�N�A�E�g�p�̃X�v���C�g�B
	CTexture	m_texture2;				//!<�u���b�N�A�E�g�p�̃e�N�X�`���B

	EnState		m_state = eFadeIn;		//!<��ԁB
	bool		m_isExecute = false;	//!<�t�F�[�h�����s���H
	float		m_timer = 1.0f;			//!<�^�C�}(�P�ʁF�b)
	float       OutTimer = 0.0f;

	CVector2 cabepos = { 720,-280 };
};
extern Fade*   g_fade;
