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
	m_texture.Load("Assets/sprite/Load2.png");
	m_texture2.Load("Assets/UI/cabe.png");
	m_sprite.Init(&m_texture);
	m_sprite2.Init(&m_texture2);
	m_sprite2.SetPosition(cabepos);
	m_sprite.SetSize({
	static_cast<float>(Engine().GetFrameBufferWidth()),
	static_cast<float>(Engine().GetFrameBufferHeight()) });
	m_sprite2.SetSize({350,350 });
	SetActiveFlag(false);
	return true;
}
void Fade::Update()
{

	if (cabepos.y <= -270.0f)
	{
		cabetu = UP;
	}
	else if (cabepos.y>-100.0f)
	{
		cabetu = DOWN;
	}

	switch (cabetu)
	{
	case UP:
		cabepos.y += 5.0f;
		break;
	case DOWN:
		cabepos.y -= 4.0f;
		break;
	}
	
	
	m_sprite.SetPosition({ 0.0f,0.0f });
	if (m_isExecute) {
		switch (m_state) {
		case eFadeOut: {
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite2.SetAlpha(min(t, 1.0f));
				m_sprite.SetAlpha(min(t, 1.0f));
				
				OutTimer += GameTime().GetFrameDeltaTime();
			}
			else if (OutTimer < 2)
			{
				m_sprite2.SetAlpha(1.0f);
				m_sprite.SetAlpha(1.0f);
				
				OutTimer += GameTime().GetFrameDeltaTime();
			}

			else {
				m_sprite2.SetAlpha(1.0f);
				m_sprite.SetAlpha(1.0f);
				m_isExecute = false;
				OutTimer = 0;
				
			}
		}break;

		case eFadeIn:
			//ブルスクが映り込まないようにするための処理
			OutTimer += GameTime().GetFrameDeltaTime();
			if (OutTimer < 1.5) { return; }

			//ここからロード画面を消す
			m_timer += GameTime().GetFrameDeltaTime();	
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite2.SetAlpha(max(1.0f - t, 0.0f));
				m_sprite.SetAlpha(max(1.0f - t, 0.0f));
				
			}

			
			else {
				//透明になったので非アクティブにする。
				m_sprite.SetAlpha(0.0f);
				m_sprite2.SetAlpha(0.0f);
				SetActiveFlag(false);
				m_timer = FADE_TIME;
				m_isExecute = false;
				OutTimer = 0;
			}
			break;
		}
		m_sprite2.SetPosition(cabepos);
	}
}
void Fade::PostRender(CRenderContext& renderContext)
{
	
	m_sprite.Draw(renderContext);
	m_sprite2.Draw(renderContext);
}