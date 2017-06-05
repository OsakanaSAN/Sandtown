#pragma once

#include "tkEngine/graphics/postEffect/tkIPostEffectFilter.h"

namespace tkEngine {
	class CFeedbackblur :
		public IPostEffectFilter
	{
	public:
		CFeedbackblur();
		~CFeedbackblur();

		void Create(const SGraphicsConfig& config);
	};
}
