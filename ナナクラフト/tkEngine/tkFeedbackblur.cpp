#include "tkEngine/tkEnginePrecompile.h"
#include "tkFeedbackblur.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine {
	CFeedbackblur::CFeedbackblur()
	{
		m_isEnable = true;
		m_blendRate = 1.0f;
	}


	CFeedbackblur::~CFeedbackblur()
	{
	}

	void CFeedbackblur::Create(const SGraphicsConfig& config)
	{
		/*m_effect = EffectManager().LoadEffect("Assets/presetShader/Feedbackblur.fx");*/
	}
}