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
	//状態。
	enum EnState {
		eFadeOut,		//!<フェードアウト。
		eFadeIn,		//!<フェードイン。
	};

	enum Load
	{
		UP,
		DOWN,
	};

	int cabetu = UP;
	const float FADE_TIME = 0.3f;		//!<フェードアウトの時間。(単位：秒)

	CSprite		m_sprite;				//!ブラックアウト用のスプライト。
	CTexture	m_texture;				//!<ブラックアウト用のテクスチャ。

	CSprite		m_sprite2;				//!ブラックアウト用のスプライト。
	CTexture	m_texture2;				//!<ブラックアウト用のテクスチャ。

	EnState		m_state = eFadeIn;		//!<状態。
	bool		m_isExecute = false;	//!<フェードを実行中？
	float		m_timer = 1.0f;			//!<タイマ(単位：秒)
	float       OutTimer = 0.0f;

	CVector2 cabepos = { 720,-280 };
};
extern Fade*   g_fade;
