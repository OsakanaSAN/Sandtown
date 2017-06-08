#include "tkEngine/tkEnginePrecompile.h"
#include "tkFeedbackblur.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/postEffect/tkIPostEffectFilter.h"

namespace tkEngine {
	CFeedbackblur::CFeedbackblur()
	{
		m_isEnable = false;
		m_blendRate = 1.0f;
	}

	CFeedbackblur::~CFeedbackblur()
	{
	}

	void CFeedbackblur::Render(CRenderContext& renderContext, CPostEffect* postEffect)
	{
		
		if (!m_isEnable) {
			angle = 0.0f;
			combineRate = 1.0f;
			scale = 1.0f;
		}
		if (m_isEnable)
		{
			CMatrix		Mat, ScaleMat;
			angle += 0.3f * GameTime().GetFrameDeltaTime();
			Mat.MakeRotationZ(angle);
			ScaleMat.MakeScaling({ scale, scale, scale });
			Mat.Mul(ScaleMat, Mat);
			scale += 0.3f * GameTime().GetFrameDeltaTime();
			//レンダリングターゲットを切り替え。
			Engine().ToggleMainRenderTarget();
	
			renderContext.SetRenderState(D3DRS_ZENABLE, FALSE);

			
			//	CPIXPerfTag tag(renderContext, L"CSepiaFilter::Render");
			float texSize[] = {
				s_cast<float>(Engine().GetMainRenderTarget().GetWidth()),
				s_cast<float>(Engine().GetMainRenderTarget().GetHeight())
			};
			
			//前のフレームの絵にこのフレームのシーンを回転させる。
			{
				m_effect->SetTechnique(renderContext, "Default");
				m_effect->Begin(renderContext);
				m_effect->BeginPass(renderContext, 0);
				m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
				m_effect->SetValue(renderContext, "g_sceneTexSize", texSize, sizeof(texSize));
				m_effect->SetValue(renderContext, "g_blendRate", &m_blendRate, sizeof(m_blendRate));
				m_effect->SetValue(renderContext, "mRot", &Mat, sizeof(Mat));
				m_effect->CommitChanges(renderContext);
				Engine().ToggleMainRenderTarget();
				renderContext.SetRenderTarget(0, &Engine().GetMainRenderTarget());
				postEffect->RenderFullScreen(renderContext);
				m_effect->EndPass(renderContext);
				m_effect->End(renderContext);
			}
			//1フレーム前の絵と合成。
			{

				m_effect->SetTechnique(renderContext, "Combine");
				m_effect->Begin(renderContext);
				m_effect->BeginPass(renderContext, 0);
				m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
				m_effect->SetTexture(renderContext, "g_lastScene", m_lastFlameRenderTarget[currentBuffer].GetTexture());
				m_effect->SetValue(renderContext, "g_combineRate", &combineRate, sizeof(combineRate));
				m_effect->CommitChanges(renderContext);
				Engine().ToggleMainRenderTarget();
				renderContext.SetRenderTarget(0, &Engine().GetMainRenderTarget());
				currentBuffer ^= 1;
				renderContext.SetRenderTarget(1, &m_lastFlameRenderTarget[currentBuffer]);
				postEffect->RenderFullScreen(renderContext);
				m_effect->EndPass(renderContext);
				m_effect->End(renderContext);
				renderContext.SetRenderTarget(1, nullptr);
				combineRate = 0.05f;
			}
			renderContext.SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			renderContext.SetRenderState(D3DRS_ZENABLE, TRUE);
			

			
		}
	}
	void CFeedbackblur::Create(const SGraphicsConfig& config)
	{
		m_effect = EffectManager().LoadEffect("Assets/presetShader/Feedbackblur.fx");
		m_lastFlameRenderTarget[0].Create(
			Engine().GetFrameBufferWidth(),
			Engine().GetFrameBufferHeight(),
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_UNKNOWN,
			D3DMULTISAMPLE_NONE,
			0
		);
		m_lastFlameRenderTarget[1].Create(
			Engine().GetFrameBufferWidth(),
			Engine().GetFrameBufferHeight(),
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_UNKNOWN,
			D3DMULTISAMPLE_NONE,
			0
		);
	}
}