#pragma once

#include "tkEngine/graphics/postEffect/tkIPostEffectFilter.h"

namespace tkEngine {
	class CPostEffect;
	typedef void(*DrawSkinModelMaskFunc)(CRenderContext& renderContext);
	class CFeedbackblur :public IPostEffectFilter
	{
	public:
		CFeedbackblur();
		~CFeedbackblur();
			void Render(CRenderContext& renderContext, CPostEffect* postEffect);


			void SetEnalbe(bool flag) {
				m_isEnable = flag;
			}
			void SetBlendRate(float rate)
			{
				m_blendRate = rate;
			}
			float GetBlendRate() const
			{
				return m_blendRate;
			}
			void RegistMaskSkinModel(DrawSkinModelMaskFunc pFunc)
			{
				maskModelsFunc.push_back(pFunc);
			}
	void Create(const SGraphicsConfig& config);

	private:
		
		CEffect*	m_effect = nullptr;
		bool		m_isEnable = false;
		float		m_blendRate = 0.0f;	//ブレンド率。1.0で完全にセピアになります。
		float		angle=0.0f;
		float		scale = 1.0f;
		std::vector<DrawSkinModelMaskFunc>	maskModelsFunc;		//マスクモデル。
		int currentBuffer = 0;
		float combineRate = 0.05f;
		CRenderTarget m_lastFlameRenderTarget[2];
	};
}
