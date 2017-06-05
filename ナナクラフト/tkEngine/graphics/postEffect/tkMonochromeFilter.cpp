/*!
 * @brief	モノクロフィルター。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkMonochromeFilter.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CMonochromeFilter::CMonochromeFilter()
	{
		/*m_isEnable = true;
		m_blendRate = 1.0f;*/
	}
	CMonochromeFilter::~CMonochromeFilter()
	{
	}
	void CMonochromeFilter::Create(const SGraphicsConfig& config)
	{
		m_effect = EffectManager().LoadEffect("Assets/presetShader/monochromeFilter.fx");
	}

}