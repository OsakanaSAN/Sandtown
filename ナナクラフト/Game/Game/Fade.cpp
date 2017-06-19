#include "stdafx.h"
#include "Fade.h"



Fade::Fade()
{
}
Fade::~Fade()
{
}
bool Fade::Start()
{
	m_texture.Load("Assets/sprite/Load.png");
	m_sprite.Init(&m_texture);
	m_sprite.SetSize({
	static_cast<float>(Engine().GetFrameBufferWidth()),
	static_cast<float>(Engine().GetFrameBufferHeight()) });
	SetActiveFlag(false);
	return true;
}
void Fade::Update()
{
	m_sprite.SetPosition({ 0.0f,0.0f });
	if (m_isExecute) {
		switch (m_state) {
		case eFadeOut: {
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite.SetAlpha(min(t, 1.0f));
				OutTimer += GameTime().GetFrameDeltaTime();
			}
			else if (OutTimer < 2)
			{
				m_sprite.SetAlpha(1.0f);
				OutTimer += GameTime().GetFrameDeltaTime();
			}

			else {
				m_sprite.SetAlpha(1.0f);
				m_isExecute = false;
				OutTimer = 0;
				
			}
		}break;

		case eFadeIn:
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite.SetAlpha(max(1.0f - t, 0.0f));
			}
			else {
				//透明になったので非アクティブにする。
				m_sprite.SetAlpha(0.0f);
				SetActiveFlag(false);
				m_timer = FADE_TIME;
				m_isExecute = false;
			}
			break;
		}
	}
}
void Fade::PostRender(CRenderContext& renderContext)
{
	m_sprite.Draw(renderContext);
}